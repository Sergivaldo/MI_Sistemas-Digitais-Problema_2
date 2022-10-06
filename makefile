all: main

main:main.c gpio.o lcd.o
  gcc -o output main main.c gpio.o lcd.o
  
lcd.o:lcd.s
  as -g -o lcd.o ldc.s
  
gpio.o:gpio.s
  as -g -o gpio.o gpio.s


