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
//Display libs
#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <nibo/display.h>
#include <nibo/gfx.h>
//Motorsteuerung
#include <nibo/copro.h>
#include <nibo/bot.h>
//Abstandssensoren
//#include <nibo/nds3.h>	// Aufsteckmodul
extern uint16_t copro_distance[5]; //!! Globale variable aus der copro.h datei merkwürdiges verhalten, daher wiederholte initialisierung benötigt für die infrarot entfernungssensoren
#define lloff
#define rroff
#define loff +4
#define roff -5
int engineR, engineL;


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
	display_init(3);
	gfx_init(); 
	gfx_set_proportional(1);
	bot_init();
	sei(); // enable interrupts
	bot_init();
	spi_init();
}


void distsens()
{
	copro_ir_startMeasure(); // Distanzsensoren starten
	char text[20]="-- -- -- -- --";
	if (copro_update()) // Co-Prozessor
	{
		sprintf(text, "%02x %02x %02x %02x %02x",
		(uint16_t)copro_distance[0]/256,
		(uint16_t)copro_distance[1]/256,
		(uint16_t)copro_distance[2]/256,
		(uint16_t)copro_distance[3]/256,
		(uint16_t)copro_distance[4]/256);
	}
	gfx_move(10,44);
	gfx_print_text 	("Entfernungssensoren: ");
	gfx_move(10, 55);
	gfx_print_text(text);
	int f = (uint16_t)copro_distance[2]/256;
	int ll = (uint16_t)copro_distance[3]/256;
	int rr = (uint16_t)copro_distance[1]/256;
	// Abstandsensoren Auslesen
	if (f+roff < 20 && engineR <1024 && engineL < 1024)
	{
		engineR = 30;
		engineL = 30;
	}
	if (f+roff > 25 )
	{
		engineR = -20;
		engineL = -20;
	}
	if (rr < 20 && f+roff < 20&&  engineR <1024 && engineL < 1024)
	{
		engineL = 30;
	}
	if (rr > 25 && f+roff < 20&&  engineR <1024 && engineL < 1024)
	{
		engineL = 10;
	}
	if (ll < 10 && f+roff < 20&& engineR <1024 && engineL < 1024)
	{
		engineR = 30;
	}
	if (ll > 15 && f+roff < 20&& engineR <1024 && engineL < 1024)
	{
		engineR = 10;
	}
	//Finaly set engine speed;
	copro_setSpeed(engineL, engineR);
	gfx_move(10,0);
	gfx_print_text 	("Engine_speed: ");
	gfx_move(10, 10);
	sprintf(text,"%02d %02d",engineL,engineR);
	gfx_print_text(text);
	delay(100);
}

int main(void)
{
	init();
	//PORTB |= ((1<<PB7)|(1<<PB6)|(1<<PB5));
	//PORTC = 0xFF;
	while (1)
	{
		distsens();
	}
}


