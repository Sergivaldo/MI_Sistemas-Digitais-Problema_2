#include<stdio.h>
#include<string.h>

extern void memory_map(void);
extern void lcd_init(void);
extern void delay(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write(int c);
extern void offset_led(int reg,int offset_pin,int pin_num);
extern void on_led(void);
extern void off_led(void);
extern void out_led(void);

void led(int pin){
	int reg= 4 * (pin/10);
	int pin_offset = 3 *(pin %10);
        offset_led(reg,pin_offset,pin);
}

void write_str(char c[]){
	int len = strlen(c);
	for(int i=0;i<len;i++){
		write(c[i]);
	}
}

void main(){
   memory_map();
   led(6);
   out_led();
   off_led();
}
