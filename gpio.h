#ifndef gpio_h   
#define gpio_h

extern void nanoSleep(void);
extern void memory_map(void);
extern void GPIODirectionOut(uint8_t reg_offset, uint8_t pin_offset);
extern void GPIOTurn(uint8_t pin_offset,uint8_t state);

#endif
