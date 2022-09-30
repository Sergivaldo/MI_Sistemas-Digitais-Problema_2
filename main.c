#include <stdio.h>
#define OFF 0;
#define ON 1;

struct pin{
        int reg_func_ofst;
        int pin_func_ofst;
        int pin_st_clr_ofst;    

};

extern void memory_map(void);
extern void GPIODirectionOut(int reg_offset, int pin_offset);
extern void GPIOTurn(int pin_offset,int value);

int  main(){
	memory_map();
	GPIODirectionOut(0,18);
	GPIOTurn(6,OFF);	
}

