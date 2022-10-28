#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <time.h>

// Comandos de requisição
#define GET_NODEMCU_SITUATION 0x03
  
#define GET_ANALOG_INPUT_VALUE 0x04
#define GET_DIGITAL_INPUT_VALUE 0x05
#define SET_ON_NODEMCU_LED 0x06
#define SET_OFF_NODEMCU_LED 0x07
#define TRUE 1
// Endereços
#define NOT_ADDRESS 0

extern void memory_map(void);
extern void lcd_init(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write_char(unsigned char c);
extern void set_cursor(int pos);
extern void cgram_addr(int local);
extern void map_e(int reg,int pin_offset, int pin_num);
extern void map_rs(int reg,int pin_offset, int pin_num);
extern void map_d7(int reg,int pin_offset, int pin_num);
extern void map_d6(int reg,int pin_offset, int pin_num);
extern void map_d5(int reg,int pin_offset, int pin_num);
extern void map_d4(int reg,int pin_offset, int pin_num);

void lcd(int e,int rs, int d7,int d6,int d5, int d4){
        memory_map();
        int reg= 4 * (e/10);
        int pin_offset = 3 *(e%10);
        map_e(reg,pin_offset,e);
        reg = 4 *(rs/10);
        pin_offset = 3*(rs%10);
        map_rs(reg,pin_offset,rs);
        reg = 4 *(d7/10);
        pin_offset = 3*(d7%10);
        map_d7(reg,pin_offset,d7);
        reg = 4 *(d6/10);
        pin_offset = 3*(d6%10);
        map_d6(reg,pin_offset,d6);
        reg = 4 *(d5/10);
        pin_offset = 3*(d5%10);
        map_d5(reg,pin_offset,d5);
        reg = 4 *(d4/10);
        pin_offset = 3*(d4%10);
        map_d4(reg,pin_offset,d4);
        set_out();
        lcd_init();
}



int uart0_filestream = -1;

void delay(int sec){
    int millis = sec * 1000;
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

void uart_receive_bytes (){

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
	    printf("%x",rx_buffer[0]);
        }
    }

}

void main(){
  lcd(1,25,21,20,16,12); 
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
				uart_send_bytes(GET_NODEMCU_SITUATION,NOT_ADDRESS);
				break;
			case 2:
				uart_send_bytes(GET_ANALOG_INPUT_VALUE,NOT_ADDRESS);
				break;
			case 3:
				uart_send_bytes(GET_DIGITAL_INPUT_VALUE,NOT_ADDRESS);
				break;
			case 4:
				uart_send_bytes(SET_ON_NODEMCU_LED,NOT_ADDRESS);
				uart_receive_bytes();
				break;
			case 5:
				uart_send_bytes(SET_OFF_NODEMCU_LED,NOT_ADDRESS);
				uart_receive_bytes();
				break;
		}
	}
}  
