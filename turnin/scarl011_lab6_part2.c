/*	Author: me
 *  Partner(s) Name: 123123123123123
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	MAKE BOARD GO 123123123123 switch every sec!!
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include<avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR (TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr ==0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States{Start, S0, S0_Press, S0_Rel, S1, S1_Press, S1_Rel, S2, S2_Press, S2_Rel,} state;
unsigned char  tmpA = 0;
unsigned char tmpC = 0x00;
unsigned char cnt = 0;


void Tick(){
	switch(state){
		case Start:
			state=S0;
			break;
		case S0:
			if (tmpA){
				state = S0_Press;
			}
			else if (cnt %9 > 1) {state = S1;}
			else {state = S0;}
			break;
		case S0_Press: 
			if (!tmpA){state = S0_Rel;}
			break;
		case S0_Rel:
			if (tmpA) {state = S0;} // I don't want to account for holding button
			break;
		case S1:
			if (tmpA){
				state = S1_Press;
			}
			else if (cnt %9 > 4 ) {state = S2;}
			else {state = S1;}
                        break;
		case S1_Press: 
			if (!tmpA){state = S1_Rel;}
			break;
		case S1_Rel:
			if (tmpA) {state = S0;} // I don't want to account for holding button
			break;
		case S2:
			if (tmpA){
				state = S2_Press;
			}
			else if (cnt % 9 > 7) {state = S0;}
                        else {state = S2;}
                        break;
		case S2_Press: 
			if (!tmpA){state = S2_Rel;}
			break;
		case S2_Rel:
			if (tmpA) {state = S0;} // I don't want to account for holding button
			break;
		default:
			state = Start;
			break;
	}
	switch(state){ //ACTIONS
		case Start:
			tmpC = 0x00;
			break;
		case S0:
			tmpC = 0x01;
			cnt++;
			break;
		case S0_Press:
			tmpC = 0x01;
			break;
		case S0_Rel:
			tmpC = 0x01;
			cnt = 0;
			break;
		case S1: 
			tmpC = 0x02;
			cnt++;
			break;
		case S1_Press:
			tmpC = 0x02;
			break;
		case S1_Rel:
			tmpC = 0x02;
			cnt = 0;
			break;
                case S2:
			tmpC = 0x04;
			cnt++;
			break;
		case S2_Press:
			tmpC = 0x04;
			break;
		case S2_Rel:
			tmpC = 0x04;
			cnt = 0;
			break;
		default:
			break;
	}
}


int main(void) {

    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(100);
	TimerOn();
    while (1){
	tmpA = ~PINA;
	Tick();
	PORTB = tmpC;
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
