.equ setregoffset, 28 @ Offset do registrador de definição
.equ clrregoffset, 40 @ Offset do registrador de limpeza

.global memory_map
.global GPIODirectionOut
.global GPIOTurn

memory_map:

    LDR R0, =fileName
    MOV R1, #0x1b0
    ORR R1, #0x006
    MOV R2, R1
    MOV R7, #5     @ sys_open
    SWI 0

    MOV R4, R0
    LDR R5, =gpioaddr
    LDR R5, [R5]
    MOV R1, #4096     @ pagelen
    MOV R2, #(1 + 2)  @ prot read + prot write
    MOV R3, #1     @ map_shared
    MOV R0, #0
    MOV R7, #192   @ sys map
    SWI 0

    MOV R8, R0

    BX LR

GPIODirectionOut:

	LDR R2, [R8, R0]     @ Carrega em R1 o valor do endereço base em R8 com um offset que é o valor de R2
	MOV R4, #0b111       @ Mascara para limpar 3 bits
	LSL R4, R1           @ Faz um deslocamento em R0 com o valor que está em R3
	BIC R2, R4           @ Limpa os 3 bits da posição
	MOV R4, #1           @ Move 1 bit para R0
	LSL R4, R1           @ Faz um deslocamento em R0 com o valor que está em R3
	ORR R2, R4           @ Faz uma operação lógica ORR para adicionar na posição o valor 1
	STR R2, [R8, R0]     @ Armazena no endereço base em R8 com um offset que é o valor de R2, o valor de R1

	BX LR 


@ A branch GPIOTurn passa o valor 0 ou 1 para um pino o ativando ou limpando.
@ R1 - Valor (1 = ativar, 0 = limpar)
@ R3 - Pino (Pino que será setado)

GPIOTurn:

	@ R0 = pin offset 
	@ R1 = value

	MOV R2, R8  
	
	CMP R1,#0               
	ADDEQ R2, #clrregoffset 
	CMP R1,#1               
	ADDEQ R2, #setregoffset 

	MOV R4,#1                           
	LSL R4, R0              
	STR R4, [R2]            

	BX LR


.data

fileName: .asciz "/dev/mem" @ Caminho do arquivo para mapeamento da memória virtual
gpioaddr: .word 0x20200 @ Offset na memória física da área a ser mapeada
