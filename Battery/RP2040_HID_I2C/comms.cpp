#include "comms.h"

#if defined(ARDUINO_ARCH_SAMD)
MYSERCOM mysercom(PIN_WIRE_SERCOM);
TwoWire MyWire(&mysercom, PIN_WIRE_BATT_SDA, PIN_WIRE_BATT_SCL);
#endif

#ifdef ARDUINO_SEEED_INDICATOR_RP2040
#define DELAYUS(_us) busy_wait_us_32(_us)
#endif
#if defined(ARDUINO_ARCH_SAMD)  
#define DELAYUS(_us) delayMicroseconds(_us)
#endif

volatile THIDData HIDData[DAUGHTERBOARDCOUNT] = {0};

TBoardInfo BoardInfo = 
{
  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  true, // DataInValid
  #endif
  #if defined(ARDUINO_ARCH_SAMD)  
  false, // DataValid
  #endif
  {0}, // Default BoardSerial
  0 // Default BoardNumber
};

uint16_t UpdateCrc(uint16_t crc, const uint8_t* data_p, uint8_t length)
{
  uint8_t x;

  while (length--){
      x = crc >> 8 ^ *data_p++;
      x ^= x>>4;
      crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
  }
  return crc;
}

static inline bool CheckWireStuck(void)
{
  bool Result = false;
  Result |= (digitalRead(PIN_WIRE_BATT_SDA) == LOW);  
  Result |= (digitalRead(PIN_WIRE_BATT_SCL) == LOW);
  return Result;    
}

// Emulate opendrain pins
void PinLow(uint32_t ulPin)
{
  digitalWrite(ulPin, LOW);
  pinMode(ulPin, OUTPUT);
}
void PinHigh(uint32_t ulPin)
{
  pinMode(ulPin, INPUT_PULLUP);
  digitalWrite(ulPin, HIGH);  
}

void ResetWire(void)
{
  byte bits;

  #ifdef DEBUG
  Serial.println("Wire reset starting.");
  #endif

  pinMode(PIN_WIRE_BATT_SDA, INPUT_PULLUP);
  pinMode(PIN_WIRE_BATT_SCL, INPUT_PULLUP);

  #ifdef ARDUINO_SEEED_INDICATOR_RP2040
  gpio_set_function(PIN_WIRE_BATT_SCL, GPIO_FUNC_SIO);
  gpio_set_function(PIN_WIRE_BATT_SDA, GPIO_FUNC_SIO);
  #endif

  DELAYUS(100U);

  if ( (digitalRead(PIN_WIRE_BATT_SDA) == LOW) && (digitalRead(PIN_WIRE_BATT_SCL) == HIGH) )
  {
    #ifdef DEBUG
    Serial.println("Wire reset manual clock.");
    #endif

    // Send at max 9 clock pulses
    bits=0;
    while ( (bits < 9) && (digitalRead(PIN_WIRE_BATT_SDA) == LOW) )
    {
      bits++;
      PinLow(PIN_WIRE_BATT_SCL);
      DELAYUS(5);
      PinHigh(PIN_WIRE_BATT_SCL);
      DELAYUS(5);
    }

    if (digitalRead(PIN_WIRE_BATT_SDA) == HIGH)
    {
      // Bus recovered : send a STOP
      PinLow(PIN_WIRE_BATT_SDA);
      DELAYUS(5);
      PinHigh(PIN_WIRE_BATT_SDA);
    }
    #ifdef DEBUG
    Serial.printf("Wire reset manual clock bits needed: #%d.\r\n", bits);
    #endif
  }

  DELAYUS(100U);

  if (CheckWireStuck())
  {
    if (digitalRead(PIN_WIRE_BATT_SCL) == HIGH)
    {
      #ifdef DEBUG
      Serial.println("Wire reset for SCL low 50ms.");
      #endif
      // Force clock low for 50ms should reset all SAMD10 slaves.
      PinLow(PIN_WIRE_BATT_SCL);
      DELAYUS(50000U);
      PinHigh(PIN_WIRE_BATT_SCL);
    }
  }

  DELAYUS(100U);

  #ifdef DEBUG
  if (CheckWireStuck())
  {
    Serial.println("Resetting wire failed.");
  }
  else
  {
    Serial.println("Resetting wire successful.");
  }
  #endif
}

bool process_command(void const *data, void *result)
{
  byte I2CRXBUFFER[16] = {0}; // datafuffer for i2c slaves

  byte cCmd = 0;
  byte cBat = 0;
  byte cLength = 0;
  byte slave_address = 0;
  
  WORD_VAL cRxCrc;
  WORD_VAL NewCRC;

  byte i,j,databyte;

  byte* databuffer = (byte*)data;
  byte* resultbuffer = (byte*)result;

  qword Ecalc;

  bool DataToSend = true;
  bool GUIUpdateNeeded = false;

  #ifdef CONSOLE_DEBUG
  bool DEBUGONSCREEN = false;
  #endif

  PBatteryBoard LocalBatteryBoard;
  PMeasurementData LocalBatteryData;

	cCmd=databuffer[0];
	resultbuffer[0]=cCmd;
  cBat=databuffer[1];
  resultbuffer[1]=cBat;

  cLength=databuffer[2];

  LocalBatteryBoard= &BatteryBoards[cBat];
  LocalBatteryData = &LocalBatteryBoard->MD;

  // Defaults
  LocalBatteryBoard->I2CStatus.I2CBytesReceived = 0;
  LocalBatteryBoard->I2CStatus.I2CSendError = 0;
  LocalBatteryBoard->I2CStatus.I2CCRCError = false;
  LocalBatteryBoard->I2CStatus.I2CBlocked = false;

  #ifndef COIN
  slave_address=((cBat)<<1U)+0x20U;
  #else
  slave_address=(cBat)/4;
  slave_address<<=1;
  slave_address+=0x20;
  #endif

  #ifndef COIN
  if (cLength>13)
  #else
  if (cLength>12)
  #endif
  {
    #ifdef DEBUG    
    Serial.printf("Error [bat: %02d]. Wrong length:%d.\r\n", cBat, cLength);
    #endif
    cCmd = CMD_error;
    cLength = 0;
  }

  if (cCmd == CMD_set_value)
  {
    if ((cLength == 5) || (cLength == 7))
    {
      LocalBatteryBoard->BM.Status=TStageMode(databuffer[3]);
      LocalBatteryBoard->BM.SetValue=databuffer[4]+256*databuffer[5]+256*256*databuffer[6]+256*256*256*databuffer[7];
      GUIUpdateNeeded = true;
    }
  }

  if (cCmd == CMD_set_energy)
  {
    if (cLength == 4)
    {
      Ecalc=(qword(databuffer[3])+qword(databuffer[4])*256+qword(databuffer[5])*256*256+qword(databuffer[6])*256*256*256);
      Ecalc *= 65536;
      Ecalc /= (8*32*3600/**1000*/);
      LocalBatteryData->E = dword(Ecalc);
      GUIUpdateNeeded = true;
    }
  }

  LocalBatteryBoard->I2CStatus.I2CBlocked = CheckWireStuck();

  // Are we good to go to communicate with slave ?
  if (!LocalBatteryBoard->I2CStatus.I2CBlocked)
  {
    // Join i2c bus as master
    WireBattery.begin();

    // Pause a few us after joining bus
    delayMicroseconds(10U);

    #ifdef ARDUINO_SEEED_INDICATOR_RP2040
    LocalBatteryBoard->I2CStatus.I2CBlocked = (!WireBattery.busIdle());
    if (LocalBatteryBoard->I2CStatus.I2CBlocked) WireBattery.end();
    #endif
  }

  // Are we still good to go to communicate with slave ?
  if (!LocalBatteryBoard->I2CStatus.I2CBlocked)
  {
    #ifdef ARDUINO_SEEED_INDICATOR_RP2040
    WireBattery.clearTimeoutFlag();            
    #endif

    NewCRC.Val = 0xFFFFU;

    //WireBattery.flush();
    WireBattery.beginTransmission((slave_address)); 
    NewCRC.Val = UpdateCrc(NewCRC.Val, &slave_address, 1);

    databyte = cCmd; 
    WireBattery.write(databyte);
    NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);

    #ifndef COIN
    databyte = cLength; 
    WireBattery.write(databyte);
    NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
    #else
    databyte = cLength+1; 
    WireBattery.write(databyte);
    NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
    databyte = cBat % 4; 
    WireBattery.write(databyte);
    NewCRC.Val = UpdateCrc(NewCRC.Val, &databyte, 1);
    #endif

    if (cLength>0)
    {
      for ( i=0; i < cLength;i++ )
      {
        databyte = databuffer[i+3];
        WireBattery.write(databyte);
      }
      NewCRC.Val = UpdateCrc(NewCRC.Val,(byte*)&databuffer[3],cLength);
    }

    WireBattery.write(NewCRC.bytes.HB);
    WireBattery.write(NewCRC.bytes.LB);

    // now, send all data !!
    LocalBatteryBoard->I2CStatus.I2CSendError = WireBattery.endTransmission(false /* false will send a restart */);

    // i2c needs at least a few us between commands
    //delayMicroseconds(5U);
    //sleep_us(2);

    if (LocalBatteryBoard->I2CStatus.I2CSendError == 0)
    {
      // All ok !!
      // Receive slave-address and 16 databytes
      LocalBatteryBoard->I2CStatus.I2CBytesReceived = WireBattery.requestFrom(slave_address, 17ul, true /* stop */);    // request max 17 bytes from slave device #2
    }
    else
    {
      // We have an i2c error !!
      // Errors:
      //  0 : Success
      //  1 : Data too long
      //  2 : NACK on transmit of address
      //  3 : NACK on transmit of data
      //  4 : Other error : could not send the required amount of data bytes
      //  5 : Timeout [on RP2040]

      #ifdef DEBUG
      Serial.printf("Error [bat: %02d]. I2C transmission error number: %d.\r\n", cBat, LocalBatteryBoard->I2CStatus.I2CSendError);
      #endif

      // Force a stop on the wire
      WireBattery.endTransmission(true /* true will send a stop */);

      // RP2040 has timeout error, others only have general errors
      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      // Timeout !!
      // Very severe !!
      if (LocalBatteryBoard->I2CStatus.I2CSendError == 5)
      #else
      // General error.
      // Check wire if stuck
      if (LocalBatteryBoard->I2CStatus.I2CSendError != 0)
      #endif
      {
        LocalBatteryBoard->I2CStatus.I2CBlocked = true;              

        #ifdef ARDUINO_SEEED_INDICATOR_RP2040
        if (WireBattery.getTimeoutFlag()) // trivial ... ;-)
        {
          WireBattery.clearTimeoutFlag();
        }
        #endif
      }
    }

    // Take a look at the i2c data received
    if (LocalBatteryBoard->I2CStatus.I2CBytesReceived != 0)
    {
      // Count real data received
      i = 0;

      // Receive slave address
      if (WireBattery.available())
      {
        slave_address = WireBattery.read();
        LocalBatteryBoard->I2CStatus.I2CAddress = slave_address;
        i++;
      }

      // Receive real data from slave
      j = 0;
      while ( WireBattery.available() && (j<sizeof(I2CRXBUFFER)) )
      {
        I2CRXBUFFER[j++] = WireBattery.read();
      }
      i += j;

      #ifdef DEBUG
      if (i == 0) Serial.printf("Error [bat: %02d]. No I2C data processed.\r\n", cBat);
      #endif

      if (LocalBatteryBoard->I2CStatus.I2CBytesReceived != i)
      {
        #ifdef DEBUG        
        Serial.printf("Error [bat: %02d]. Mismatch between I2C data's received/processed [%d/%d].\r\n", cBat, LocalBatteryBoard->I2CStatus.I2CBytesReceived, i);
        #endif
        LocalBatteryBoard->I2CStatus.I2CBlocked = true;
      }
    }

    // Ready with wire: end master
    WireBattery.end();

    cLength = 0;
    cCmd = USB_CMD_error;

    // Look at the valid i2c data
    if (LocalBatteryBoard->I2CStatus.I2CBytesReceived != 0)
    {
      // Process the data and check the CRC

      NewCRC.Val = UpdateCrc(0xFFFFU, &slave_address, 1);

      j = 0;

      cCmd = I2CRXBUFFER[j++];
      cLength = I2CRXBUFFER[j++];

      // Check length
      // If not ok, this is a severe error: handle later
      if (cLength<=(sizeof(I2CRXBUFFER)-5))
      {
        NewCRC.Val = UpdateCrc(NewCRC.Val, &cCmd, 1);
        NewCRC.Val = UpdateCrc(NewCRC.Val, &cLength, 1);

        if (cLength>0)
        {
          NewCRC.Val = UpdateCrc(NewCRC.Val,(byte*)&I2CRXBUFFER[j],cLength);            
        }   

        j += cLength;

        cRxCrc.bytes.HB = I2CRXBUFFER[j++];
        cRxCrc.bytes.LB = I2CRXBUFFER[j++];

        LocalBatteryBoard->I2CStatus.I2CCRCError = (cRxCrc.Val != NewCRC.Val);
        if (LocalBatteryBoard->I2CStatus.I2CCRCError) Serial.printf("Error [bat: %02d]. I2C CRC error on #%d databytes.\r\n", cBat, LocalBatteryBoard->I2CStatus.I2CBytesReceived);
      } 
      else
      {
        #ifdef DEBUG
        Serial.printf("Error [bat: %02d]. I2C length [%d] error on #%d databytes.\r\n", cBat, cLength, LocalBatteryBoard->I2CStatus.I2CBytesReceived);            
        #endif
        cLength = 0;
        cCmd = USB_CMD_error;            
      }
    }

    // Always set the result buffer with the data received for easier debugging !!
    j = 0;
    resultbuffer[j++]=cCmd;
    resultbuffer[j++]=cBat;
    resultbuffer[j++]=cLength;
    if (cLength>0) // cLength is not bigger than [sizeof(I2CRXBUFFER)-5] = 11
    {
      // Copy i2c data into result
      for ( i = 0; i < cLength ; i++ ) resultbuffer[j++]= I2CRXBUFFER[i + 2];
    }
    resultbuffer[j++] = cRxCrc.bytes.HB;
    resultbuffer[j++] = cRxCrc.bytes.LB;

    // All ok ? Process data
    if ( (LocalBatteryBoard->I2CStatus.I2CBytesReceived != 0) && (!LocalBatteryBoard->I2CStatus.I2CCRCError) && (!LocalBatteryBoard->I2CStatus.I2CBlocked) )
    {
      if (cCmd == CMD_get_data)
      {
        LocalBatteryData->V = (I2CRXBUFFER[0 + 2] + I2CRXBUFFER[1 + 2]*256);
        LocalBatteryData->I = (I2CRXBUFFER[2 + 2] + I2CRXBUFFER[3 + 2]*256);
        LocalBatteryData->E = (I2CRXBUFFER[4 + 2] + I2CRXBUFFER[5 + 2]*256 + I2CRXBUFFER[6 + 2]*256*256 + I2CRXBUFFER[7 + 2]*256*256*256);
        /*
        Ecalc=(qword(I2CRXBUFFER[4 + 2])+qword(I2CRXBUFFER[5 + 2])*256+qword(I2CRXBUFFER[6 + 2])*256*256+qword(I2CRXBUFFER[7 + 2])*256*256*256);
        Ecalc *= 65536;
        Ecalc /= (8*32*3600);
        LocalBatteryData->E = dword(Ecalc);
        */
        //MyUSBDevice.Data[cBat].C = MyUSBDevice.Data[cBat].E / (MyUSBDevice.Vmax[cBat]*MyUSBDevice.Data[cBat].V / ((1 << BITS)-1));
        LocalBatteryData->T = (I2CRXBUFFER[8 + 2] + I2CRXBUFFER[9 + 2]*256);
        GUIUpdateNeeded = true;
      }

      if (cCmd == CMD_set_value)
      {
        if (cLength > 4)
        {
          LocalBatteryBoard->BM.Status=TStageMode(I2CRXBUFFER[4 + 2]);
          LocalBatteryBoard->BM.SetValue=I2CRXBUFFER[5 + 2]+256*I2CRXBUFFER[6 + 2]+256*256*I2CRXBUFFER[7 + 2]+256*256*256*I2CRXBUFFER[8 + 2];
          if (LocalBatteryBoard->BM.SetValue==0)
          {
            //LocalBatteryData->Status=BSOff;
          }
          GUIUpdateNeeded = true;
        }
      }

      if (cCmd == CMD_get_firmware)
      {
        LocalBatteryBoard->Firmware = (I2CRXBUFFER[0 + 2]);
        LocalBatteryBoard->Imax = (I2CRXBUFFER[2 + 2] + I2CRXBUFFER[3 + 2]*256);
        LocalBatteryBoard->Vmax = (I2CRXBUFFER[4 + 2] + I2CRXBUFFER[5 + 2]*256);
        LocalBatteryBoard->NeedsDataUpdate;
      }

      if (cCmd == CMD_get_localserial)
      {
        for ( j=0; j<8; j++ )
        {
          LocalBatteryBoard->Serial[j] = (I2CRXBUFFER[j + 2]);
        }
      }
    }
  } // !Blocked

  LocalBatteryBoard->NeedsGUIUpdate |= GUIUpdateNeeded;

  // Error handling
  if ( (LocalBatteryBoard->I2CStatus.I2CBytesReceived == 0) || (LocalBatteryBoard->I2CStatus.I2CBlocked) )
  {
    #ifdef DEBUG    
    if (LocalBatteryBoard->I2CStatus.I2CBlocked)
    {
      Serial.printf("Error [bat: %02d]. I2C wire transmission blocked.\r\n", cBat);
    }
    else
    {  
      if (LocalBatteryBoard->I2CStatus.I2CBytesReceived == 0)
      {
        Serial.printf("Error [bat: %02d]. No I2C data received.\r\n", cBat);
      }
      else
      {
        //Serial.printf("Error [bat: %02d]. Unknown I2C error.\r\n", cBat);
      }
    }
    #endif

    // Wire might be severely blocked.
    if (CheckWireStuck())
    {
      delayMicroseconds(1000U);
      // Check again !!
      if (CheckWireStuck())
      {
        #ifdef DEBUG
        Serial.println("Wire stuck. Severe error. Trying to reset wire.");
        #endif
        // We have a severe bus-error. Try to unblock.
        ResetWire();
      }
    }
  }
  // Trivial: return true to indicate we have data to return.
  // Should always be true with this firmware !!
  return (DataToSend);
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* hid_report_out, uint16_t bufsize)
{
  (void) report_id;
  (void) report_type;
  (void) bufsize;

  byte hid_report_in[HID_INT_IN_EP_SIZE] = {0};
  byte j;

  bool SendData = true;
	byte cCmd = hid_report_out[0];

	hid_report_in[0] = cCmd;

	switch (cCmd)
  {
	  case 0:
		{
      hid_report_in[0]=CMD_error;      
      break;
    }

	  case USB_CMD_get_serial:
		{
      for ( j=0; j<12; j++ )
      {
        hid_report_in[j+1] = BoardInfo.BoardSerial[j];
      }
      break;
    }

		case USB_CMD_set_serial:
		{
      for ( j=0; j<12; j++ )
      {
        BoardInfo.BoardSerial[j] = hid_report_out[j+1];
        hid_report_in[j+1] = BoardInfo.BoardSerial[j];
      }
      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      BoardInfo.InValid = false;
      #endif
      #if defined(ARDUINO_ARCH_SAMD)  
      BoardInfo.Valid = true;
      #endif
      storePutBoardInfo(&BoardInfo);
			break;
		}

		case USB_CMD_get_firmware:
		{
			hid_report_in[1]=FW_MAJOR;
			hid_report_in[2]=FW_MINOR;
			break;
		}

    case USB_CMD_get_board_number:
    {
      hid_report_in[1] = BoardInfo.BoardNumber;
      break;
    }

    case USB_CMD_set_board_number:
    {
      BoardInfo.BoardNumber = hid_report_out[1];
      #ifdef ARDUINO_SEEED_INDICATOR_RP2040
      BoardInfo.InValid = false;
      #endif
      #if defined(ARDUINO_ARCH_SAMD)  
      BoardInfo.Valid = true;
      #endif
      storePutBoardInfo(&BoardInfo);
      break;
    }

		default:
		{
      byte cBat=hid_report_out[1];
      if (cBat<DAUGHTERBOARDCOUNT)
      {
        SendData = false;
        for ( j=0; j<HID_INT_OUT_EP_SIZE; j++ ) HIDData[cBat].HIDEPOUTData[j] = hid_report_out[j];
        HIDData[cBat].DataReceived = true;
      }
      else
      {
        #ifdef DEBUG
        Serial.printf("Error. Wrong battery number:%d.\r\n", cBat);
        #endif
	      hid_report_in[0]=CMD_error;
      }
    }
  }

  if (SendData)
  {
     // This delay seems necessary for communication with PC host
     // I do not know why ... :-()
    delayMicroseconds(1000U);

    // Send report back to host
    usb_hid.sendReport(0, hid_report_in, HID_INT_IN_EP_SIZE);
  }
}
