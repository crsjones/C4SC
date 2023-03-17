
#include "stdio.h"

// Southern Cross Monitor Version 1.8 System Calls

#include "SCMonitor.h"

// system calls without passed or returned parameters
void sc_SystemCall(unsigned char call) __naked
{
(void) call;
 __asm
    ld c,a
	rst  0x30
    ret
 __endasm;
}

// return software version string
unsigned char* sc_Version(void) __naked __sdcccall(1)
{
__asm
	ld	c,#VERS
	rst	0x30
	ex	de,hl
	ret
__endasm;
}

// return keyboard type string
unsigned char* sc_KbdType(void) __naked __sdcccall(1)
{
__asm
	ld	c,#KBDTYP
	rst	0x30
	ex  de,hl
	ret
__endasm;
}

// return PCB type string
unsigned char* sc_PCBType(void) __naked __sdcccall(1)
{
__asm
	ld	c,#PCBTYP
	rst	0x30
	ex	de,hl
	ret
__endasm;
}

// initialise serial bit bang
void sc_InitBitBang(unsigned int BAUD) __naked
{
(void) BAUD;
__asm
	ld	c,#SERINI
	rst 0x30
	ret
__endasm;
}
// send a serial character
int putchar(int value)
{
  sc_TxChar((int)value);
  return value;
}

// transmit a serial character
void sc_TxChar(unsigned char value) __naked
{
	(void) value;
 __asm
	push	ix
    ld c,#TXDATA
    rst 0x30
	pop	ix
    ret
 __endasm;
 
}
// wait for a serial character
int getchar(void)
{
 return (int)sc_RxChar();
}

// wait for a serial character
unsigned char sc_RxChar(void) __naked
{
  __asm
  ld c,#RXDATA
  push ix
  rst 0x30
  pop ix
  ret
  __endasm;
}

// send zero terminated string to serial port
void sc_SendStr(const unsigned char* sz) __naked __sdcccall(1)
{
(void) sz;
 __asm
	push ix
    ld c,#SNDMSG
	rst  0x30
	pop ix
    ret
 __endasm;
}

// put address in display buffer
void sc_DisplayAddress(unsigned int Address) __naked __sdcccall(1)
{
  (void) Address;
 __asm
    ld c,#DISADD
	rst  0x30
    ret
 __endasm;

}
// put data in display buffer
void sc_DisplayData(unsigned char Data) __naked
{
  (void) Data;
__asm
   ld c,#DISBYT
   rst 0x30
   ret
 __endasm;
 
}

// scan display until key press
unsigned char sc_ScanUntilKey(void) __naked
{
  __asm
  ld c,#SKEYIN
  rst 0x30
  ret
  __endasm;
}
// wait for key press
unsigned char sc_WaitKey(void) __naked
{
  __asm
  ld c,#KEYIN
  rst 0x30
  ret
  __endasm;
}
// check for a key press
unsigned char sc_ScanKey(void) __naked
{
  __asm
  ld c,#SCANKEY
  rst 0x30
  ret
  __endasm;
}
// convert a Nybble to ascii
unsigned char* sc_Nybble2Asc(unsigned char byte,unsigned char *sz) __naked __sdcccall(1)
{
(void) byte;
(void) sz;
__asm
    ex	de,hl
    ld c,#NYBASC
	rst 0x30
	ex	de,hl
    ret
 __endasm;
}
// convert a byte to ascii
unsigned char* sc_Byte2Asc(unsigned char byte,unsigned char *sz) __naked __sdcccall(1)
{
(void) byte;
(void) sz;
__asm
    ex	de,hl
    ld c,#BYTASC
	rst  0x30
	ex	de,hl
    ret
 __endasm;
}

// convert a word to ascii
unsigned char* sc_Word2Asc(unsigned int Word,unsigned char *sz) __naked __sdcccall(1)
{
(void) Word;
(void) sz;
__asm
	ex	de,hl
    ld c,#WRDASC
	rst  0x30
	ex	de,hl
    ret
 __endasm;
}
// convert a byte to a binary string
unsigned char* sc_Bit2Asc(unsigned char Bits,unsigned char *sz) __naked __sdcccall(1)
{
(void) Bits;
(void) sz;
__asm
    ex	de,hl
    ld c,#BITASC
	rst  0x30
	ex	de,hl
    ret
 __endasm;
}
// play music data
void sc_Music(unsigned char *sz)__naked __sdcccall(1)
{
(void) sz;	
__asm
    ld c,#MUSIC
	rst  0x30
    ret
 __endasm;
	
}	
// scan 8x8 display
void sc_Scan8x8(unsigned char *sz)__naked __sdcccall(1)
{
(void) sz;	
__asm
	ex	de,hl
    ld c,#SKATE
	rst  0x30
    ret
 __endasm;
	
}
// return variable base address
unsigned int sc_Varram(void) __naked __sdcccall(1)
{
__asm
    ld c,#VARRAM
	rst  0x30
	ex	de,hl
	ret
__endasm;
}

// return random number
unsigned int sc_Rand(void) __naked __sdcccall(1)
{
__asm   
    ld c,#RAND
	rst  0x30
	ex	de,hl
	ret
__endasm;
}
// play a note
void sc_Tone(unsigned char period2,unsigned int time2) __naked __sdcccall(1)
{
  (void) period2;
  (void) time2;
__asm
	ex	de,hl 
   ld c,#TONE
   rst 0x30
   ret
__endasm;
} 
