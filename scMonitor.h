#ifndef _SCMHEADER
#define _SCMHEADER

// Southern Cross Monitor Version 1.8

#define BOTRAM 0x2000	//bottom of SRAM
#define TOPRAM 0x3fff	//top of SRAM

#define VARBLS TOPRAM-0xff	//Monitor Variables
#define BUFFER VARBLS-0x0100	//general purpose buffer
#define TXBUFFER BUFFER-0x0100	//transmit buffer (reserved for interrupt serial comms)
#define RXBUFFER TXBUFFER-0x0100	//receive buffer (reserved for interrupt serial comms)
#define ISTACK RXBUFFER		//stack
#define RAMEND TOPRAM-0x0400	//end of 'user' RAM
#define RAMSRT BOTRAM	//start of 'user' RAM

// Southern Cross Monitor System Calls 

#define MAIN	0	//restart monitor - no paramaters
#define VERS	1	//returns monitor version
#define DISADD	2	//address -> display buffer
#define DISBYT	3	//data -> display buffer
#define CLRBUF	4	//clear display buffer - no parameters
#define SCAND	5	//scan display - no parameters
#define CONBYT	6	//byte -> display code
#define CONVHI	7	//hi nybble -> display code
#define CONVLO	8	//lo nybble - > display code
#define SKEYIN	9	//scan display until key press
#define SKEYRL	10	//scan display until key release - no parameters
#define KEYIN	11	//wait for key press
#define KEYREL	12	//wait for key release - no parameters
#define MENU	13	//select entry from menu
#define CHKSUM	14	//calculate checksum
#define MUL16	15	//16 bit multiply
#define RAND	16	//generate random number
#define INDEXB	17	//index into byte table
#define INDEXW	18	//index into word table
#define MUSIC	19	//play music table
#define TONE	20	//play a note
#define BEEP	21	//key entry beep - no parameters
#define SKATE	22	//scan 8x8 display
#define TXDATA	23	//bit banged transmit serial byte
#define RXDATA	24	//bit banged receive serial byte
#define ASCHEX	25	//ascii code -> hex
#define WWATCH	26	//write to smart watch
#define RWATCH	27	//read from smart watch
#define ONESEC	28	//one second delay using smartwatch
#define RLSTEP	29	//relay sequencer
#define DELONE	30	//one second delay loop
#define SCANKEY	31	//scan the keyboard
#define INTELH	32	//receive intel hex file
#define SPLIT	33	//separate a byte into nybbles
#define SNDMSG	34	//send zero terminated string to bit banged serial port
#define BITASC	35	//convert a byte into an ascii string of ones and zeroes
#define WRDASC	36	//convert a word to ascii
#define BYTASC	37	//convert a byte to ascii
#define NYBASC	38	//convert a nybble to ascii
#define PCBTYP	39	//returns board type, sc or tec-1f
#define PRNTSZ	40	//inline bit banged serial print string
#define KBDTYP	41	//returns keyboard type
#define UPDATE	42	//update display and mode decimal point segments
#define VARRAM	43	//return base variable address
#define	SERINI	44	//initialise bit bang serial port

// bit bang baud rate constants
#define	B300	0x0220	// 300 BAUD
#define B1200	0x0080	// 1200 BAUD
#define B2400	0x003F	// 2400 BAUD
#define B4800	0x001B	// 4800 BAUD
#define B9600	0x000B	// 9600 BAUD
#define SAME	0x0000	// unchanged

// 
int putchar(int);
int getchar(void);

// prototypes
void sc_SystemCall(unsigned char) __naked;
unsigned char* sc_Version(void) __naked __sdcccall(1);
unsigned char* sc_KbdType(void) __naked __sdcccall(1);
unsigned char* sc_PCBType(void) __naked __sdcccall(1);

void sc_InitBitBang(unsigned int) __naked;
void sc_TxChar(unsigned char) __naked;
unsigned char sc_RxChar(void) __naked;
void sc_SendStr(const unsigned char*) __naked __sdcccall(1);

void sc_DisplayAddress(unsigned int) __naked;
void sc_DisplayData(unsigned char) __naked;

unsigned char sc_ScanUntilKey(void) __naked;
unsigned char sc_WaitKey(void) __naked;
unsigned char sc_ScanKey(void) __naked;

unsigned char* sc_Nybble2Asc(unsigned char,unsigned char*) __naked __sdcccall(1);
unsigned char* sc_Byte2Asc(unsigned char,unsigned char*) __naked __sdcccall(1);
unsigned char* sc_Word2Asc(unsigned int,unsigned char*) __naked __sdcccall(1);
unsigned char* sc_Bit2Asc(unsigned char,unsigned char*) __naked __sdcccall(1);
void sc_Music(unsigned char*)__naked __sdcccall(1);
void sc_Scan8x8(unsigned char*)__naked __sdcccall(1);
unsigned int sc_Varram(void) __naked __sdcccall(1);
unsigned int sc_Rand(void) __naked __sdcccall(1);
void sc_Tone(unsigned char,unsigned int) __naked;


#endif

