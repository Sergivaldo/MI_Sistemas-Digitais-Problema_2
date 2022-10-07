#include<stdio.h>
#include<stdint.h>

extern void memory_map(void);
extern void lcd_init(void);
extern void delay(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write(uint8_t c);

void counter(){
   int num = 0x39;
   for (int i =9;i<=0;i--){
      write(num);
      delay_millis(1000);
      clear_lcd();
      num--;
   }
}

void delay_millis(int millis){
  for(int i =0; i<millis;i++){
    delay();
  }
}


void main(){
  memory_map();
  set_out();
  lcd_init();
 
  counter();
}

