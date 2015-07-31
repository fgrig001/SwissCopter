/////////////////////////////////////////////////////////////////////
// AUTHOR: Frederick Grigsby
// DATE: 12 AUGUST 2014
// TITLE: RC_Contoller.h
// DESCRIPTION: A header to interface an n-channel RC controller 
// 				with an Arduino Uno using interupts to minimize
// 				procesor usage.
/////////////////////////////////////////////////////////////////////
// RC_Controller.h is free software: you can redistribute it and/or modify
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
/////////////////////////////////////////////////////////////////////

#ifndef RC_CONTROLLER_H
#define RC_CONTROLLER_H

#include <Arduino.h>
#include <PinChangeInt.h>  // http://playground.arduino.cc/Main/PinChangeInt
#include <TimerOne.h>      // http://playground.arduino.cc/Code/Timer1
#include <stdint.h>

///////////////////////////////////////////////////////////////////////
//  MODIFY DEPENDING ON WHAT PINS ARE CONNECTED AND 
//  HOW MANY RC CHANNES ARE USED
///////////////////////////////////////////////////////////////////////
/* call space-saving macros */
//#define NO_PORTB_PINCHANGES
//#define NO_PORTC_PINCHANGES
//#define NO_PORTD_PINCHANGES

/* define filter resolution */
#define FILTER_RES 20

/* define number of pins */
#define PIN_COUNT 4

/* define pins to be used */
#define RC_CH1 2
#define RC_CH2 3
#define RC_CH3 4
#define RC_CH4 5

/* define array of pin numbers */
uint8_t PIN_NO[] = {RC_CH1,RC_CH2,RC_CH3,RC_CH4};
///////////////////////////////////////////////////////////////////////

/* golobal variable declarations */
volatile uint16_t PPM_TIME[PIN_COUNT];
uint16_t PPM_STABLE_TIME[PIN_COUNT];
volatile uint8_t pin_index = 0;

/* function prototypes */
void rise();			// ISR - Do not call!
void fall();			// ISR - Do not call!
void Init_RC_Controller();	// This is the only function that needs to be called 
uint8_t Stabelize_PPM_SM(uint8_t state);

/* define ISR function "rise" */
void rise(){
	Timer1.restart();
	Timer1.start();
	PCintPort::detachInterrupt(PIN_NO[pin_index]);
	PCintPort::attachInterrupt(PIN_NO[pin_index],&fall,CHANGE);
}

/* define ISR function "fall" */
void fall(){ 
	PPM_TIME[pin_index] = Timer1.read();
	PCintPort::detachInterrupt(PIN_NO[pin_index]);
	pin_index = (pin_index+1) % PIN_COUNT;
	PCintPort::attachInterrupt(PIN_NO[pin_index],&rise,CHANGE);
}

/* init function */
void Init_RC_Controller(){
	/* clear times to 0 */
	for(uint8_t i=0;i<PIN_COUNT;++i)
		PPM_TIME[i]=0;
	/* initialize interrupt */
	PCintPort::attachInterrupt(PIN_NO[pin_index],&rise,RISING);
	/* initalize timer */
	Timer1.initialize(1024);
}

/* state machine that filters the ppm input and writes to PPM_STABLE_TIME[] */
int8_t Stabelize_PPM_SM(int8_t state){
	/* static variables */
	static uint16_t ppm_buffer[PIN_COUNT][FILTER_RES];
	static uint8_t iterate = 0;
	/* temp variables */
	uint32_t temp;
	static uint16_t hold = 0;
	/* states */	
	enum states{UPDATE};
	/* state machine */
	switch(state){ // transitions
		case UPDATE:
		default:
			state=UPDATE;
		break;
	}
	switch(state){ //actions
		case UPDATE:
			for(uint8_t i=0;i<PIN_COUNT;++i){
				ppm_buffer[i][iterate] = PPM_TIME[i];
				temp = 0;
				for(uint8_t j=0;j<FILTER_RES;++j)
					temp += ppm_buffer[i][j];
				PPM_STABLE_TIME[i] = temp/FILTER_RES;
			}
			iterate = (iterate+1)%FILTER_RES;
			break;
		default:
			break;
	}
	return state;
}

#endif
