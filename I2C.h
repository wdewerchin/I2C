#ifndef I2C_H_
#define I2C_H_

#include <string>
#include <iostream>
using namespace std;

#include <stdio.h>
#include <unistd.h>           // Needed for I2C port
#include <fcntl.h>            // Needed for I2C port
#include <errno.h>            // include if errno is being used
#include <sys/ioctl.h>        // Needed for I2C port
#include <linux/i2c-dev.h>    // Needed for I2C port
#include <time.h>

#include <memory.h>

void I2cError(const string sMessage);
int  I2cOpen(const string sDeviceNumber, const int iDeviceAddress);
void I2cClose(int fI2cFile);
int  I2cWrite(int fI2cFile,  unsigned char * spData, int iLength);
void I2cWriteAddress(int fI2cFile, unsigned char * spAddress, int iAddressLength, unsigned char * spData, int iDataLength);
int  I2cRead(int fI2cFile, unsigned char * spBuffer, int iLength);
void I2cReadAddress(int fI2cFile, unsigned char * spAddress, int iAddressLength, unsigned char * spData, int iDataLength);

#endif /* I2C_H_ */
