#include<stdio.h>
#include<string.h>

extern void memory_map(void);
extern void lcd_init(void);
extern void delay(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write(int c);

void write_str(char c[]){
	int len = strlen(c);
	for(int i=0;i<len;i++){
		write(c[i]);
	}
}

void main(){
  memory_map();
  set_out();
  lcd_init();
  write_str(" Hello, World!");
}
