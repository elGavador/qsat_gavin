enum class TRComm 	//transceiver commands
{
	//data frame command, send data with this byte as a header
	DATA = 0x00, 
	
	//setup/debug
	SET_FREQ = 0x20,
	GET_FREQ = 0x21,
	SET_POWER = 0x22,
	GET_POWER = 0x23,
	GET_RSSI = 0x24,
	PING = 0x25,
	DEBUG = 0x26,
	
	//correlation coef.
	SET_CC = 0x27, 
	GET_CC = 0x28,
	
	//set mode to transmit or receive
	SET_MODE = 0x29, 
	GET_MODE = 0x30
};

enum class EPSComm	//EPS commands
{
	//HOUSEKEEPING
	B_STATUS = 0x01,
	GET_LASTERR = 0x03,
	GET_VERSION = 0x04,
	GET_CHECKSUM = 0x05,
	GET_REVISION = 0x06,
	GET_TELEMETRY = 0x10,	//table 11-8: has addresses of "pins"
	
	//WATCHDOG
	GET_WDPERIOD = 0x20,
	SET_WDPERIOD = 0x21,
	RESET_WD = 0x22,
	
	//Number of RESETS
	GET_BROWNOUT_R = 0x31,		//Brownout resets
	GET_SOFT_R = 0x32,		//Software resets
	GET_MAN_R = 0x33,		//Manual resets
	GET_WD_R = 0x34,	//Watchdog
	
	//ALL PDMS
	ALL_PDMS_ON = 0x40,		
	ALL_PDMS_OFF = 0x41,
	GET_STATE_ACTUAL = 0x42,	
	GET_STATE_EXPECTED = 0x43,
	GET_STATE_INITIAL = 0x44,
	SET_STATE_INITIAL = 0x45,
	
	//PDM-N (specific switch)
	N_PDM_ON = 0x50,	
	N_PDM_OFF = 0x51,
	N_SET_STATE_ON = 0x52,	//INITIAL STATES
	N_SET_STATE_OFF = 0x53,
	N_GET_STATUS = 0x54,
	
	//PDM-N timer
	N_SET_TIMELIM = 0x60,
	N_GET_TIMELIM = 0x61,
	N_GET_TIMER = 0x62,

	//RESETS
	PCM_RESET = 0x70,
	MAN_RESET = 0x80
};

enum class P2Comm 	//Payload 2 commands
{
	QUERY_SUNSENSOR = 0x00;
	MODE_A = 0x01;
	MODE_B = 0x02;
	QUERY_MAGNETOMETER = 0x03;
};