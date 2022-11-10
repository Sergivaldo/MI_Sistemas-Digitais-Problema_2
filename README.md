<a id="inicio"></a>
## Mi Sistemas digitais - Problema 2



O Problema 2 da disciplina de sistemas digitais consiste em uma aplicação que faz o uso de até 8 sensores genéricos através da nodeMCU e faz a comunicação serial com a RaspBerry Pi, onde está solicita dados dos sensores e os exibe em um display LCD. 

Este documento mostra os detalhes de implementação de um protótipo de
sistema de sensoriamento genérico.

Esse sistema é o prosseguimento do protótipo do sistema digital baseado em um processador ARM.

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

#### Passo 1: Clonando o Projeto
Primeiramente, clone o repositório utilizando o
comando abaixo:

&nbsp;&nbsp;&nbsp; `git clone <repository-url>`

#### Passo 2: Gerando executável com o make
Abra o diretório em que o projeto foi salvo em seu computador, entre no terminal e execute o seguinte comando:

&nbsp;&nbsp;&nbsp;`make`

O código acima irá executar makefile responsável
por gerar os arquivos objetos do código assembly e compilar o código c, gerando um binário executável para
que a aplicação possa ser iniciada.

#### Passo 3: Iniciando o programa
Para iniciar o programa, use a seguinte instrução no terminal:

&nbsp;&nbsp;&nbsp;`sudo ./main`

<a id=""></a>
## Protocolo UART

Para fazer a comunicação serial entre as placas, foi feito um protocolo de comunicação com comandos de requisição e resposta. Dessa forma,
a Raspberry irá requisitar algo a NodeMCU que executará o que foi pedido e enviará de volta para Raspberry um código de resposta informando a ação que foi feita.

#### Comandos de requisição (Raspberry)

| **Código** 	|                 **Descrição**                 	|
|:----------:	|:---------------------------------------------:	|
|    0x03    	|      Solicita a situação atual do NodeMCU     	|
|    0x04    	|     Solicita o valor da entrada analógica     	|
|    0x05    	| Solicita o valor de uma das entradas digitais 	|
|    0x06    	|         Acendimento do led da NodeMCU         	|
|    0x07 	   |             Apagar led da NodeMCU 	            |

#### Comandos de resposta (NodeMCU)

| **Código** 	|          **Descrição**          	|
|:----------:	|:-------------------------------:	|
|    0x1F    	|       NodeMCU com problema      	|
|    0x00    	| NodeMCU funcionando normalmente 	|
|    0x01    	|   Estado da entrada analógica   	|
|    0x02    	|    Estado da entrada digital    	|
|    0x03    	|            Led ligado           	|
|    0x04    	|          Led Desligado          	|

## Endereços dos sensores 

Visto que o sistema deve ser capaz de suportar diversos sensores, uma forma de ter acesso a cada um destes foi fazendo endereços 
para que pudesse ser abstraído o tipo de sensor que irá ser utilizado e tornar a aplicação compatível com qualquer tipo de sensor digital, bastando apenas
especificar o endereço do sensor que está relacionado com uma porta digital. Foram feitos 8 endereços, ou seja, até 8 sensores podem ser adicionados a node mcu para serem usados.

| **Sensor** 	| **Endereço** 	|
|:----------:	|:------------:	|
|     D0     	|     0xD0     	|
|     D1     	|     0xD1     	|
|     D2     	|     0xD2     	|
|     D3     	|     0xD3     	|
|     D4     	|     0xD4     	|
|     D5     	|     0xD5     	|
|     D6     	|     0xD6     	|
|     D7     	|     0xD7     	|

## Metodologias e Técnicas aplicadas

Para fazer a utilização da comunicação serial das placas, foi necessário utilizar de alguns recursos, como por exemplo
a utilização da IDE do arduino para fazer a leitura das portas digitais e analógicas da NodeMCU, além do descarregamento do código na placa. Ainda foi utilizada
também a biblioteca **Serial** para que pudesse ser feita a transmissão de dados da NodeMCU para a RaspBerry Pi assim como o recebimento dos códigos de requisição para executar as tarefas.

Na Raspberry Pi também foi necessário fazer o uso de bibliotecas para utilizar as portas seriais do dispositivo, para isso foi utilizada a **termios**, com ela foi possível configurar o baudrate, quantidade de bits que seriam transmitidos e também fazer a escrita e leitura de dados na porta.

Para que a Raspberry pudesse receber um dado, foi utilizado de um loop onde este manteria a placa sempre lendo algo da porta serial até que um dado fosse recebido, tentando dessa forma garantir que caso algum dado seja enviado ele será lido. Na NodeMCU foi utilizado de uma técnica parecida, onde antes de tentar ler alguma informação, primeiramente é verificado se existe algum dado disponível para isso.


#### Leitura na porta serial da Raspberry Pi

```
// Lê a porta serial até que um dado seja recebido
while(rx_length == -1){
			rx_length = read(uart0_filestream, (void*)rx_buffer, 10);	
			if (rx_length == 0)
			{
			    printf("Não há bytes para serem lidos.");
			}
			
		}
```

#### Leitura na porta serial da NodeMCU

```
// Lê a porta serial se tiver algum dado disponível 
  if(Serial.available() > 0){
    String str = Serial.readString();
    byte_read = str[0];
    sensor_addr = str[1];
  }
 
```

## Testes realizados

#### Teste do led da NODEMCU

<iframe width="560" height="315" src="https://www.youtube.com/embed/7k6Zos6qosA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Limitações do projeto

#### O sistema pode ficar em loop infinito se não houver dados para serem lidos

Se não tiver dados para serem recebidos o sistema fica em loop infinito até receber algo na porta serial, já que a aplicação não irá parar de 
ler até que tenha informações disponíveis para serem consumidas. Esse pode ser considerado um problema bastante crítico, pois, caso essa situação ocorra
o programa irá ficar preso e nada mais será executado.

#### Valor aleatório vindo da requisição do sinal analógico

Por mais que a comunicação serial funcione e ao mover o potênciometro o valor mude, o dado que está vindo não é completo, somente um dígito 
vem correto, sendo o resto caracteres aleatórios. Portanto, nesta versão do protótipo não é possível obter o valor real do sensor analógico.

#### NodeMCU não retorna o status de funcionamento dos sensores

Outro limitação presente no programa é a falta de um retorno do status da NodeMCU indicando se os sensores estão funcionando corretamente ou não.
Desta forma, caso o sensor esteja com problema ou tiver algum sensor desconectado, o sistema não consegue identificar.
