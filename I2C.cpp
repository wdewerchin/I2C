// Reading and writing I2C devices connected to a RPi on I2C-1
//
// The device 1 is a port expander                 (MCP230008) on address 0x20
//            2 is a temp,pressure,humidity sensor (bme280)    on address 0x77

#include "I2C.h"

void I2cError(const string sMessage)
{
   string sErrorMessage = sMessage + " - " + strerror(errno);
   throw (sErrorMessage);
}

int I2cOpen(const string sDeviceNumber, const int iDeviceAddress)
{
   string sMessage;
   int fI2cFile = -1;
   string sI2cFileName = "/dev/i2c-" + sDeviceNumber;

   if ( (fI2cFile = open(sI2cFileName.c_str(), O_RDWR))  < 0) I2cError("Failed to open the i2c bus");
   if (ioctl(fI2cFile, I2C_SLAVE, iDeviceAddress) < 0)        I2cError("Failed to acquire bus access and/or talk to slave");
   return fI2cFile;
}

void I2cClose(int fI2cFile)
{
   close(fI2cFile);
}

int I2cWrite(int fI2cFile, unsigned char * spData, int iLength)
{
   int iBytesWritten;
   if ((iBytesWritten = write(fI2cFile, spData, iLength) ) != iLength) I2cError("Failed to write to the i2c bus");
   return iBytesWritten;
}

void I2cWriteAddress(int fI2cFile, unsigned char * spAddress, int iAddressLength, unsigned char * spData, int iDataLength)
{
   unsigned char spCombined[iAddressLength + iDataLength];
   memcpy(spCombined,                  spAddress, iAddressLength);
   memcpy(spCombined + iAddressLength, spData,    iDataLength);
   I2cWrite(fI2cFile, spCombined, iAddressLength + iDataLength);
}

int I2cRead(int fI2cFile, unsigned char * spBuffer, int iLength)
{
   int iBytesRead;
   if ((iBytesRead = read(fI2cFile, spBuffer, iLength)) != iLength)     I2cError("Failed to read from the i2c bus");
   return iBytesRead;
}

void I2cReadAddress(int fI2cFile, unsigned char * spAddress, int iAddressLength, unsigned char * spData, int iDataLength)
{
   I2cWrite(fI2cFile, spAddress, iAddressLength);
   I2cRead(fI2cFile, spData, iDataLength);
}
