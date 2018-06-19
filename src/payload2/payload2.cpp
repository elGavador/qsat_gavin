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


#define Arduino_FrameLength 1

class Payload2 {
public:
  Payload2(){};
  void cmd(uint8_t);  //command, data[0], data[1]
  ~Payload2(){};
};

void Payload2::cmd(uint8_t cmd, uint8_t *buffer, int readLength)
{
  uint8_t addr = 8; // factory-set i2c address of the arduino
  uint8_t packet[8] = {0};	//8 is an arbitrary packet length
  int file;
  int length;
  bool TRcomplete;
  
  I2C i2c;
  
  file = i2c.open(addr);
  
  packet[0] = cmd;
  
  length = Arduino_FrameLength;	//length of command frame
  
  //if TRcomplete = 1, the command was sent successfully and data can then be read from the EPS
  TRcomplete = i2c.write(file, buffer, length);  //address of EPS should be a global variable in fact all of the I2C 
												//addresses should be global or at least known by the I2C class 
  if (TRcomplete)
  {
	i2c.read(file, buffer, readLength);
  }
}