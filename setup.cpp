#include<Arduino.h>

#include"setup.h"
#include"define.h"

void setup_init(){
	Serial.begin(9600);

	#ifdef PROMICRO
	//pinMode(3,OUTPUT);
	bitSet(DDRD, 3);
	//pinMode(9,OUTPUT);
	bitSet(DDRB, 1);
	//pinMode(10,OUTPUT);
	bitSet(DDRB, 2);
	//pinMode(11,OUTPUT);
	bitSet(DDRB, 3);  

	TCCR1A |= _BV(COM1A1); // connect pin 9 to timer 1 channel A  PB1
	TCCR1A |= _BV(COM1B1); // connect pin 10 to timer 1 channel B  PB2

	TCCR2A |= _BV(COM2A1); // connect pin 11 to timer 2 channel A  PB3
	TCCR2A |= _BV(COM2B1); // connect pin 3 to timer 2 channel B  PD3	

	#endif

	#ifdef MEGA
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(2, OUTPUT);

	TCCR3A |= (1<<WGM31); // phase correct mode
	TCCR3A &= ~(1<<WGM30);
	TCCR3B |= (1<<WGM33);
	TCCR3B &= ~(1<<CS31); // no prescaler
	ICR3   |= 0x3FFF; // TOP to 16383;  
	TCCR3A |= _BV(COM3C1); // connect pin 3 to timer 3 channel C
	TCCR3A |= _BV(COM3A1); // connect pin 5 to timer 3 channel A

	TCCR4A |= (1<<WGM41); // phase correct mode
	TCCR4A &= ~(1<<WGM40);
	TCCR4B |= (1<<WGM43);
	TCCR4B &= ~(1<<CS41); // no prescaler
	ICR4   |= 0x3FFF; // TOP to 16383;  

	TCCR4A |= _BV(COM4A1); // connect pin 6 to timer 4 channel A
	TCCR3A |= _BV(COM3B1); // connect pin 2 to timer 3 channel B
	#endif
}
