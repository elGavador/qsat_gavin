// SunSensor Data-Handler

#include <iostream>
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

void readSensors(int *parray);

int main()
{
  uint8_t buffer[4];
  
  uint8_t response[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int photoDiodeVals[3];
  
   
  readSensors(photoDiodeVals);
  memcpy(response, photoDiodeVals, sizeof(int)*3);
  
  int value1, value2, value3;
  
  value1 = *response | 0x0000000000000000FFFFFFFF;
  value2 = (*response | 0x00000000FFFFFFFF00000000) >> 32;
  value3 = (*response | 0xFFFFFFFF0000000000000000) >> 64;
  
  printf("%d\n", value1);
  printf("%d\n", value2);
  printf("%d\n", value3);
}

void readSensors(int *parray)
{
    parray[0] = 1;
    parray[1] = 2;
    parray[2] = 3;
}
