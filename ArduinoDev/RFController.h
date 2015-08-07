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

#include <Arduino.h>
#include <PinChangeInt.h>  // http://playground.arduino.cc/Main/PinChangeInt
#include <TimerOne.h>      // http://playground.arduino.cc/Code/Timer1
#include <stdint.h>

class RFController{
   public:
      RFController(int ch_num,int* ch_pins); 
      ~RFController(); 
   private:
      uint8_t chNum;
      uint8_t* chPins; 
      uint16_t* pulseWidth;
      uint8_t chIndex;
      /* define ISR function "rise" */
      void rise();
      /* define ISR function "fall" */
      void fall();
;


RFController::RFController(int ch_num,int* ch_pins):
   chNum(ch_num),
   chPins(ch_pins),
   pulseWidth(new uint16_t[ch_num]),
   chIndex(0)
{
   for(uint8_t i=0;i<chPins;++i){
      pulseWidth[i]=0;
   }
}

/* define ISR function "rise" */
// TODO: update variables to reflect changes
void RFController::rise(){
   Timer1.restart();
   Timer1.start();
   PCintPort::detachInterrupt(PIN_NO[pin_index]);
   PCintPort::attachInterrupt(PIN_NO[pin_index],&fall,CHANGE);
}

/* define ISR function "fall" */
// TODO: update variables to reflect changes
void RFController::fall(){ 
   PPM_TIME[pin_index] = Timer1.read();
   PCintPort::detachInterrupt(PIN_NO[pin_index]);
   pin_index = (pin_index+1) % PIN_COUNT;
   PCintPort::attachInterrupt(PIN_NO[pin_index],&rise,CHANGE);
}


