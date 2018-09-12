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

#define F_CPU 16000000				// 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initlight() // initialisiert die Ports & Pins die für die Beleuchtung verwendet werden
{
	DDRC=0xFF;				// grüne status Leds
	DDRE=0xFF;				// rote status Leds
	DDRB|= (1<<PB7);		// status leds
	DDRB|= (1<<PB6);		// lcd Beleuchtung
	DDRB|= (1<<PB5);		//headlights
}

void cntrlled(int led,bool value)
{


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
	
	
	while (1)
	{
	}
}


