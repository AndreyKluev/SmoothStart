/*
 * SmoothStart.c
 *
 * Created: 21.10.2013 23:50:38
 *  Author: AndreyKluev
 */ 


#include <avr/io.h>

#define outMotor 0
#define outLight 1
#define outLed   2
#define inButton 3

int main(void)
{
	// ����
	DDRB  = 0b00000111;	// 0 - ����, 1 - �����, PB0 - �����
	PORTB = 0b00000110;

    while(1)
    {
        //TODO:: Please write your application code 
    }
}