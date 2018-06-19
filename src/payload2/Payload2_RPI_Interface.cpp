//Payload 2 Command Interface Test
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
#include <iostream>
#include "command_lib.h"
#include "payload2.cpp"

int main()
{
	Payload2 P2;
	FILE *fp;
	//std:: string commandString = "P2Comm::" + userInput; //string of EPS::+userInput 
	
	//need to convert commandString to unsigned int
	uint8_t command; 
	int readLength;
	int value1, value2, value3;
	uint8_t buffer[6];
	
	*readLength = 0;
	
	// want the user to be able to type in words, not hexadecimal numbers
	scanf("%x", &command);
	
	if (command == 0x00)
	{
		while (readLength > 3 || readLength < 0)
		{
			scanf("Number of values to read: %u", &readLength);
		}
	}
	
    P2.cmd(command, buffer, readLength*2);  
	
	// Each value received is a two byte int; all values received are put into one buffer
	value1 = ((value1 | buffer[1]) << 8) | buffer[0];
	value2 = ((value2 | buffer[3]) << 8) | buffer[2];
	value3 = ((value3 | buffer[5]) << 8) | buffer[4];
	
	// OUTPUT_VALUES()
	if ( (fp = fopen("P2data", "a+")) == NULL)
	{
		fprintf(stderr, "Error opening file.");
	}	
	else
	{
		fprintf(fp, "Value1: %f", value1);
		fprintf(fp, "Value2: %f", value2);
		fprintf(fp, "Value3: %f", value3);
	}
	fclose(fp);
}