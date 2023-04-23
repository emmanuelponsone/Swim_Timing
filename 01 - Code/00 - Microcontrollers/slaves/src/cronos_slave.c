/*****************************************************************************
 *   uarttest.c:  UART test C file for NXP LPC13xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#include "LPC13xx.h"
#include "uart.h"
#include "clkconfig.h"
#include "gpio.h"
#include "config.h"
#include "timer32.h"

#define MAX_LAPS	50
#define A			0
#define B			1

unsigned char aux;
unsigned int cuentas;

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint8_t  Buffer[BUFSIZE];
volatile uint32_t centesimas  = 0,lap[MAX_LAPS],n_laps=5,cont_laps=0,lado=B,ultimo;
union CUENTAS
{
	uint32_t cuentas[1];
	unsigned char bytes[4];

};

union CUENTAS pepe;


int main (void) {
	  /* Basic chip initialization is taken care of in SystemInit() called
	   * from the startup code. SystemInit() and chip settings are defined
	   * in the CMSIS system_<part family>.c file.
	   */

/* NVIC is installed inside UARTInit file. */

unsigned char id;

//pepe.auxiliar[0]=123456;

init_timer32(0, TIME_INTERVAL);				//TIME_INTERVAL está en timer32.h. Leer los comentarios para definir la frecuencia
GPIOInit();
//P2.0: Boton de start
GPIOSetDir( PORT2, 0, 0 ); 					//Configura P2.1 como entrada
GPIOSetInterrupt( PORT2, 0, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
GPIOIntEnable( PORT2, 0 );					//Habilita las interrupciones.
//P2.1: pulsos de la base de tiempo
GPIOSetDir( PORT2, 1, 0 ); 					//Configura P2.1 como entrada
GPIOSetInterrupt( PORT2, 1, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
//GPIOIntEnable( PORT2, 1 );					//Habilita las interrupciones.
//P2.2: Placa de toque A
GPIOSetDir( PORT2, 2, 0 ); 					//Configura P2.1 como entrada
GPIOSetInterrupt( PORT2, 2, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
//GPIOIntEnable( PORT2, 2 );					//Habilita las interrupciones.
//P2.3: Pulsador Manual A
GPIOSetDir( PORT2, 3, 0 ); 					//Configura P2.1 como entrada
GPIOSetInterrupt( PORT2, 3, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
//GPIOIntEnable( PORT2, 3 );					//Habilita las interrupciones.
//P2.4: Placa de toque B
GPIOSetDir( PORT2, 4, 0 ); 					//Configura P2.1 como entrada
GPIOSetInterrupt( PORT2, 4, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
GPIOIntEnable( PORT2, 4 );					//Habilita las interrupciones.
//P2.5: Pulsador manual B
GPIOSetDir( PORT2, 5, 0 ); 					//Configura P2.5 como entrada
GPIOSetInterrupt( PORT2, 5, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
GPIOIntEnable( PORT2, 5 );					//Habilita las interrupciones.
enable_timer32(0);							//Habilita el timer.

UARTInit(9600);

id='2';


while (1)
	{				/* Loop forever */
	while(UARTBuffer[0]!=id)
		{
		UARTCount=0;
		}
	if(UARTBuffer[0]==id)
		{
			LPC_UART->IER = IER_THRE | IER_RLS;				/* Disable RBR */
			pepe.cuentas[0]=centesimas;
			UARTSend( (uint8_t *)pepe.bytes, sizeof(uint32_t) );
			UARTCount = 0;
			UARTBuffer[0]=0;
			LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */
		}
	} //FIN WHILE 1
}//FIN MAIN
