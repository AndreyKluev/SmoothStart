/*
 * SmoothStart.c
 *
 * Created: 22.10.2013 08:09:36
 *  Author: AndreyKluev
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define outMotor 0
#define outLight 1
#define outLed   2
#define inButton 3

ISR(TIM0_OVF_vect)
{
}	

int main(void)
{
	// Init port B
	DDRB  = 0b00000111;	// 0 - вход, 1 - выход
	PORTB = 0b00000110;

	// Init PWM

	// Init Timer0

    while(1)
    {
	}		
}