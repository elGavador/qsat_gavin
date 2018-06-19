// *****************************************************************************
/// \file     main.c
///
/// \brief    Pseudo-code implementation of CONOPS outlined on qsat wiki.
///           Primarily handles logic control between the four main modes:
///                 - default mode (DefaultMode)
///                 - payload 1 mode (Payload1Mode)
///                 - payload 2 mode (Payload1Mode)
///                 - communications mode (CommsMode)
///
// Platform:  TBD  
// *****************************************************************************

// *****************************************************************************
// Function:  payload1Mode 
//
/// \brief:   Spectrometer Measurements
//
///           Check for sufficient power. Query sun sensor. If below ambient
///           light threshold, loop. Otherwise activate spectrometer and
///           perform measurements.
///
//
// *****************************************************************************

void 
Payload1Mode()
{
    int num_of_loops = 0; 
    int loop_limit; 

    int payload_mode = 1

    while( num_of_Loops != loop_Limit )
    {
        if ( QueryEPS() && QuerySunSensor( payload_mode ) )
        {
            // Would be nicely defined in C++/C as a
            // spectrometer class/struct with methods for:
            //      - query
            //      - activate
            //      - record
            //      etc.
            
            QuerySpectrometerBuffer(); 

            ActivateSpectrometer();
    
            RecordData();

            SelectSampleLamp();

            Wait(300);

            TakeSpectra()

            StoreSpectra()

        }
        else 
        {
            loop_limit++;
        }
    }
}

// *****************************************************************************
// Function:  payload2Mode 
//
/// \brief:   Morse Code 
///
///           Check for sufficient power and eclipse, loop. Otherwise check
///           uplink message for Mode A or Mode B, and pass control accordingly.
///           Mode A activates LED of specificied wavelength on X, -X, Y or 
///           -Y. Mode B blinks morse code on Z LED's. 
//
// *****************************************************************************

void 
Payload2Mode()
{
    int num_of_loops = 0; 
    int loop_limit; 

    int payload_mode = 2;

    while ( num_of_loops != loop_limit )
    {
        if ( QueryEPS() && QuerySunSensor( payload_mode ) )
        {
            char mode = QueryReciever();            
            
            switch ( mode )
            {
                case 'A':   
                    morseCode();
                case 'B':
                    while ( !contactTimeBeam )
                    { 
                        activateLed('X');
                        activateLed('Y');
                        activateLed('Z');

                    }
            }
        } 
        else 
        {
            loop_limit++;
        }
    }

}


// *****************************************************************************
// Function: queryReciever 
//
/// \brief:  Checks the reciever buffer/file to see if there has been an uplink. 
///
/// \return: Return 0 or 1 depending on if there has been an uplink.  
//
// *****************************************************************************

void 
QueryReciever()
{

}


// *****************************************************************************
// Function: deployAntenna 
//
/// \brief:  Trigger current to burn restraint and deploy antenna. 
///
/// \return: Currently void. If there is a mechanism that can determine if
///          deployment has been successful (i.e. a button that is depressed 
///          when the antenna is extended) than return 0 or 1 depending on
///          status of deployment. 
//
// *****************************************************************************

void
DeployAntenna()
{
    // Code to release wire current 
}

// *****************************************************************************
// Function: queryEPS 
//
/// \brief:  Determine if there is sufficient battery power to perform task. 
///
/// \param:  Could be void or accept a parameter depending on the task needed. 
///
/// \return: powerStatus     Return 0 or 1 depending on if there is sufficient 
///          power.
//
// *****************************************************************************

int
QueryEPS() 
{
    // Check power. This will require a knowledge
    // of the both the electrical circuitry being
    // used and the software drivers available.
    // 
    // Find out:
    //      - Are there drivers specific to the 
    //      power supply that will return a
    //      battery power estimation? (unlikely)
    //
    //      - Is it an electrical problem?
    //      For example:
    //          - A circuit that monitors voltage
    //          through an Analogue to Digital
    //          converter (ADC).

    return powerStatus;
}

// *****************************************************************************
// Function: querySunSensor
//
/// \brief:  Determine whether ambient light is above threshold, or determine
///          if cubesat is in eclipse depending on input.
///
/// \param:  mode          The mode to be selected. If mode = 1, indicating
//                         payload 1 mode, querySunSensor will check ambient
//                         light threshold. If mode = 2, indicating payload
//                         2 mode, querySunSensor will check if cubesat is 
//                         in ecplipse.
///
/// \return: Return 0 or 1 depending on if there is sufficient 
///          power.
//
// *****************************************************************************

int
QuerySunSensor( int payload_mode )
{

}

// *****************************************************************************
// Function: defaultMode 
//
/// \brief:  Check for sufficient power. On first boot deploy antenna. 
///          Turn on and query reciever. If no ground input transmit telemetry
///          then query reciever.
///          If ground input transfer control to communications mode,
///          payload 1 mode and payload 2 mode.
//
// *****************************************************************************

void
DefaultMode()
{
    // While there is not sufficient power, wait 30 minutes.
    while ( !QueryEPS() )
    {
        wait(1800) // 30 minutes
    }

    // If antenna has not been deployed, deploy antenna.
    if ( !antenna_status )
    {
        DeployAntenna();
    }
   
    // If reciever is off, turn reciever on.
    if ( !reciever_status )
    {
        RecieverOn(); // modifies receiverHandle to 1
    }

    int uplink = QueryReciever();

    if ( uplink )
    {
        CommsMode();

        Payload1Mode();

        Payload2Mode();
    }
    else
    {
        TransmitTelemetry();
    }

}

int
main()
{
    defaultMode();

    sensorsOff();

    return 0;
}
