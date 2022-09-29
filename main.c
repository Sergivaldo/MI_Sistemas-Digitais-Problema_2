#include <stdio.h>
#define OFF 0;
#define ON 1;
struct pin{
        int ofst_reg_fsel;
        int ofst_pin_fsel;
        int ofst_pin_st_clr;    

};


extern memory_map();
extern GPIODirectionOut(struct pin *p);
extern GPIOTurn(struct pin *p,int value);

int  main(){

	struct pin pin5;
	pin5.ofst_reg_fsel = 0;
	pin5.ofst_pin_fsel = 18;
	pin5.ofst_pin_st_clr= 6;

	memory_map();
	GPIODirectionOut(&pin5);
	GPIOTurn(&pin5,OFF);	
}

