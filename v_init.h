#define DMK  ((IOPIN0>>20)&1)
#define ADMK ((IOPIN0>>21)&1)
#define TVK  ((IOPIN0>>22)&1)
#define RES  ((IOPIN0>>19)&1)

unsigned char dmk=0,admk=0,tvk=0;

void result_calc(void);
void votingInit(void);
void display_init(void);

void votingInit()
{
	display_init();
	while(1)
	{
		if(DMK==0)
		{
			dmk++;
			delay_ms(150);
			while(DMK==0);
			return;
		}
		else if(ADMK==0)
		{
			admk++;
			delay_ms(150);
			while(ADMK==0);
			return;
		}
		else if(TVK==0)
		{
			tvk++;
			delay_ms(150);
			while(TVK==0);
			return;
		}	
	}
}

void display_init()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);lcd_str(">> SELECT PARTIES <<");
	lcd_cmd(0xC0);lcd_str("[1] DMK       ");
	lcd_cmd(0x94);lcd_str("[2] ADMK      ");
	lcd_cmd(0xD4);lcd_str("[3] TVK       ");
}

void result_calc()
{
	lcd_cmd(0x01);
	lcd_cmd(0xC0);lcd_str(" CALCULATING RESULT ");
	lcd_cmd(0x9B);lcd_write('.');delay_ms(500);
	lcd_cmd(0x9C);lcd_write('.');delay_ms(500);
	lcd_cmd(0x9D);lcd_write('.');delay_ms(500);
	lcd_cmd(0x9E);lcd_write('.');delay_ms(500);
	lcd_cmd(0x9F);lcd_write('.');delay_ms(500);
	lcd_cmd(0xA0);lcd_write('.');delay_ms(500);
	lcd_cmd(0x01);
	lcd_cmd(0x80);lcd_str("--------------------");
	lcd_cmd(0xC8);
	((dmk>admk)&&(dmk>tvk))  ? lcd_str("DMK")  :
	((admk>dmk)&&(admk>tvk)) ? lcd_str("ADMK") : 
	((tvk>dmk)&&(tvk>admk))  ? lcd_str("TVK")  : lcd_str(" NO");
	lcd_cmd(0x94);lcd_str("       WINNER       ");
	lcd_cmd(0xD4);lcd_str("--------------------");
	delay_sc(5);
}

