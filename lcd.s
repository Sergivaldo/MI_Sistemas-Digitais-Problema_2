.macro load_pin pin, reg_offset, pin_offset
        
.endm

@ Da um pulso no pino enable o ligando e desligando.
.macro enable
        GPIOTurn e, #0
        nanoSleep time1ms

        GPIOTurn e,#1
        nanoSleep time1ms

        GPIOTurn e, #0
        nanoSleep time1ms
        .ltorg
.endm

@ Seta todos os pinos do lcd como saída.
.macro setOut
        GPIODirectionOut e
        GPIODirectionOut rs
        GPIODirectionOut d7
        GPIODirectionOut d6
        GPIODirectionOut d5
        GPIODirectionOut d4
.endm

@ Macro para setar o modo de operação do display para 4 bits.
.macro fset

        
.endm

@ Macro que define se o cursor será exibido e piscará e se o display será ligado 
.macro display d,c,b

.endm

@ Define o modo de entrada do display. Faz com que o cursor ou display desloque
@ para esquerda ou direita quando um caractere é escrito
.macro entrymode i_d, s

.endm


@ Macro para limpar o display LCD.

.macro clearLcd

.endm

.macro write

.endm

@ Macro para escrever um caractere no display
@
@ Parâmetros
@ hex - Hexadecimal do caractere a ser escrito

.macro command value
        MOV R6, \value

        GPIOTurn rs, #1

        MOV R0,#7
        BL get_bit
        GPIOTurn d7, R1

        MOV R0,#6
        BL get_bit
        GPIOTurn d6, R1

        MOV R0,#5
        BL get_bit
        GPIOTurn d5, R1

        MOV R0,#4
        BL get_bit
        GPIOTurn d4, R1

        enable

        GPIOTurn rs, #1

        MOV R0,#3
        BL get_bit
        GPIOTurn d7, R1


        MOV R0,#2
        BL get_bit
        GPIOTurn d6, R1


        MOV R0,#1
        BL get_bit
        GPIOTurn d5, R1


        MOV R0,#0
        BL get_bit
        GPIOTurn d4, R1

        enable
        .ltorg
.endm

lcd_init:
	
	command #0x01
	command #0x20
	command #0x20
	command #0x20
	command #0x20
	command #0x0f
	
	BX LR
	
@ branch que pega um bit do valor hexadecimal do caractere
get_bit:
        MOV R2,#1 @ Move 1 para o registrador R0
        LSL R2,R0 @ Desloca para esquerda o valor em R2 para a posição do bit passado em R0
        AND R1, R6,R2 @ Realiza a operação lógica and para que seja pego apenas o bit desejado
        LSR R1,R0 @ Desloca para o bit menos significativo o bit da posição desejada

        BX LR
	
@ Macro usada para deslocar o display sempre que chamado.
.macro cursor_display_shift sc, rl 

.endm

.data

rs:
	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear
e:
	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear
d4: 
	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear
d5:
	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear 
d6:
	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear
d7:
 	.word 0 @ offset para selecionar o registrador de função
	.word 0 @ offset do pino no registrador de função
	.word 0 @ offset do pino no registrador de set e clear
