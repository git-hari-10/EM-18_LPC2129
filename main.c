#include<lpc21xx.h>
#include "lcd.h"
#include "homeScr.h"
#include "v_init.h"
#include "uart.h"
#include "string.h"

char BASEID[3][13] = {
	"0600680EE989",
	"05005351C6C1",
	"060067F1C656"
	};
unsigned char voted[3] ={0,0,0};  
unsigned char index = 0;
unsigned char received = 0;
char VOTERID[15];

/*            UART1_ISR             */

void VOTER_ID_ISR(void) __irq    
{
	VOTERID[index++] = U1RBR;
	if(index==12)
	{
		VOTERID[index] = '\0';
		received = 1;
		index=0;
	}
	VICVectAddr = 0;
}
/* ______________ X _______________ */

/*            MAIN FUNC()           */
int main()
{
	unsigned char i;
	unsigned char valid = 0;
	unsigned char found = 0;
	UART1_config();
	
	U1FCR = 0x07;
	U1IER = 0x01; 
	
	/*    SLOT-0 -> UART1    */ 
	VICIntSelect  = 0;
	VICVectCntl0  = (0x20)|7;
	VICVectAddr0  = (unsigned long)VOTER_ID_ISR;
	VICIntEnable |= 1<<7;
	/*  ________ x ________  */
	
	
	lcd_init();
	homeScr();

	while(1) // MAIN CODE          
	{
		if(RES==0)
		{
			result_calc();
			dmk = admk = tvk = 0;
			while(RES==0); 
        	delay_ms(150);
			homeScr();
		}	
		if(received)
		{
			received = 0;
			UART1_Txstr(VOTERID);
			valid = 0;
			found = 0;
			for(i=0;i<3;i++)
			{
			    if(!strcmp(VOTERID, BASEID[i]))
			    {
			        found = 1;
			
			        if(voted[i] == 0)
			        {
			            voted[i] = 1;
			            valid = 1;
			        }
			        else
			        {
			            lcd_cmd(0x01);
						lcd_cmd(0x80);lcd_str(" ------------------ ");
			            lcd_cmd(0xC0);lcd_str("       ALREADY      ");
						lcd_cmd(0x94);lcd_str("        VOTED       ");
						lcd_cmd(0xD4);lcd_str(" ------------------ ");
			            delay_sc(3);
			        }
			        break;
			    }
			}
			
			if(valid)
			{
			    lcd_cmd(0x01);
			    lcd_cmd(0xC0);lcd_str(" [ ACCESS GRANTED ] ");
			    lcd_cmd(0x94);
			
			    for(i=0;i<20;i++)
			    {
			        lcd_write('=');
			        delay_ms(150);
			    }
			
			    votingInit();
			}
			else if(!found)
			{
			    lcd_cmd(0x01);
			    lcd_cmd(0x80);lcd_str(" ------------------ ");
			    lcd_cmd(0xC0);lcd_str("       INVALID      ");
			    lcd_cmd(0x94);lcd_str("       VOTERID      ");
			    lcd_cmd(0xD4);lcd_str(" ------------------ ");
			    delay_sc(3);
			}
			homeScr();
		}
	}
}

