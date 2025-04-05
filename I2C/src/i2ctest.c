/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

/****************************************************************************
 *   $Id:: i2ctest.c 3662 2012-10-31 19:47:02Z usb00423                     $
 *   Project: NXP LPC8xx I2C example
 *
 *   Description:
 *     This file contains I2C test modules, main entry, to test I2C APIs.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 
 * Permission to use, copy, modify, and distribute this software and its 
 * documentation is hereby granted, under NXP Semiconductors' 
 * relevant copyright in the software, without fee, provided that it 
 * is used in conjunction with NXP Semiconductors microcontrollers. This 
 * copyright, permission, and disclaimer notice must appear in all copies of 
 * this code.
****************************************************************************/
#include "LPC8xx.h"			/* LPC8xx Peripheral Registers */
#include "type.h"
#include "lpc8xx_i2c.h"
#include "lpc8xx_mrt.h"

volatile uint8_t I2CMasterTXBuffer[I2C_BUFSIZE];
volatile uint8_t I2CMasterRXBuffer[I2C_BUFSIZE];
volatile uint8_t I2CSlaveTXBuffer[I2C_BUFSIZE];
volatile uint8_t I2CSlaveRXBuffer[I2C_BUFSIZE];
//volatile uint32_t I2CMonBuffer[I2C_MONBUFSIZE];
volatile uint32_t I2CReadLength, I2CWriteLength;

extern volatile uint32_t mrt_counter;


void i2c_write( char addr, const char *data, char size );
void delay( uint32_t d );
void write_register( char i2c_addr, char reg_addr, char data );
char wave( int x );
void pca9956a_operation( void );


/*****************************************************************************
** Function name:		Main
**

** Descriptions:		Main entry
** parameters:			None
** Returned value:		int
**
*****************************************************************************/
int main (void)
{                       /* Main Program */
	uint32_t	i;

	SystemCoreClockUpdate();

	/*
	 * Initialize I2C pin connect
	 */

	//	SDA = pin8(PIO0_0), SCL = pin5(PIO0_1)

	/* Pin Assign 8 bit Configuration */
	/* I2C0_SDA */
	LPC_SWM->PINASSIGN7 = 0x00ffffffUL;
	/* I2C0_SCL */
	LPC_SWM->PINASSIGN8 = 0xffffff01UL;

	LPC_IOCON->PIO0_0	|= ((0x1<<10) | 0x2);	/* Enable pseudo open drain */
	LPC_IOCON->PIO0_1	|= ((0x1<<10) | 0x2);	/* Enable pseudo open drain */

	/* Pin Assign 1 bit Configuration */
	/* SWCLK */
	/* SWDIO */
	LPC_SWM->PINENABLE0 = 0xfffffff3UL;

	/* Enable I2C clock */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
	/* Toggle peripheral reset control to I2C, a "1" bring it out of reset. */
	LPC_SYSCON->PRESETCTRL &= ~(0x1<<6);
	LPC_SYSCON->PRESETCTRL |= (0x1<<6);

	I2C_TimeoutInit( LPC_I2C, TIMEOUT_VALUE );

	LPC_I2C->INTENSET = STAT_SLVPEND;
	I2C_MstInit(LPC_I2C, I2C_FMODE_PRE_DIV, CFG_MSTENA, 0x00);

	/* Get device ID register */
	for ( i = 0; i < I2C_BUFSIZE; i++ )	/* clear buffer */
	{
		I2CMasterTXBuffer[i] = 0;
		I2CMasterRXBuffer[i] = 0;
		I2CSlaveTXBuffer[i] = 0;
		I2CSlaveRXBuffer[i] = 0;
	}

	I2C_CheckIdle( LPC_I2C );

	pca9956a_operation();		//	loop forever inside of this function

	return 0;
}


const 	char	data[]	= {
	    0x80,                							//  Command
	    0x00, 0x05,                                     //  MODE1, MODE2
	    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,				//  LEDOUT[5:0]
	    0x80, 0x00,                                     //  GRPPWM, GRPFREQ
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  PWM[7:0]
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  PWM[15:8]
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  PWM[23:16]
	    0x08, 0x08, 0x10, 0x08, 0x08, 0x10, 0x08, 0x08, //  IREF[7:0]
	    0x10, 0x08, 0x08, 0x10, 0x08, 0x08, 0x10, 0x08, //  IREF[15:8]
	    0x08, 0x10, 0x08, 0x08, 0x10, 0x08, 0x08, 0x10, //  IREF[23:16]
};



void pca9956a_operation( void )
{
	char	leds[ 25 ];
	int		i;
	int		j;
	float	b;

	init_mrt( 0x8000 );

	while ( 1 )
	{
		i2c_write( 0x02, data, sizeof( data ) );

		for ( j = 0; j < 3; j++ )
		{
			b	= 255.0;

			for ( i = 0; i < 50; i++ )
			{
				write_register( 0x02, 0x3F, (char)b );
				b	*= 0.9;
				delay( 5 );
			}
		}

		for ( i = 0; i < (24 * 0xFF); i += 8 )
		{
			if ( i & 0xFF )
				write_register( 0x02, 0xA + (i >> 8), i & 0xFF );
			else
				i2c_write( 0x02, data, sizeof( data ) );

			delay( 2 );
		}

		leds[ 0 ]	= 0xA | 0x80;

#define	COLOR_PERIOD	768
#define	COLOR_PHASE		(COLOR_PERIOD / 3)
#define	COLOR_OFFSET	(COLOR_PERIOD / 24)

#if 0
		for ( k = 0; k < 12; k++ )
		{
			for ( j = 0; j < 256; j++ )
			{
				for ( i = 1; i <= 24; i += 3 )
				{
					leds[ i + ((k + 0) % 3) ]	= 255 - j;
					leds[ i + ((k + 1) % 3) ]	= j;
					leds[ i + ((k + 2) % 3) ]	= 0;
				}
				i2c_write( 0x02, leds, sizeof( leds ) );
				delay( 2 );
			}
		}
#else

		for ( j = 0; j < (COLOR_PERIOD * 1); j++ )
		{
			for ( i = 1; i <= 24; i += 3 )
			{
				leds[ i + 0 ]	= wave( j  + (COLOR_PHASE * 0) );
				leds[ i + 1 ]	= wave( j  + (COLOR_PHASE * 1) );
				leds[ i + 2 ]	= wave( j  + (COLOR_PHASE * 2) );
			}
			i2c_write( 0x02, leds, sizeof( leds ) );
			delay( 2 );
		}
#endif

		for ( j = 0; j < (COLOR_PERIOD * 4); j++ )
		{
			for ( i = 1; i <= 24; i += 3 )
			{
				leds[ i + 0 ]	= wave( j + (COLOR_OFFSET * i) + (COLOR_PHASE * 0) );
				leds[ i + 1 ]	= wave( j + (COLOR_OFFSET * i) + (COLOR_PHASE * 1) );
				leds[ i + 2 ]	= wave( j + (COLOR_OFFSET * i) + (COLOR_PHASE * 2) );
			}
			i2c_write( 0x02, leds, sizeof( leds ) );
			delay( 2 );
		}
	}
}

char wave( int x )
{
	x	%= 768;

	return ( (x < 256) ? x : ((512 <= x) ? 0 : 255 - (x - 256)) );
}

void write_register( char i2c_addr, char reg_addr, char data )
{
	char		tmp[ 2 ];

	tmp[ 0 ]	= reg_addr;
	tmp[ 1 ]	= data;

	i2c_write( i2c_addr, tmp, 2 );
}

void delay( uint32_t d )
{
	mrt_counter	= 0;

	while ( mrt_counter < d )
		;
}

void i2c_write( char addr, const char *data, char size )
{
	I2C_MstSend( LPC_I2C, addr, (uint8_t *)data, size );
}



/******************************************************************************
**                            End Of File
******************************************************************************/
