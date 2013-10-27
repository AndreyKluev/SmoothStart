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

#define minShort  5
#define maxShort  100
#define minMedium 150
#define maxMedium 300
#define minLong   350

char MotorStatus = 2; // 1 - on, 2 - off
char MotorSpeed = 3;
char MotorValue = 0;

char LightStatus = 2; //1 - on, 2 - off
char LightSpeed = 3;
char LightValue = 0;

unsigned int timeBtn = 0;

ISR(TIM0_OVF_vect) {
	if ( (MotorStatus==1 && MotorValue<255) || (MotorStatus==2 && 0<MotorValue)) {
		cli();
		if (MotorStatus==1) {
			MotorValue = MotorValue + MotorSpeed;
			if (255<MotorValue) MotorValue = 255;
		} else {
			MotorValue = MotorValue - MotorSpeed;
			if (MotorValue<0) MotorValue = 0;
		}

		if (MotorValue==255) {
			PORTB |= (1<<outLed);
		} else {
			PORTB &= ~(1<<outLed);
		}

		OCR0A = 255 - MotorValue;
		sei();
	}

	if ( (LightStatus==1 && LightValue<255) || (LightStatus==2 && 0<LightValue)) {
		cli();
		if (LightStatus==1) {
			LightValue = LightValue + LightSpeed;
			if (255<LightValue) LightValue = 255;
		} else {
			LightValue = LightValue - LightSpeed;
			if (MotorValue<0) LightValue = 0;
		}

		OCR0B = LightValue;
		sei();
	}
}

int main(void) {
	// Init port B
	DDRB  = 0b00000111;	// 0 - вход, 1 - выход
	PORTB = 0b00000001;

	// Init PWM
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000011;
	TCNT0 = 0x00;

	OCR0A = 255 - MotorValue;
	OCR0B = LightValue;

	// Init Timer0
//	TCCR0B |= (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	while(1) {
		// Проверяем нажатие кнопки
		// Если кнопка нажата
		if ((PINB&(1<<inButton))==0) {
			timeBtn = 0;

			// Ждем отжатия клавиши (Считаем длину удержания кнопки)
			while((PINB&(1<<inButton))==0) {
				timeBtn++;
				_delay_ms(5);
			}
			
			// Короткое нажатие
			if (minShort<timeBtn && timeBtn<maxShort) {
				if (MotorStatus==2) {
					MotorStatus = 1;
				} else {
					MotorStatus = 2;
				}
			}

			// Среднее нажатие
			if (minMedium<timeBtn && timeBtn<maxMedium) {
				if (LightStatus==2) {
					LightStatus = 1;
				} else {
					LightStatus = 2;
				}
			}

			// Длинное нажатие
			if (minLong<timeBtn) {
				MotorStatus = 2;
				LightStatus = 2;
			}
		}
	}		
}