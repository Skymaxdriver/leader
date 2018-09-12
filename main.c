/*
 * nibo2onceagain.c
 *
 * Created: 12.09.2018 16:00:25
 * Author : skymax
 * __________________________
 * |   Port		|	LED		|	Displaybeleuchtung: PB6
 * |____________|___________|	Scheinwerfer:		PB5
 * |Grün: 0		|	PC0		|	Status Pwm:			PB7
 * |	1		|	PC1		|
 * |	2		|	PC2		|
 * |	3		|	PC3		|
 * |	4		|	PC4		|
 * |	5		|	PC5		|
 * |	6		|	PC6		|
 * |	7		|	PC7		|
 * |____________|___________|	|
 * |___________Rot:_________|
 * |	0		|	PE0		|
 * |	1		|	PE1		|
 * |	2		|	PE2		|
 * |	3		|	PE3		|
 * |	4		|	PE4		|
 * |	5		|	PE5		|
 * |	6		|	PE6		|
 * |	7		|	PE7		|
 * |____________|___________|
 */

#define headlights PB5
#define lcdbacklight PB6
#define statuspwm PB7
#define _NIBO_2_

#define F_CPU 16000000				// 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ks0108lib/KS0108.h"
#include "ks0108lib/graphic.h"
#include "ks0108lib/KS0108-AVR.c"

void initlight() // initialisiert die Ports & Pins die für die Beleuchtung verwendet werden
{
	DDRC=0xFF;				// grüne status Leds
	DDRE=0xFF;				// rote status Leds
	DDRB|= (1<<PB7);		// status leds
	DDRB|= (1<<PB6);		// lcd Beleuchtung
	DDRB|= (1<<PB5);		//headlights
}



void init() // allgemeine initialisierung der funktionen
{
	initlight();

}

int main(void)
{
	init();
	PORTB |= ((1<<PB7)|(1<<PB6)|(1<<PB5));
	PORTC = 0xFF;
	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_GoTo(0,0);
	GLCD_WriteString("+-------------------+");
	while (1)
	{
	}
}


