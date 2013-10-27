/*
 * SmoothStart.c
 *
 * Created: 22.10.2013 08:09:36
 *  Author: AndreyKluev
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define outMotor 0
#define outLight 1
#define outLed   2
#define inButton 3

#define cntMin    10
#define cntShort  150
#define cntMedium 500

unsigned char MotorStatus = 0; // 0 - не меняем, 1 - увеличиваем, 2 - уменьшаем
unsigned char MotorSpeed = 1;
unsigned char MotorValue = 0;

unsigned char LightStatus = 0; // 0 - не меняем, 1 - увеличиваем, 2 - уменьшаем
unsigned char LightSpeed = 1;
unsigned char LightValue = 0;

unsigned int timeBtn = 0;

ISR(TIM0_OVF_vect)
{
		if (MotorStatus==1) {
			PORTB &= ~(1<<outMotor);
			PORTB |= (1<<outLed);
		}
		if (MotorStatus==2) {
			PORTB |= (1<<outMotor);
			PORTB &= ~(1<<outLed);
		}

		if (LightStatus==1) { PORTB |= (1<<outLight); }
		if (LightStatus==2) { PORTB &= ~(1<<outLight); }
}

int main(void)
{
	// Init port B
	DDRB  = 0b00000111;	// 0 - вход, 1 - выход
	PORTB = 0b00000001;

	// Init PWM
	
	// Init Timer0
	TCCR0B |= (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	while(1)
	{
		// Проверяем нажатие кнопки
		if ((PINB&(1<<inButton))==0) // Если кнопка нажата
		{
			timeBtn = 0;

			// Ждем отжатия клавиши (Считаем длину удержания кнопки)
			while((PINB&(1<<inButton))==0)
			{
				timeBtn++;
				_delay_ms(5);
			}
			
			// Короткое нажатие
			if (cntMin<timeBtn && timeBtn<cntShort)
			{
				if (MotorStatus==0 || MotorStatus==2)
				{
					MotorStatus = 1;
				}
				else
				{
					MotorStatus = 2;
				}
			}

			// Среднее нажатие
			if (cntShort<timeBtn && timeBtn<cntMedium)
			{
				if (LightStatus==0 || LightStatus==2)
				{
					LightStatus = 1;
				}
				else
				{
					LightStatus = 2;
				}
			}

			// Длинное нажатие
			if (cntMedium<timeBtn)
			{
				MotorStatus = 2;
				LightStatus = 2;
			}
		}
	}		
}