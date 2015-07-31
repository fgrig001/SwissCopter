/////////////////////////////////////////////////////////////////////
// AUTHOR: Frederick Grigsby
// DATE: 19 AUGUST 2014
// TITLE: TickTimer0.h
// DESCRIPTION: A set of timer functions that uses timer 0 and sets 
// 				a flag to 1 every given number of milliseconds.
/////////////////////////////////////////////////////////////////////
// TickTimer0.h is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
// EXAMPLE USAGE:
// int main(){
// 		TickTimer0On();
// 		TickTimer0Set(1); // tick every 1 ms
// 		while(1){
// 			/* your sm code here */
// 			while(!TickTimer0Flag);
// 			TickTimer0Flag=0;
// 		}
// 		return 0;
// 	}
////////////////////////////////////////////////////////////////////

#ifndef TICKTIMER0_H
#define TICKTIMER0_H

#include <avr/interrupt.h>

/* Timer flag that is set to 1 by TickTimer0ISR() */
volatile uint8_t TickTimer0Flag = 0; 

/* variables for counting ticks  */
uint32_t _Timer0_Start_= 1; 
uint32_t _Timer0_Current_= 0; 

/* Set TickTimer0ISR() to tick every n ms */
void TickTimer0Set(uint32_t n){
	_Timer0_Current_ = _Timer0_Start_ = n;
}

/* set register bits to initialize TickTimer0 */
void TickTimer0On(){
	/* Timer/Counter Controll Register */
	/* set CTC mode and prescaler of 64 */
	TCCR0B 	= 0x0B;	
	/* Output Controll Register */
	/* the ISR is called when TCNT == OCR */
	OCR0A 	= 250;
	/* TImer MaSK */
	/* set compare match interrupt bit */
	TIMSK0 	= 0x02; 
	/* Timer CouNTer */
	/* Initialize  counter  to 0 */
	TCNT0 = 0;
	/* enable interrupts */
	SREG |= 0x80;
}

/* turn off TickTimer0 */
void TickTimer0Off(){
	TCCR0B 	= 0x00; 
}

/* define TickTimer0 ISR*/
void TickTimer0ISR(){
	TickTimer0Flag = 1;
}

/* define timer0 ISR */
ISR(TIMER0_COMPA_vect){
	_Timer0_Current_--; 
	if (_Timer0_Current_ == 0){
		TickTimer0ISR();
		_Timer0_Current_ = _Timer0_Start_;
	}
}

#endif 
