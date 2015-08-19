/////////////////////////////////////////////////////////////////////
// AUTHOR: Frederick Grigsby
// DATE: 7th AUGUST 2015
// TITLE: RFContoller.h
// DESCRIPTION: A header to interface an n-channel RF controller 
// 				with an Arduino Uno using interupts to minimize
// 				procesor usage.
/////////////////////////////////////////////////////////////////////
// RFController.h is free software: you can redistribute it and/or modify
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
#pragma once

#include <Arduino.h>
#include <PinChangeInt.h>  // http://playground.arduino.cc/Main/PinChangeInt
#include <TimerOne.h>      // http://playground.arduino.cc/Code/Timer1
#include <stdint.h>


/* function prototypes */
void rise();      // ISR - Do not call!
void fall();      // ISR - Do not call!
void Init_RC_Controller(uint8_t ch_num,uint8_t* ch_pins); // This is the only function that needs to be called 

struct RFController{
   uint8_t chNum;
   uint8_t* chPins; 
   uint16_t* pulseWidth;
   uint8_t chIndex;
}rfController;


void InitRFController(uint8_t ch_num,uint8_t* ch_pins){
   rfController.chNum=ch_num;
   rfController.chPins=ch_pins;
   rfController.pulseWidth=new uint16_t[ch_num];
   rfController.chIndex=0;
   for(uint8_t i=0;i<rfController.chNum;++i){
      rfController.pulseWidth[i]=0;
   }
   /* initialize interrupt */
   PCintPort::attachInterrupt(rfController.chPins[rfController.chIndex],&rise,RISING);
   /* initalize timer */
   Timer1.initialize(1024);
}

/* define ISR function "rise" */
// TODO: update variables to reflect changes
void rise(){
   Timer1.restart();
   Timer1.start();
   PCintPort::detachInterrupt(rfController.chPins[rfController.chIndex]);
   PCintPort::attachInterrupt(rfController.chPins[rfController.chIndex],&fall,CHANGE);
}

/* define ISR function "fall" */
// TODO: update variables to reflect changes
void fall(){ 
   rfController.pulseWidth[rfController.chIndex] = Timer1.read();
   PCintPort::detachInterrupt(rfController.chPins[rfController.chIndex]);
   rfController.chIndex = (rfController.chIndex+1) % rfController.chNum;
   PCintPort::attachInterrupt(rfController.chPins[rfController.chIndex],&rise,CHANGE);
}


