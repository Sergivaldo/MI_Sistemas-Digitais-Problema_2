#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

extern void memory_map(void);
extern void lcd_init(void);
extern void set_out(void);
extern void clear_lcd(void);
extern void write_char(unsigned char c);
extern void set_cursor(int pos);
extern void cgram_addr(int local);

extern void map_e(int reg,int pin_offset, int pin_num);
extern void map_rs(int reg,int pin_offset, int pin_num);
extern void map_d7(int reg,int pin_offset, int pin_num);
extern void map_d6(int reg,int pin_offset, int pin_num);
extern void map_d5(int reg,int pin_offset, int pin_num);
extern void map_d4(int reg,int pin_offset, int pin_num);

void lcd(int e,int rs, int d7,int d6,int d5, int d4);

void print_lcd(unsigned char c[]){

#endif
