#include  "stdio.h"
#include  "scMonitor.h"

static char signon[] =  " Southern Cross Monitor ";

// monitor variables
static unsigned char* MODE = VARBLS+57; 
static unsigned int* ADDRESS = VARBLS+59;

main()
{
 volatile unsigned char keyPress;
 sc_InitBitBang((unsigned int)B4800);	//initialise bit bang serial port
 sc_SendStr(sc_PCBType()); //board type, SC-1 or TEC-1F
 sc_SendStr(signon);
 sc_SendStr(sc_Version()); // software version
 sc_SendStr("\r\n");
 sc_SendStr(sc_KbdType());	//keyboard type, Hardware (MM74C923N installed) or Software
 sc_SendStr(" Keyboard\r\n");
 
 *MODE = 0x80;  //set data mode (bit 7 high) enable beep (bit 6 low)
 *ADDRESS = 0x2000;	//initial address displayed
 
 while(1)
 {	 
	 sc_SystemCall(UPDATE);  //update the current displayed address and data
	 sc_SystemCall(SKEYRL);	//scan display until key release 
	 
	 keyPress = sc_ScanUntilKey(); //scan display until a key is pressed
     sc_SystemCall(BEEP); // beep if enabled
     
	  switch(keyPress & 0x1f)  // handle the keyboard input
	  {
		case 0x10: // function key
				  sc_SendStr("Test scMonitor functions\r\n");
				  SystemCallTest();
		          break;
		case 0x11: // address key
                  //change the data entry mode from address to data and vica-versa
                  if(*MODE & 0x80) *MODE &= 0x7f;
                   else *MODE |= 0x80;
				  break;
		case 0x12: // increment address
					*ADDRESS+=1;
					break;
		case 0x13: // decrement address
					*ADDRESS-=1;
					break;
		default: // the rest are hex keys
		     // address entry or data entry mode?
		     if(*MODE & 0x80)  // data mode - shift hex key into lsn of data
			      *(unsigned char*) *ADDRESS = *(unsigned char*) *ADDRESS << 4  | keyPress & 0x0f;
		       else // address mode - shift hex key into lsn of address 
		          *ADDRESS = (unsigned int) *ADDRESS << 4 | (unsigned int)keyPress & 0x000f;
		    break;
	  }
 }
} 
