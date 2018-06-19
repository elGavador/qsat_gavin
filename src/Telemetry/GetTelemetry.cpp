/*QUERYBEACON(): Gathers all telemetry from all critical hardware; to be transmitted to earth ASAP
Critical Hardware includes:
	- EPS (Power readings, I2C bus) **DONE
	- Magnetometer (data, I2C bus)
	- RTC (Current Time)
	- Thermistors (Temperature readings, ADC)
	- Sun Sensors (Data, ADC)	**DONE
Will append all readings to a telemetry file; to be sent to earth for health readings

NOTES: 
	- writes everything to a file 
	  and then sends that to the Transceiver at the end (Transceiver functions need to be integrated)
	- Need to check the endianness of the Rpi to see how memcpy will work  
*/
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
#include <sys/types.h>
#include <sys/stat.h>
#include "command_lib.h"
#include "EPS.cpp"
#include "payload2.cpp"

//**Get all telemetry from EPS**
//refer to table 11-8 in the EPS User Manual for pin addresses
int main() 
{
	Query_EPS();
	Query_P2();
}

// QUERY EPS()
void Query_EPS()
{
	FILE *fp;
	uint8_t buffer[6];
	
	if ( (fp = fopen("TelemetryBeacon.txt", "a+")) == NULL)
	{
		fprintf(stderr, "Error opening file.");
	}	
	else
	{
		fprintf("EPS DATA:\n\n");
		EPS eps;

		//Get all output currents and voltages
		int EPSPDM_n = 10;
		int length = 4;
		float voltage[10];
		float current[10];
		
		// EPS: OUTPUT SWITCHES
		for (int i = 0; i < EPSPDM_n; i++)
		{
			//cycles through all pins connected to the EPS;
			//GET VOLTAGE
			eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE410 + (8*i), 0x00, buffer, 4);
			
			// debug statement to check buffer endianness
			//std::cout << buffer[0] << " " << buffer[1] << " " << buffer[2] << " " << buffer[3] << "\n";
			
			//depending on the "endianness" of the rPi, data received might have to be shifted
			memcpy(voltage[i], buffer, sizeof(float));
			fprintf(fp,"Output Voltage Switch %d: %f", i, voltage[i]);
			
			//GET CURRENT
			eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE414 + (8*i), 0x00, buffer, 4);
			
			memcpy(current[i], buffer, sizeof(float));
			fprintf(fp,"Output Current Switch %d: %f", i, current[i]); // Instead of printing, would have to send to transceiver (e.g. Send2Transceiver())
		}
		
		// EPS: 3.3V and 5V current draw
		
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE205, 0x00, buffer, 4);		// 3.3 V current draw
		fprintf(fp, "3.3V Bus Current Draw: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE215, 0x00, buffer, 4);		// 5 V current draw
		fprintf(fp, "5V Bus Current Draw: %f\n", buffer);
		//**Send2Transceiver(String label);
		
		// EPS: Busses
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE234, 0x00, buffer, 4);		// 12V Bus Current
		fprintf(fp, "12V Bus Output Current: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE230, 0x00, buffer, 4);		// 12V Bus Voltage
		fprintf(fp, "12V Bus Output Voltage: %f\n", buffer);
		
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE224, 0x00, buffer, 4);		// Battery Bus Current
		fprintf(fp, "Battery Bus Output Current: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE220, 0x00, buffer, 4);		// Battery Bus Voltage
		fprintf(fp, "Battery Bus Output Voltage: %f\n", buffer);
		
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE214, 0x00, buffer, 4);		// 5V Bus Current
		fprintf(fp, "5V Bus Output Current: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE210, 0x00, buffer, 4);		// 5V Bus Voltage
		fprintf(fp, "5V Bus Output Voltage: %f\n", buffer);
		
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE204, 0x00, buffer, 4);		// 3.3V Bus Current
		fprintf(fp, "3.3V Bus Output Current: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE200, 0x00, buffer, 4);		// 3.3V Bus Voltage
		fprintf(fp, "3.3V Bus Output Voltage: %f\n", buffer);
		
		// EPS: Motherboard Temperature & Daughterboard Temperature
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE308, 0x00, buffer, 4);		// 12V Bus Current
		fprintf(fp, "Motherboard Temperature: %f\n", buffer);
		eps.cmd(static_cast<uint8_t>(EPSComm::GET_TELEMETRY), 0xE388, 0x00, buffer, 4);		// 12V Bus Current
		fprintf(fp, "Daughterboard Temperature: %f\n", buffer);
	}
	
	//send file to Transceiver, need to write this
	Send2Transceiver(fp);
	
	fclose(fp);
}

// QUERY PAYLOAD2()
void Query_P2()
{
	Payload2 P2;
	uint8_t command = 0x00; 	//Get Sun Sensor Values
	int readLength;
	int value1, value2, value3;
		
	FILE *fp;
	uint8_t buffer[6];
	
	if ( (fp = fopen("TelemetryBeacon.txt", "a+")) == NULL)
	{
		fprintf(stderr, "Error opening file.");
	}	
	else
	{
		fprintf("PAYLOAD 2 DATA:\n\n");
			
		P2.cmd(command, buffer, readLength*2);  
		
		// Each value received is a two byte int; all values received are put into one buffer
		value1 = ((value1 | buffer[1]) << 8) | buffer[0];
		value2 = ((value2 | buffer[3]) << 8) | buffer[2];
		value3 = ((value3 | buffer[5]) << 8) | buffer[4];
			
		fprintf(fp, "Sun sensors: \n");
		fprintf(fp, "Value 1: %f\n", value1);
		fprintf(fp, "Value 2: %f\n", value2);
		fprintf(fp, "Value 3: %f\n", value3);
	}
	
	//send file to Transceiver, need to write this
	Send2Transceiver(fp);
	
	fclose(fp);
}
