// *****************************************************************************
// \file     main.c
//
// \brief    Implementation of CONOPS outlined on qsat wiki.
//           Primarily handles logic control between the four main modes:
//                 - default mode (DefaultMode)
//                 - payload 1 mode (Payload1Mode)
//                 - payload 2 mode (Payload1Mode)
//                 - communications mode (CommsMode)
//
// Platform:  TBD  
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <iostream.h>
#include "avaspec.h"
#include "avaspec-configure.h"
#include "Spectrometer.h"

#define QueryEPS 1o
#define QuerySunSensor 1

EPS clyde_eps;
SUNsensor sunSensors;
// *****************************************************************************
// Function:  Payload1Mode 
//
// \brief:    Spectrometer Measurements
//
//            Check for sufficient power. Query sun sensor. If below ambient
//            light threshold, loop. Otherwise activate spectrometer and
//            perform measurements.
//
//
// *****************************************************************************
void 
Payload1Mode()
{
	if ( clyde_eps.QueryEPS && sunSensors.QuerySunSensor )
	{
		Spectrometer AVS_MiniSpec;

		AVS_MiniSpec.activate();

		AVS_MiniSpec.setMeasureConfig();

		AVS_MiniSpec.measure();

		for( int i = 0; i < 2047; i++ )
		{
			printf("%f\n", AVS_MiniSpec.buffer[i]);
		}
	}
}

void DefaultMode()
{
	Transceiver transceiver;
	Command message;		//need to create a command class (struct?) with command ID, arg and priority fields
	
	while(1)
	{
		message = transceiver.QueryReceiver();
		//do we want to have one message for both command and data? and Identify it using arguments?
		//probs better to have just commands, I just don't know how to handle file transfers
		if(message != 0) 
		{
			CommsMode();
		}
		else
		{
			//need a function to accumulate all telemetry that needs to be sent to ground (telemetryQueue)
			transceiver.transmitToGround(); 	//transmit all queued telemetry
			void (*command)();		//function pointer for command
			while(commandQueue.pop()!= 0) //empty the priorityQueue
			{
				command = commandQueue.serviceNext();	//take the command with the highest priority
				command();
				//need an interrupt in case other things need to be serviced first
			}
		}
	}
	
}

void CommsMode()
{
	//IDK if we need to tell it to keep transmitting. might be redundant and needlessly complicated
	//volatile unsigned int* cont; uplink telling you whether to continue transmitting
	//while (cont == 1)		 continue == 1 means continue transmitting
	//{
		transceiver.getDownlink();
	//	cont = transceiver.QueryReceiver(); 
	//}
	
	if(message.ID == 'start')	//'start' would be the hex digit for the command?
	{
		switch(message.arg2)	//arg2 determines which mode to activate
		{
			case 1: Payload1Mode();
			case 2: Payload2Mode(message.arg3); 	//arg3 tells if mode A or B
			default: defaultMode();
		}
	}
	else if(message.ID == 'upload')
	{
		unsigned char* uploadData;	//maybe send a file identifier
		FILE *fp;
		fp = fopen(filepath, "a");
		//empty the transceiver buffer into a file 
		while (transceiver.buffer != 0)
		{
			*uploadData = transceiver.getData();
			fprintf(fp, "%c", *uploadData);
		}
		fclose(fp);
	}
	
	return 0;
}
int
main()
{
    
	DefaultMode();
	
    return 0;
}
