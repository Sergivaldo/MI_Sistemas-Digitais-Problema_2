#include <stdio.h>
#define OFF 0;
#define ON 1;

struct pin{
        int ofst_reg_fsel;
        int ofst_pin_fsel;
        int ofst_pin_st_clr;    

}pin6={0,18,6};

extern memory_map();
extern GPIODirectionOut(struct pin *p);
extern GPIOTurn(struct pin *p,int value);

int  main(){

	memory_map();
	GPIODirectionOut(&pin6);
	GPIOTurn(&pin6,OFF);	
}

