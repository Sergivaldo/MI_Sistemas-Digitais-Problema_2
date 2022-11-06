<a id="inicio"></a>
## Mi Sistemas digitais - Problema 2

Este documento mostra os detalhes de implementação de um protótipo de
sistema de sensoriamento genérico.

Esse sistema é o prosseguimento do protótipo do sistema digital baseado em um processador ARM.

Nesta etapa, o projeto consiste em um sistema que detecta até 32 sensores genéricos através da nodeMCU e faz a comunicação serial com a RaspBerry para fazer a exibição das informações no display LCD.

### Membros do grupo
  **Jacob Santana**<br>
  **Sergivaldo Junior**
## Seções
&nbsp;&nbsp;&nbsp;[**1.** Ferramentas utilizadas](#secao1)

&nbsp;&nbsp;&nbsp;[**2.** Informações do computador usado para os testes](#secao2)

&nbsp;&nbsp;&nbsp;[**3.** Configuração e instalação do projeto](#secao3)

&nbsp;&nbsp;&nbsp;[**4.** Testes realizados](#secao4)

&nbsp;&nbsp;&nbsp;[**5.** Testes realizados](#secao5)

&nbsp;&nbsp;&nbsp;[**6.** Limitações da solução desenvolvida](#secao6)

&nbsp;&nbsp;&nbsp;[**7.** Materiais utilizados no desenvolvimento](#secao7)

<a id="secao1"></a>
## Ferramentas utilizadas

Para o processo de desenvolvimento do sistema foram utilizadas as seguintes ferramentas:

**Arduino IDE**: É uma plataforma eletrônica de código aberto baseada em hardware e software fáceis de usar. Nesta plataforma é possível realizar o envio do código desenvolvido na linguagem C, para a nodeMCU esp8266 através da comunicação via wifi.

**GNU Makefile**: O makefile determina automaticamente quais partes de um programa grande precisam ser recompiladas e emite comandos para compilar novamente. Inicialmente deve ser escrito um arquivo chamado makefile que descreve os relacionamentos entre os arquivos do programa e fornece comandos para atualizar cada arquivo. Em um programa, normalmente, o arquivo executável é atualizado a partir de arquivos de objeto, que por sua vez são feitos pela compilação de arquivos de origem
Uma vez que existe um makefile adequado, cada vez que alguns arquivos de origem são alterados, apenas o comando “make” é suficiente para realizar todas as recompilações necessárias.

**GNU Binutils**: O ***Binutils*** é uma coleção de ferramentas binárias. Neste software se encontra o GNU assembler (as) que foi utilizado para montar os códigos assembly, além do  GNU linker(ld) que combina vários arquivos objetos, realoca seus dados e vincula referências de símbolos, fazendo por último a criação do executável do programa.

**GDB**: É o depurador de nível de fonte GNU que é padrão em sistemas linux (e muitos outros unix). O propósito de um depurador como o GDB é permitir ver o que está acontecendo “dentro” de outro programa enquanto ele é executado, ou o que outro programa estava fazendo no momento em que travou. Ele pode ser usado tanto para programas escritos em linguagens de alto nível como C e C++ quanto para programas de código assembly.

**QEMU** e **CPUlator**: O ***QEMU*** implementa um emulador de processador, permitindo uma virtualização completa de um sistema PC dentro de outro. O ***CPUlator*** também é um emulador online de processador que conta ainda com a simulação de alguns periféricos como leds, botões e dip switches. Os dois foram utilizados para simular a arquitetura ARM. No primeiro foi utilizado uma simulação do ARMv6, a mesma arquitetura da máquina utilizada, o que ajudou bastante em pequenos códigos que não necessitavam da utilização das GPIOs. O segundo emula o ARMv7, apesar de ser uma arquitetura diferente da utilizada nos testes, foi bem útil para práticar o uso da linguagem.


<a id="secao2"></a>
## Informações dos computadores usados para os testes

Os computadores utilizados para os testes foram a Raspberry PI Zero W, e a NodeMCU Esp8266. 

Características da Raspberry PI Zero W utilizada:

- Chip Broadcom BCM2835, com processador ARM1176JZF-S 1GHz single core;
- O processador conta com arquitetura ARMv6.
- 512MB de memória LPDDR2 SDRAM;

Características da NodeMCU Esp8266 utilizada:

- NodeMCU é formado por um ESP12E, o qual ainda possui um ESP8266EX em seu interior.
- 13 pinos GPIO, 10 canais PWM, I2C, SPI, ADC, UART e 1-Wire.
- Tem uma antena interna.

<a id="secao3"></a>
## Configuração e instalação do projeto
