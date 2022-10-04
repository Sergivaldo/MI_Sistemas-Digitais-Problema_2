#include <stdio.h>

struct gpio_pin{
        int func_reg_ofst;
        int func_pin_ofst;
        int pin_number;    
};

enum state{OFF,ON};

extern void nanoSleep(void);
extern void memory_map(void);
extern void GPIODirectionOut(int reg_offset, int pin_offset);
extern void GPIOTurn(int pin_offset,int state);

void delay(int millis){
	for(int i=0;i<millis;i++){
		nanoSleep();
	}
}

void set_gpio_to_out(struct gpio_pin pin){
	GPIODirectionOut(pin.func_reg_ofst,pin.func_pin_ofst);
}

void set_gpio_value(struct gpio_pin pin, enum state pin_state){
	int state = pin_state;
	GPIOTurn(pin.pin_number,state);
}

int  main(){
}
