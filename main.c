#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdint.h>
// Comandos de requisição
#define GET_NODEMCU_SITUATION 0x03
  
#define GET_ANALOG_INPUT_VALUE 0x04
#define GET_DIGITAL_INPUT_VALUE 0x05
#define SET_ON_NODEMCU_LED 0x06
#define SET_OFF_NODEMCU_LED 0x07
#define TRUE 1
// Endereços
#define ADDR_D0 0xD0
#define ADDR_D1 0xD1
#define ADDR_D2 0xD2
#define ADDR_D3 0xD3
#define ADDR_D4 0xD4
#define ADDR_D5 0xD5
#define ADDR_D6 0xD6
#define ADDR_D7 0xD7

extern void memory_map(void);
extern void init_lcd(void);
extern void clear_lcd(void);
extern void write_char(unsigned char c);

void lcd(){
	memory_map();
	init_lcd();
	clear_lcd();
}

void print_lcd(unsigned char c[]){
        int len = strlen(c);
        
        for(int i=0;i<len;i++){
                write_char(c[i]);
        }
}

int uart0_filestream = -1;

void delay(int millis){
    clock_t start_time = clock();
    while (clock() < start_time + millis)
    {}
}

void uart_configure(){
    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1)
    {
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void serialFlush ()
{
  tcflush (uart0_filestream, TCIOFLUSH) ;
}

void serialPutchar (const unsigned char c)
{
  write (uart0_filestream, &c, 1) ;
}

void serialGetString(){
	static unsigned char rx_buffer[6];
	int rx_length = -1;
    	if (uart0_filestream != -1){
		while(rx_length == -1){
			rx_length = read(uart0_filestream, (void*)rx_buffer, 6);		//Filestream, buffer to store in, number of bytes to read (max)
			if (rx_length == 0)
			{
			    printf("Não há bytes para serem lidos.");
			}
			
		}
		clear_lcd();
		print_lcd("Analogico: ");
		print_lcd(rx_buffer);
	}
}


unsigned char serialGetChar(){
    static unsigned char rx_buffer[1];
    int rx_length = -1;
    if (uart0_filestream != -1)
    {
	while(rx_length == -1){
		rx_length = read(uart0_filestream, (void*)rx_buffer, 1);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length == 0)
		{
		    printf("Não há bytes para serem lidos.");
		}
		
	}
		    clear_lcd();
		    print_lcd("Digital: ");
		    write_char(0x30 + rx_buffer[0]);
	}
	
}

void main(){ 
  lcd();
  uart_configure(); // Inicia as configurações do uart.
  int input = 0;
	while(TRUE){
		
		printf("Envie um comando:\n");
		printf("1 - Solicitar a situação do NODEMCU\n");
		printf("2 - Solicitar o valor da entrada analógica\n");
		printf("3 - Solicitar o valor de uma entrada digital\n");
		printf("4 - Acender led da NODEMCU\n");
		printf("5 - Apagar led do NODEMCU\n");
		printf("\n\n");
		scanf("%d",&input);
		switch(input){
			case 1:
				serialPutchar(GET_NODEMCU_SITUATION);
				break;
			case 2:
				serialFlush();
				serialPutchar(GET_ANALOG_INPUT_VALUE);
				serialGetString();
				break;
			case 3:
				serialFlush();
				serialPutchar(GET_DIGITAL_INPUT_VALUE);
				serialPutchar(ADDR_D0);
			        serialGetChar();
				break;
			case 4:
				serialFlush();
				serialPutchar(SET_ON_NODEMCU_LED);
				clear_lcd();
				print_lcd("Led Ligado");
				break;
			case 5:
				serialFlush();
				serialPutchar(SET_OFF_NODEMCU_LED);
				clear_lcd();
				print_lcd("Led Desligado");
				break;
		}
     
                
	}
}  
