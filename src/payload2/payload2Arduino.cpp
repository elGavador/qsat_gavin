#include <Wire.h>  // Library which contains functions to have I2C Communication
#define SLAVE_ADDRESS 8 // Define the I2C address to Communicate to Uno

#define RD_SUN_SENSORS 0x00
#define MODE_B	0x02

byte response["SIZE_OF_SUNSENSOR_DATA"]; // this data is sent to PI
int photoDiodeVals[3]; //create sun sensor data array
uint8_t command[1]; //command to be sent by the RPi
  
void setup() 
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); // this will begin I2C Connection with 0x40 address
  int channelA = 2;
  int LED = 1;
  int channelB = 3;
  int channelC = 4;
  int inhibitor = 5;
  int dot = 200;
  int dash = dot*3;
  int letterSpace = dot*3;
  int wordSpace = dot*7;
  int asciiA = 65;
  int asciiSpace = 32;
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}
void loop() 
{
  //On receiving data from the I2C bus (from the RPI), execute receiveEvent
  Wire.onReceive(receiveEvent);
  //if the RPI sends the command represented by 0x00 (arbitrary byte)
  if (command[0] == RD_SUN_SENSORS)
  {
    readSunSensors(photoDiodeVals); 
	memcpy(response, photoDiodeVals, sizeof(float)*3);
  }
  if (command[0] == MODE_B)//If Mode B blink morse code
  {
	blinkMorse();
  }
  delay(100);
  Wire.onRequest(sendData); // sendData is function called when Pi requests data from sun sensors
  memset(command,0,sizeof(command));  //reset command
  delay(1000);
}

void sendData()
{
  //Example data, to be replaced with the sun sensor data
  byte x = 0x21; //exclamation mark
  response[0]= x;
  Wire.write("DATA TO BE SENT (response)","LENGTH OF DATA TO BE SENT"); // return data to PI
}

void receiveEvent() 
{
  int i = 0;
  while(1 < Wire.available()) 
  {
    //read command sent from the raspberry pi
     command[i] = Wire.read();
     i++;
  }
}

void blinkMorse()
{
	String message = "QSDT";
	int redLED[3] = {0,0,0};
	int greenLED[3] = {0,0,1};
	int morseCode[26][5]{
		{1,2,0,0,0},
		{2,1,1,1,0},
		{2,1,2,1,0},
		{2,1,1,0,0},
		{1,0,0,0,0},
		{1,1,2,1,0},
		{2,2,1,0,0},
		{1,1,1,1,0},
		{1,1,0,0,0},
		{1,2,2,2,0},
		{2,1,2,0,0},
		{1,2,1,1,0},
		{2,2,0,0,0},
		{2,1,0,0,0},
		{2,2,2,0,0},
		{1,2,2,1,0},
		{2,2,1,2,0},
		{1,2,1,1,0},
		{1,1,1,0,0},
		{2,0,0,0,0},
		{1,1,2,0,0},
		{1,1,1,2,0},
		{1,2,2,0,0},
		{2,1,1,2,0},
		{2,1,2,2,0},
		{2,2,1,1,0}
	   };
	   delay(2000);
	   
	   if(LED == 0)
	   {
		digitalWrite(channelA, redLED[0]);
		digitalWrite(channelB, redLED[1]);
		digitalWrite(channelC, redLED[2]);
	   }
	   
	   else if(LED == 1)
	   {
		digitalWrite(channelA, greenLED[0]);
		digitalWrite(channelB, greenLED[1]);
		digitalWrite(channelC, greenLED[2]);
	   }
	   
	   digitalWrite(inhibitor, HIGH);
	   
	   for(int i = 0; i < message.length(); i++)
	   {
		int letter = message.charAt(i);
		for(int j = 0; j < 5; j++)
		{
		  if(morseCode[letter-asciiA][j] == 2)
		  {
			digitalWrite(inhibitor,LOW);
			delay(dash);
			digitalWrite(inhibitor,HIGH);
		  }
		  else if(morseCode[letter-asciiA][j] == 1)
		  {
			Serial.write(" dot ");
			digitalWrite(inhibitor,LOW);
			delay(dot);
			digitalWrite(inhibitor,HIGH);
		  }
		  else
		  {
			break;
		  }
		  
		  if(message.charAt(i+1)==asciiSpace && morseCode[letter-asciiA][j+1] != 2 && morseCode[letter-asciiA][j+1] != 1)
		  {
			delay(wordSpace);
		  }
		  else if(morseCode[letter-asciiA][j+1] != 2 && morseCode[letter-asciiA][j+1] != 1)
		  {
			delay(letterSpace);
		  }
		  else
		  {
			delay(dot);
		  }
	   }
	  }
	}
}

void readSunSensors(int *parray){
  for(int i = 0; i < 3; i ++){ //reads three photo diodes from three pins
    parray[i] = analogRead(i);
  }
}