// TODO write destructor

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "avaspec.h"
#include "avaspec-configure.h"
#include "Spectrometer.h"
#include "log.h"

#define USB 1

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds);
}

Spectrometer::Spectrometer()
{
    a_pMeasConfig  = (MeasConfigType*) malloc(sizeof(MeasConfigType));	

	a_pTimeLabel = (unsigned int*) malloc(sizeof(unsigned int) * 100);

	buffer = (double*) malloc(sizeof(double) * 2047);
}

void Spectrometer::activate()
{
	unsigned int ByteSet;

	int port = USB;

	AvsIdentityType a_pList[30];

	AVS_Init(port); 

	AVS_UpdateUSBDevices();
	
	AVS_GetList( sizeof(a_pList), &ByteSet, a_pList );

	a_hDevice = AVS_Activate( &a_pList[0] );

}


void Spectrometer::setMeasureConfig()
{
	setAvaSpecParameters(a_pMeasConfig);	

	int msmt_prp_sts = AVS_PrepareMeasure(a_hDevice, a_pMeasConfig ); // measurement prepare status

	if(msmt_prp_sts == ERR_SUCCESS)
	{
		log("SCS", "Success: Spectrometer is configured");
	} 
	else 
	{
		log("ERR", "Error: Spectrometer configuration imcomplete");
	}

}

void Spectrometer::measure()
{
	int msmt_sts = AVS_MeasureCallback( a_hDevice, NULL, 1 );
	if(msmt_sts  == ERR_SUCCESS)
	{
		printf ("Measurement Ready\n");
	}
	else
	{
		printf ("%d\n", msmt_sts);
	}

	
	while( !AVS_PollScan( a_hDevice ) )
	{
		delay(10);
	}


	for(int j = 0; j < a_pMeasConfig -> m_Control.m_StoreToRam; j++)
	{
	   AVS_GetScopeData( a_hDevice, a_pTimeLabel, buffer);
	}

}
