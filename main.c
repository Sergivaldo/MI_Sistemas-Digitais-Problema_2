#include <stdio.h>
#define OFF 0
#define ON 1

struct pin{
        int reg_func_ofst;
        int pin_func_ofst;
        int pin_st_clr_ofst;    

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

int  main(){
	memory_map();
	GPIODirectionOut(0,18);
	
	for(int i=0;i<10;i++){
		 GPIOTurn(6,ON);
	         delay(1000);
       		 GPIOTurn(6,OFF);
       		 delay(1000);    
		
	}	
}
