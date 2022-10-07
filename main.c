#include<stdio.h>
#include<string.h>

extern void memory_map(void);
extern void lcd_init(void);
extern void delay(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write(int c);
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


void write_str(char c[]){
	int len = strlen(c);
	for(int i=0;i<len;i++){
		write(c[i]);
	}
}

void delay_millis(int millis){
        for (int i =0;i<millis;i++){ 
                delay();
        }
}

void main(){
   	lcd(1,25,21,20,16,12);
	write_str("MI - SD");	
}
