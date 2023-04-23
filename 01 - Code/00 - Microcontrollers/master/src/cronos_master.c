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

#define     EN_TIMER32_1    (1<<10)
#define     EN_IOCON        (1<<16)
#define     EN_USBREG       (1<<14)
#define 	NUM_BYTES		9
#define		OK				1
#define		LAPS_OK			2
#define 	NLAPS_OK		3


extern volatile uint32_t UARTCount;
volatile uint32_t auxiliar,resto;
extern volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint8_t  Buffer[BUFSIZE];
unsigned char aux,start,laps,inicializacion;
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
};

struct TIME
{
unsigned char min[3];
unsigned char seg[2];
unsigned char cent[2];
};

/*----------------------------------------------------------------------------
 Initializes the VCOM port.
 Call this function before using VCOM_putchar or VCOM_getchar
 *---------------------------------------------------------------------------*/
void Actualizar(void)
{
int n;
LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='1';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea1,"DESCONEC");
	}
else
	{
	for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
	}
/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='2';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea2,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea2[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='3';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea3,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea3[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='4';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea4,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea4[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='5';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea5,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea5[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='6';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea6,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea6[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='7';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea7,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea7[7]=0;
	}

/****************************************************************/

LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
UARTBuffer[0]='8';
UARTSend( (uint8_t *)UARTBuffer, 1 );
UARTCount = 0;
LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;

delay(1000000);
if(UARTCount!=sizeof(uint32_t))
	{
		strcpy(info.linea8,"DESCONEC");
	}
else
	{
		for(n=0;n<4;n++)
		{
		pepe.bytes[n]=UARTBuffer[n];
		}

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
		info.linea8[7]=0;
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
  Reads character from USB buffer and writes to serial port buffer
 *---------------------------------------------------------------------------*/
void Lee_USB(void)
{
static char serBuf [32];
int  numBytesToRead, numBytesRead, numAvailByte;

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
	if(aux=='L')
		{
		start=LAPS_OK;
		}
	}

}

}

/*----------------------------------------------------------------------------
  Main Program
 *---------------------------------------------------------------------------*/
int main (void) {
	  	/* Enable Timer32_1, IOCON, and USB blocks */
LPC_SYSCON->SYSAHBCLKCTRL |= (EN_TIMER32_1 | EN_IOCON | EN_USBREG);

USBIOClkConfig();

VCOM_Init();                              // VCOM Initialization
UARTInit(9600);

USB_Init();                               // USB Initialization
USB_Connect(TRUE);                        // USB Connect
while (!USB_Configuration) ;              // wait until USB is configured

strcpy(info.estado,"ESTADO   ");
/*strcpy(info.linea1,"001:38:25");
strcpy(info.linea2,"001:38:26");
strcpy(info.linea3,"001:38:27");
strcpy(info.linea4,"001:38:28");
strcpy(info.linea5,"001:38:29");
strcpy(info.linea6,"001:38:30");
strcpy(info.linea7,"001:38:31");
strcpy(info.linea8,"001:38:32");*/

while (1)
	{			                               // Loop forever
	inicializacion=0;

	//Espero el numero de laps
	while(start!=NLAPS_OK)
		{
		Lee_USB();		  					//Espera a que se de comienzo a la tx
		}
	laps=aux;
	CDC_DepInEmpty = 0;						//Envio numero de laps recibido
	USB_WriteEP (CDC_DEP_IN, &aux,1);
	aux=0;

	//Espero el Ok para comenzar la transmicion de datos
	while(start!=OK)
		{
		Lee_USB();		  					//Espera a que se de comienzo a la tx
		}
	if(start==OK)
		{
		Actualizar();
		aux='C';
		CDC_DepInEmpty = 0;
		USB_WriteEP (CDC_DEP_IN, &aux,1);
		inicializacion=1;					//Indica el fin de la inicializacion en las coms con la pc.

		Enviar_Datos_USB(&info.estado[0]);
		Enviar_Datos_USB(&info.linea1[0]);
		Enviar_Datos_USB(&info.linea2[0]);
		Enviar_Datos_USB(&info.linea3[0]);
		Enviar_Datos_USB(&info.linea4[0]);
		Enviar_Datos_USB(&info.linea5[0]);
		Enviar_Datos_USB(&info.linea6[0]);
		Enviar_Datos_USB(&info.linea7[0]);
		Enviar_Datos_USB(&info.linea8[0]);
		}
	aux=0;
	start=0;
	} // end while
} // end main ()
