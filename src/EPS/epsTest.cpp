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
#include "EPS.cpp"


int main()
{
	// snip
	/* std::string userInput = "B_STATUS";
		std::cout << "Please input a desired command." << std::endl;
		std::getline(std::cin, userInput);
		std::cout << userInput << std::endl;
	// 	end of trash */
	EPS eps;
	int length = 6;
	uint8_t buffer[length];
	//std:: string commandString = "EPSComm::" + userInput; //string of EPS::+userInput 
	//need to convert commandString to unsigned int
	uint8_t command = static_cast<uint8_t>(EPSComm::GET_LASTERR); 
    eps.cmd(command,0x2,0x03, buffer, length);  
}

