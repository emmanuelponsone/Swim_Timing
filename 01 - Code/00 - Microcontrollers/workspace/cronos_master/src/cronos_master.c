/*----------------------------------------------------------------------------
 *      Name:   main.c
 *      Purpose: Programa principal para la unidad maestra del sistema cronos
 *      Version: V0.1
 *--------------------------------------------------------------------------*/

#include "LPC13xx.h"
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "cdc.h"
#include "cdcuser.h"
#include "vcomdemo.h"
#include "string.h"
#include "uart.h"

#include "clkconfig.h"
#include "gpio.h"
#include "config.h"
#include "timer32.h"

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)
#define     EN_USBREG       (1<<14)
#define 	NUM_BYTES		8
#define		OK				1
#define		HAB_OK			2
#define 	NLAPS_OK		3
#define		DESC			0
#define 	VIRGEN			0
#define		PC_OK	 		1
#define		SET	 			2
#define		ADQ	 			3
#define		RESET 			4
#define		FIN 			5
#define		UI_FIN 			0
#define		UI_RUN 			1

extern volatile uint32_t UARTCount;
volatile uint32_t auxiliar,resto;
extern volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint8_t  Buffer[BUFSIZE], estado[8];
unsigned char aux,start,laps,inicializacion,comienzo,hab_andrv[8];
struct DATOS info;
struct TIME tiempos;
union CUENTAS pepe;


union CUENTAS
{
	uint32_t cuenta[1];
	unsigned char bytes[4];

};


struct DATOS
{
unsigned char estado[NUM_BYTES];
unsigned char linea1[NUM_BYTES];
unsigned char linea2[NUM_BYTES];
unsigned char linea3[NUM_BYTES];
unsigned char linea4[NUM_BYTES];
unsigned char linea5[NUM_BYTES];
unsigned char linea6[NUM_BYTES];
unsigned char linea7[NUM_BYTES];
unsigned char linea8[NUM_BYTES];
uint32_t cuenta_andv[8];
unsigned char pos[8];
};

struct TIME
{
unsigned char min[3];
unsigned char seg[2];
unsigned char cent[2];
};

/*----------------------------------------------------------------------------
 ACTUALIZA LOS DATOS DESDE LAS UNIDADES INDIVIDUALES
 *---------------------------------------------------------------------------*/
void Actualizar(void)
{
int n;
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='A';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}http://www.e-torredebabel.com/Historia-de-la-filosofia/Filosofiacontemporanea/Sartre/Principal-Sartre.htm
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
	strcpy(info.linea1,"DESCON  ");
	info.cuenta_andv[0]=9999999;
	estado[0]=DESC;
	UARTCount = 0;
	}
else
	{

	for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

	info.cuenta_andv[0]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

	if(UARTBuffer[n]==UI_RUN)
		{
		estado[0]=UI_RUN;
		}
	if(UARTBuffer[n]==UI_FIN || hab_andrv[0]=='0')
		{
		estado[0]=UI_FIN;
		}

	UARTCount = 0;

	//Comienza el armado del ascii a partir de las cuentas recibidas
	aux=pepe.cuenta[0]/1000000;
	resto=pepe.cuenta[0]-1000000*aux;
	info.linea1[0]=aux+0x30;
	aux=resto/100000;
	info.linea1[1]=aux+0x30;
	resto=resto-100000*aux;
	aux=resto/10000;
	info.linea1[2]=aux+0x30;
	resto=resto-10000*aux;
	aux=resto/1000;
	info.linea1[3]=aux+0x30;
	resto=resto-1000*aux;
	aux=resto/100;
	info.linea1[4]=aux+0x30;
	resto=resto-100*aux;
	aux=resto/10;
	info.linea1[5]=aux+0x30;
	resto=resto-10*aux;
	info.linea1[6]=resto+0x30;
	info.linea1[7]=' ';

	}
/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='B';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */

if(comienzo==SET)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}


UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea2,"DESCON  ");
		info.cuenta_andv[1]=9999999;
		estado[1]=DESC;
		UARTCount = 0;
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}


		if(UARTBuffer[n]==UI_RUN)
			{
			estado[1]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[1]=='0')
			{
			estado[1]=UI_FIN;
			}

		UARTCount = 0;

		info.cuenta_andv[1]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea2[0]=aux+0x30;
		aux=resto/100000;
		info.linea2[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea2[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea2[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea2[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea2[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea2[6]=resto+0x30;
		info.linea2[7]=' ';
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='C';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;
//delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea3,"DESCON  ");
		info.cuenta_andv[2]=9999999;
		estado[2]=DESC;
		UARTCount = 0;

	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

		if(UARTBuffer[n]==UI_RUN)
			{
			estado[2]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[2]=='0')
			{
			estado[2]=UI_FIN;
			}

		UARTCount = 0;

		info.cuenta_andv[2]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea3[0]=aux+0x30;
		aux=resto/100000;
		info.linea3[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea3[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea3[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea3[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea3[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea3[6]=resto+0x30;
		info.linea3[7]=' ';
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='D';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;
//delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea4,"DESCON  ");
		info.cuenta_andv[3]=9999999;
		estado[3]=DESC;
		UARTCount = 0;

	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

		if(UARTBuffer[n]==UI_RUN)
			{
			estado[3]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[3]=='0')
			{
			estado[3]=UI_FIN;
			}

		UARTCount = 0;

		info.cuenta_andv[3]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea4[0]=aux+0x30;
		aux=resto/100000;
		info.linea4[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea4[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea4[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea4[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea4[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea4[6]=resto+0x30;
		info.linea4[7]=' ';
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='E';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea5,"DESCON  ");
		info.cuenta_andv[4]=9999999;
		estado[4]=DESC;
		UARTCount = 0;

	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}
		if(UARTBuffer[n]==UI_RUN)
			{
			estado[4]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[4]=='0')
			{
			estado[4]=UI_FIN;
			}

		UARTCount = 0;


		info.cuenta_andv[4]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea5[0]=aux+0x30;
		aux=resto/100000;
		info.linea5[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea5[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea5[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea5[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea5[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea5[6]=resto+0x30;
		info.linea5[7]=' ';
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='F';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
		UARTBuffer[0]='S';
	}

if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//delay(1000000);

if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea6,"DESCON  ");
		info.cuenta_andv[5]=9999999;
		estado[5]=DESC;
		UARTCount = 0;

	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

		if(UARTBuffer[n]==UI_RUN)
			{
			estado[5]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[5]=='0')
			{
			estado[5]=UI_FIN;
			}

		UARTCount = 0;

		info.cuenta_andv[5]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea6[0]=aux+0x30;
		aux=resto/100000;
		info.linea6[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea6[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea6[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea6[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea6[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea6[6]=resto+0x30;
		info.linea6[7]=' ';
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='G';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
		UARTBuffer[0]='S';
	}

if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//delay(1000000);
if(UARTCount!=sizeof(uint32_t)+1)
	{
		strcpy(info.linea7,"DESCON  ");
		info.cuenta_andv[6]=9999999;
		estado[6]=DESC;
		UARTCount = 0;

	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

		if(UARTBuffer[n]==UI_RUN)
			{
			estado[6]=UI_RUN;
			}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[6]=='0')
			{
			estado[6]=UI_FIN;
			}

		UARTCount = 0;

		info.cuenta_andv[6]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea7[0]=aux+0x30;
		aux=resto/100000;
		info.linea7[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea7[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea7[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea7[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea7[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea7[6]=resto+0x30;
		info.linea7[7]=' ';
	}

/****************************************************************/
//Envio ID
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='H';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;
//Envio laps
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]=laps;
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;
//Envio estado
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
if(comienzo==SET)
	{
		UARTBuffer[0]='S';
	}

if(comienzo==ADQ)
	{
	UARTBuffer[0]='S';
	}
if(comienzo==PC_OK)
	{
	UARTBuffer[0]='R';
	}
if(comienzo==FIN)
	{
	UARTBuffer[0]='W';
	}
if(comienzo==VIRGEN)
	{
	UARTBuffer[0]='W';
	}
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

//delay(1000000);

if(UARTCount!=sizeof(uint32_t)+1)
	{
	strcpy(info.linea8,"DESCON  ");
	info.cuenta_andv[7]=9999999;
	estado[7]=DESC;
	UARTCount = 0;
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

		if(UARTBuffer[n]==UI_RUN)
		{
		estado[7]=UI_RUN;
		}
		if(UARTBuffer[n]==UI_FIN || hab_andrv[7]=='0')
		{
		estado[7]=UI_FIN;
		}

		UARTCount = 0;

		info.cuenta_andv[7]=pepe.cuenta[0];	//Guardo la cuenta sin desglosar

		aux=pepe.cuenta[0]/1000000;
		resto=pepe.cuenta[0]-1000000*aux;
		info.linea8[0]=aux+0x30;
		aux=resto/100000;
		info.linea8[1]=aux+0x30;
		resto=resto-100000*aux;
		aux=resto/10000;
		info.linea8[2]=aux+0x30;
		resto=resto-10000*aux;
		aux=resto/1000;
		info.linea8[3]=aux+0x30;
		resto=resto-1000*aux;
		aux=resto/100;
		info.linea8[4]=aux+0x30;
		resto=resto-100*aux;
		aux=resto/10;
		info.linea8[5]=aux+0x30;
		resto=resto-10*aux;
		info.linea8[6]=resto+0x30;
		info.linea8[7]=' ';
	}
aux=0;
for(n=0;n<8;n++)
{
	if(estado[n]==UI_FIN)
	{
		aux++;
	}
}
if(aux==8)		//Todas las unidades terminaron
{
	comienzo=FIN;
}
}

/*----------------------------------------------------------------------------
 Initializes the VCOM port.
 Call this function before using VCOM_putchar or VCOM_getchar
 *---------------------------------------------------------------------------*/
void VCOM_Init(void) {

  CDC_Init ();
}

/*----------------------------------------------------------------------------
  Envia los 32 bytes del array buffer por USB hacia la PC
 *---------------------------------------------------------------------------*/
void Enviar_Datos_USB(unsigned char *puntero)
{
aux=0;
while(aux!='S')
  {
	  Lee_USB();					//Espera a que se de comienzo a la tx
  }
CDC_DepInEmpty = 0;
USB_WriteEP (CDC_DEP_IN, (unsigned  char *)puntero,NUM_BYTES);
}

/*----------------------------------------------------------------------------
 *Lee un caracter desde USB
 *---------------------------------------------------------------------------*/
void Lee_USB(void)
{
static char serBuf [32];
int  numBytesToRead, numBytesRead, numAvailByte,n;

CDC_OutBufAvailChar (&numAvailByte);
if (numAvailByte > 0)
{
	numBytesToRead = numAvailByte > 32 ? 32 : numAvailByte;
	numBytesRead = CDC_RdOutBuf (&serBuf[0], &numBytesToRead);
	aux=serBuf[0];											//El caracter recibido se guarda en aux
	if(inicializacion==0)
	{
	if(aux>='0')
		{
		start=NLAPS_OK;
		}
	if(aux=='S')
		{
		start=OK;
		}
	if(numBytesRead==8)	//Indica que se han recibido los estados de habilitacion de cada andarivel
		{
		for(n=0;n<8;n++)
		{
			hab_andrv[n]=serBuf[n];
		}
		}
	}

}

}
/*----------------------------------------------------------------------------
ORDENA LOS TIEMPOS E INDICA LA POSICION DE CADA ANDARIVEL
*---------------------------------------------------------------------------*/
void Ordenar()
{
	int i,k;
	uint32_t muleto;
	unsigned char aux;
	for(i=0;i<8;i++)
	{
		info.pos[i]=i+0x31;
	}

	for(i=1;i<8;i++)
	{
		for(k=0;k<8-i;k++)
		{
			if(info.cuenta_andv[k]>info.cuenta_andv[k+1])
			{
				muleto=info.cuenta_andv[k];
				info.cuenta_andv[k]=info.cuenta_andv[k+1];
				info.cuenta_andv[k+1]=muleto;
				aux=info.pos[k];
				info.pos[k]=info.pos[k+1];
				info.pos[k+1]=aux;
			}
		}
	}

}

/*----------------------------------------------------------------------------
  Main Program
 *---------------------------------------------------------------------------*/
int main (void) {
	  	/* Enable Timer32_1, IOCON, and USB blocks */
int m;
LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON | EN_USBREG);

init_timer32(0, TIME_INTERVAL);				//TIME_INTERVAL está en timer32.h. Leer los comentarios para definir la frecuencia
GPIOInit();
GPIOSetDir( 2, 0, 1 );
//P2.2: Boton de Comienzo
GPIOSetDir( PORT2, 2, 0 ); 					//Configura P2.0 como entrada
GPIOSetInterrupt( PORT2, 2, 1, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
GPIOIntEnable( PORT2, 2 );					//Habilita las interrupciones.

//P2.4: Boton de start
GPIOSetDir( PORT2, 4, 0 ); 					//Configura P2.0 como entrada
GPIOSetInterrupt( PORT2, 4, 0, 0, 0 ); 		//Ahora además de ser entrada, es de interrupcion.
//GPIOIntEnable( PORT2, 1 );					//Habilita las interrupciones.

enable_timer32(0);							//Habilita el timer.
GPIOSetValue( 2, 0, 0 );
USBIOClkConfig();
VCOM_Init();                              // VCOM Initialization
UARTInit(9600);
USB_Init();                               // USB Initialization
USB_Connect(TRUE);                        // USB Connect
while (!USB_Configuration) ;              // wait until USB is configured

strcpy(info.estado,"ESTADO  ");
comienzo=VIRGEN;
while (1)
	{			                               // Loop forever
	//Espero el numero de laps
	while(start!=NLAPS_OK)
		{
		Lee_USB();		  					//Espera a que se de comienzo a la tx
		}
	if(aux=='R')
	{
		comienzo=PC_OK;
	}
	else
	{
		laps=aux;
	}
	aux=0;
	strcpy(info.estado,"PCOK    ");
	if(comienzo==VIRGEN)
		{
		comienzo=PC_OK;
		}
	if(comienzo==SET)
		{
		strcpy(info.estado,"SET     ");
		}
	if(comienzo==ADQ)
		{
		strcpy(info.estado,"ADQ     ");
		}
	if(comienzo==FIN)
		{
		strcpy(info.estado,"FIN     ");
		}
	//Envio el flag para que continue el programa en la pc
	aux='C';
	CDC_DepInEmpty = 0;
	USB_WriteEP (CDC_DEP_IN, &aux,1);


	Actualizar();
	Ordenar();
/****************************************************************************
 * Comienzo indica el estado en el que se encuentra el sistema.
 *
 *		*-PC_OK: Indica que la PC envio el numero de laps y esta lista para comenzar
 *		*-SET: Indica que se presiono el boton de comienzo y se esta esperando a que el juez comience la
 *		competencia.
 *		*-ADQ: Indica que la competencia se ha iniciado y se esta llevando a cabo la adquisicion de tiempos.
 *		*-FIN: Indica que todas las UIs conectadas han finalizado la toma de tiempos.
 *		*-RESET: Indica que se ha reseteado el equipo. Esto se logra teniendo presionado por mas de
 *		dos segundos el boton de comienzo en la unidad central.
 *
 ****************************************************************************/
		aux='C';
		CDC_DepInEmpty = 0;
		USB_WriteEP (CDC_DEP_IN, &aux,1);
		Enviar_Datos_USB(&info.estado[0]);
		Enviar_Datos_USB(&info.linea1[0]);
		Enviar_Datos_USB(&info.linea2[0]);
		Enviar_Datos_USB(&info.linea3[0]);
		Enviar_Datos_USB(&info.linea4[0]);
		Enviar_Datos_USB(&info.linea5[0]);
		Enviar_Datos_USB(&info.linea6[0]);
		Enviar_Datos_USB(&info.linea7[0]);
		Enviar_Datos_USB(&info.linea8[0]);
		Enviar_Datos_USB(&info.pos[0]);
		GPIOIntEnable( PORT2, 2 );		//Vuelvo a habilitar la interrupcion del boton de comienzo.

		//}
	aux=0;
	start=0;
	} // end while
} // end main ()
