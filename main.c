#include<stdio.h>

extern void memory_map(void);
extern void lcd_init(void);

void main(){
  memory_map();
  lcd_init();
}
