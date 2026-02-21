#include<lpc21xx.h>
#include "lcd.h"
#include "uart.h"
#include "string.h"
#define LED 1<<16

char TAG[15];
char *RFID = "ABCDEFGHIJKL";
unsigned char index = 0;
unsigned char received = 0;

/* _________ UART1_ISR __________ */

void VOTER_ID_ISR(void) __irq    
{
	TAG[index++] = U1RBR;
	if(index==12)
	{
		TAG[index] = '\0';
		received = 1;
		index=0;
	}
	VICVectAddr = 0;
}
/* ______________________________ */

void projTopic(void);

int main()
{
	IODIR0 |= LED;
	lcd_init();
	UART1_config();
	
	U1FCR = 0x07;
	U1IER = 0x01; 
	
	/*___ SLOT-0 -> UART1 ___*/ 
	VICIntSelect  = 0;
	VICVectCntl0  = (0x20)|7;
	VICVectAddr0  = (unsigned long)VOTER_ID_ISR;
	VICIntEnable |= 1<<7;
	/*  ________ x ________  */
	
	projTopic();

	while(1) // MAIN CODE          
	{	
		if(received)
		{
			received = 0;
			IOSET0   = LED;
			delay_ms(100);
			IOCLR0   = LED;
			if(!strcmp(TAG,RFID))
			{
				lcd_cmd(0x01);
				lcd_cmd(0xC0);lcd_str(" [ ACCESS GRANTED ] ");
				lcd_cmd(0x94);lcd_str(">>>>");delay_ms(200);lcd_str(">>>>");delay_ms(200);lcd_str(">>>>");delay_ms(200);lcd_str(">>>>");
			}
			else
			{
				lcd_cmd(0x01);
				lcd_cmd(0xC0);lcd_str("  ________________  ");
				lcd_cmd(0x94);lcd_str(" |  INVALID CARD  | ");
				delay_ms(500);
			}
			projTopic();
		}
	}
}

/* _______________ HOME SCREEN ______________*/

void projTopic()
{
	lcd_cmd(0x80);lcd_str("### VOTE MACHINE ###");
	lcd_cmd(0xC0);lcd_str("--------------------");
	lcd_cmd(0x94);lcd_str(">> [ SCAN  CARD ] <<");
	lcd_cmd(0xD4);lcd_str("      WAITING...    ");
}
/* _________________________________________ */

