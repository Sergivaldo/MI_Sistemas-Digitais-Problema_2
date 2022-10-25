#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <time.h>
#include "lcd.h"

// Comandos de requisição
#define GET_NODEMCU_SITUATION 0x03
#define GET_ANALOG_INPUT_VALUE 0x04
#define GET_DIGITAL_INPUT_VALUE 0x05
#define SET_ON_NODEMCU_LED 0x06
#define SET_OFF_NODEMCU_LED 0x07
#define TRUE 1
int uart0_filestream = -1;

void delay(int sec){
    int millis = 1000*sec;

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

void uart_send_bytes(unsigned char command,unsigned char addr){
    //----- TX BYTES -----
    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = command;
    *p_tx_buffer++ = addr;

    if (uart0_filestream != -1)
    {
        int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
        if (count < 0)
        {
            printf("UART TX error\n");
        }
    }
}

unsigned char* uart_receive_bytes (){
    
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        static unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            //No data waiting
        }
        else
        {
            //Bytes received
            rx_buffer[rx_length] = '\0';
	    return rx_buffer;
        }
    }
    
}

void main(){
	
	lcd(1,25,21,20,16,12); 
	uart_configure(); // Inicia as configurações do uart.
	unsigned char input = 0;
	while(TRUE){
		printf("Envie um comando:");
		printf("1 - Solicitar a situação do NODEMCU");
		printf("2 - Solicitar o valor da entrada analógica");
		printf("3 - Solicitar o valor de uma entrada digital");
		printf("4 - Acender led da NODEMCU");
		printf("5 - Apagar led do NODEMCU");
		printf("\n\n");
		scanf("%c",&input);
		
		switch(input){
			case 1:
				uart_send_bytes(GET_NODEMCU_SITUATION,0);
				break;
			case 2:
				uart_send_bytes(GET_ANALOG_INPUT_VALUE,0);
				break;
			case 3:
				uart_send_bytes(GET_DIGITAL_INPUT_VALUE,0);
				break;
			case 4:
				uart_send_bytes(SET_ON_NODEMCU_LED,0);
				break;
			case 5:
				uart_send_bytes(SET_OFF_NODEMCU_LED,0);
				break;
			default:
				printf("Comando inválido");
				break;
		}
	}
}
