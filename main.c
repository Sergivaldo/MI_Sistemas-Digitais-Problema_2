#include <stdio.h>
#define OFF 0
#define ON 1

struct gpio_pin{
        int reg_func_ofst;
        int pin_func_ofst;
        int pin_number;    

};

extern void nanoSleep(void);
extern void memory_map(void);
extern void GPIODirectionOut(int reg_offset, int pin_offset);
extern void GPIOTurn(int pin_offset,int value);


void delay(int millis){
	for(int i=0;i<millis;i++){
		nanoSleep();
	}
}

void set_pin_direction(struct gpio_pin pin){
	GPIODirectionOut(pin.reg_func_ofst,pin.pin_func_ofst);
}

void set_pin_value(struct gpio_pin pin,int value){
	GPIOTurn(pin.pin_number,value);
}

int  main(){
	memory_map();
}
