#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdint>
#include "I2C.cpp"

#define EPS_FrameLength 6

class EPS {
public:
  EPS(){};
  void cmd(uint8_t, int, uint8_t);  //command, data[0], data[1]
  ~EPS(){};
};

void EPS::cmd(uint8_t cmd, int data0, uint8_t data1, uint8_t *buffer, int length)
{
  uint8_t addr = 8; //0x2B; factory-set address
  int file;
  bool TRcomplete;
  
  I2C i2c;
  
  file = i2c.open(addr);
  
  //initialize command packet
  buffer[0] = cmd;
  int * data0location = (int*)(&buffer[1]);  
  *data0location = data0;
  buffer[5] = data1;
  
  length = EPS_FrameLength;	//length of command frame
  
  //if TRcomplete = 1, the command was sent successfully and data can then be read from the EPS
  TRcomplete = i2c.write(file, buffer, length);  //address of EPS should be a global variable in fact all of the I2C 
												//addresses should be global or at least known by the I2C class 
  if (TRcomplete)
  {
	//how many data bytes to be read, depends on command
	i2c.read(file, buffer, length);
  }
  
  // Probably will have to close the i2c bus here
}