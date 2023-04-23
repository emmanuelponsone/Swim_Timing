// Code based on content of NXP gpio.c, to be found in LPC13xx_Lib project.
// Interrupts handlers have been extracted to this file so that the library
// project is then application independent.

#include "LPC13xx.h"			/* LPC13xx Peripheral Registers */
#include "gpio.h"
#include "config.h"

#define INTERVALO 	1000		//Para fosc= 100KHz. Divisor = 100
#define	ON	 		1
#define	OFF			0
#define MAX_LAPS	50
#define A			0
#define B			1


// CodeRed
unsigned int LEDvalue = LED_OFF;
extern volatile uint32_t centesimas,lap[MAX_LAPS],n_laps,cont_laps,lado,ultimo;

volatile uint32_t gpio2_counter = 0;
volatile uint32_t p2_1_counter  = 0;
volatile uint32_t contador  = 0;
unsigned int start=0,PM_A=0;PM_B=0,esperar_PT_A=0,esperar_PT_B=0,fin=0;

/*****************************************************************************
** Function name:		PIOINT2_IRQHandler
**
** Descriptions:		Use one GPIO pin(port2 pin1) as interrupt source
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void PIOINT2_IRQHandler(void)
{
uint32_t regVal;

regVal=0;
regVal = GPIOIntStatus( PORT2, 0 );
if ( regVal )
	{
	GPIOIntClear( PORT2, 0 );
	GPIOIntDisable( PORT2, 0 );
	start=ON;
	GPIOIntEnable( PORT2, 1 );					//Habilita las interrupciones de la base de tiempos
	}

regVal = GPIOIntStatus( PORT2, 1 );	//Chequea que P2.1 sea la que genero la int.
if ( regVal )
{
p2_1_counter++;
GPIOIntClear( PORT2, 1 );
if(p2_1_counter==INTERVALO)
  {
	centesimas++;
  }
}
/***********************************************************************/

//P2.2: Placa de toque A
regVal=0;
regVal = GPIOIntStatus( PORT2, 2 );
GPIOIntDisable( PORT2, 2 );	//Deshabilito las interrupciones de la placa.

if ( regVal )
	{
	GPIOIntClear( PORT2, 2 );
	if(start==ON && lado==A)
		{
		lado=B;
		GPIOIntDisable( PORT2, 3 );	//Deshabilito las interrupciones del pulsador manual.
		GPIOIntClear( PORT2, 3 );
		lap[cont_laps]=centesimas;
		ultimo=lap[cont_laps];
		cont_laps++;
		GPIOIntClear( PORT2, 4 );
		GPIOIntClear( PORT2, 5 );
		GPIOIntEnable( PORT2, 4 );	//Habilita las interrupciones de los pulsadores del otro lado de la pileta
		GPIOIntEnable( PORT2, 5 );
		if(cont_laps==n_laps)
			{
			fin=ON;
			}
		if(PM_A==ON)				//Se activó antes el pulsador manual que la placa de toque
			{
			PM_A=OFF;				//Se reinician ambos flags
			esperar_PT_A=OFF;			//Deja de esperar a la placa de toque
			contador=0;				//Reinicia el contador de espera
			}
		}
	}
else
	{
	GPIOIntEnable( PORT2, 2 );
	}
/***********************************************************************/

//P2.3: Pulsador Manual A. La unica forma de que entre aqui es si se pulsa antes de que se accione la PT_A
regVal=0;
regVal = GPIOIntStatus( PORT2, 3 );
GPIOIntDisable( PORT2, 3 );	//Deshabilito las interrupciones de la placa.

if ( regVal )
	{
	GPIOIntClear( PORT2, 3 );
	if(start==ON & lado==A)
		{
		PM_A=ON;		//Indica que el pulsador manual se accionó correctamente.
		lap[cont_laps]=centesimas;
		esperar_PT_A=ON;	//Comienza a correr el tiempo para esperar a la placa de toque
		}
	}
else
	{
	GPIOIntEnable( PORT2, 3 );
	}


/***********************************************************************/

//P2.4: Placa de toque B
regVal=0;
regVal = GPIOIntStatus( PORT2, 4 );
GPIOIntDisable( PORT2, 4 );	//Deshabilito las interrupciones de la placa.

if ( regVal )
	{
	GPIOIntClear( PORT2, 4 );

	if(start==ON & lado==B)
		{
		lado=A;
		GPIOIntDisable( PORT2, 5 );	//Deshabilito las interrupciones del pulsador manual.
		GPIOIntClear( PORT2, 5 );

		lap[cont_laps]=centesimas;
		ultimo=lap[cont_laps];
		cont_laps++;

		GPIOIntClear( PORT2, 2 );
		GPIOIntClear( PORT2, 3 );
		GPIOIntEnable( PORT2, 2 );	//Habilita las interrupciones de los pulsadores del otro lado de la pileta
		GPIOIntEnable( PORT2, 3 );
		if(cont_laps==n_laps)
			{
			fin=ON;
			}
		if(PM_B==ON)				//Se activó antes el pulsador manual que la placa de toque
			{
			PM_B=OFF;				//Se reinician ambos flags
			esperar_PT_B=OFF;			//Deja de esperar a la placa de toque
			contador=0;				//Reinicia el contador de espera
			}
		}
	}
else
	{
	GPIOIntEnable( PORT2, 4 );
	}
/***********************************************************************/

//P2.5: Pulsador manual B
regVal=0;
regVal = GPIOIntStatus( PORT2, 5 );
GPIOIntDisable( PORT2, 5 );	//Deshabilito las interrupciones de la placa.

if ( regVal )
	{
	GPIOIntDisable( PORT2, 5 );
	GPIOIntClear( PORT2, 5 );
	if(start==ON & lado==B)
		{
		GPIOIntDisable( PORT2, 5 );
		PM_B=ON;		//Indica que el pulsador manual se accionó correctamente.
		lap[cont_laps]=centesimas;
		esperar_PT_B=ON;
		}
	}
else
	{
	GPIOIntEnable( PORT2, 5 );
	}
/***********************************************************************/
  // CodeRed - extend original interrupt handler so as to toggle the LED state

  //GPIOSetValue( LED_PORT, LED_BIT, LEDvalue );

  return;
}

