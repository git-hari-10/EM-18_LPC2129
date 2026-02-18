void delay_sc(int);
void delay_ms(int);
void delay_us(int);

void delay_sc(int sec)  // SECONDS
{
	T0PR  = 15000000-1;
	T0TCR = 0x01;
	while(T0TC<sec);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_ms(int ms)  // MILLISECONDS
{
	T0PR  = 15000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_us(int us)  // MICROSECONDS
{
	T0PR  = 15-1;
	T0TCR = 0x01;
	while(T0TC<us);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

