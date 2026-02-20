#include<lpc21xx.h>
#include "lcd.h"
#include "uart.h"
#include "string.h"
#define EINT0 1<<16

char TAG[15];
char *RFID = "HARISH123450";
unsigned char received = 0;

/* _________ UART1_ISR __________ */

void VOTER_ID_ISR(void) __irq    
{
	static unsigned char x = 0;
	TAG[x++] = U1RBR;
	if(x==12)
	{
		TAG[x] = '\0';
		received = 1;
		x=0;
	}
	VICVectAddr = 0;
}
/* ______________________________ */

void projTopicScroll(unsigned char *);

int main()
{
	unsigned char T[] = "                MODERN VOTING MACHINE USING LPC2129 & RFID      ";
	IODIR0 = EINT0;
	lcd_init();
	UART1_config();
	
	U1FCR = 0x07;
	U1IER = 0x01; // ENABLE UART1_Rx INTERRUPT
	
	/*___ SLOT-0 -> UART1 ___*/ 
	VICIntSelect  = 0;
	VICVectCntl0  = (0x20)|7;
	VICVectAddr0  = (unsigned long)VOTER_ID_ISR;
	VICIntEnable |= 1<<7;
	/*  ________ x ________  */
	
	while(1)              
	{	
		projTopicScroll(T);
		if(received)
		{
			received = 0;
			if(!strcmp(TAG,RFID))
				IOSET0   = EINT0;
		}
	}
}

/* ________ PROJECT TITLE ________*/

void projTopicScroll(unsigned char *s)
{
	static unsigned char i=0;
	unsigned char j;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	for(j=0;j<16;j++)
		lcd_write(s[i+j]);
	i++;
	lcd_cmd(0xC0);
	lcd_str("==> SCAN  ID <==");
	delay_ms(150);
	
	if(s[i+15] == '\0') 
		i=0;
}
/* ________________________________ */

