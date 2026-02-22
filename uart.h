void UART1_config(void);
void UART1_Txchr(char);
char UART1_Rxchr(void);
void UART1_Txstr(char *);

void UART1_config()
{
	PINSEL0 |= 0x00050000;
	U1LCR    = 0x83;
	U1DLL    = 97;
	U1DLM    = 0;
	U1LCR    = 0x03;
}

void UART1_Txchr(char TxD)
{
	while(!((U1LSR>>5)&1));
	U1THR = TxD;
}

char UART1_Rxchr(void)
{
	while(!(U1LSR&1));
	return U1RBR;
}

void UART1_Txstr(char *str)
{
	while(*str)
		UART1_Txchr(*str++);
}

