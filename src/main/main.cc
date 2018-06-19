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
#include "avaspec.h"
#include "avaspec-configure.h"
#include "Spectrometer.h"

#define QueryEPS 1
#define QuerySunSensor 1

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
	if ( QueryEPS && QuerySunSensor )
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


int
main()
{
    
	Payload1Mode();

    return 0;
}
