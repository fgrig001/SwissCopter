/////////////////////////////////////////////////////////////////////
// AUTHOR: David Lean
// DATE: 19 AUGUST 2014
// TITLE: ESC_Controller.h
// DESCRIPTION: A header to interface 4 ESC's that control motors 
// 				with an Arduino Uno using the ServoTimer2
// 				library so that the timer does not interfere
//                              with the RC Controller library.
/////////////////////////////////////////////////////////////////////
// ESC_Controller.h is free software: you can redistribute it and/or modify
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

#ifndef ESC_CONTROLLER_H
#define ESC_CONTROLLER_H

#include <ServoTimer2.h>

///////////////////////////////////////////////////////////////////////
//  MODIFY DEPENDING ON WHAT PINS ARE CONNECTED AND 
//  HOW MANY RC CHANNES ARE USED
///////////////////////////////////////////////////////////////////////
/* define pins for ESC's */
#define PIN_MOTOR_NOSE 9
#define PIN_MOTOR_TAIL 10
#define PIN_MOTOR_LEFT 11
#define PIN_MOTOR_RIGHT 12

///////////////////////////////////////////////////////////////////////

/* Servo objects for ESC's */
ServoTimer2 esc_nose;
ServoTimer2 esc_tail;
ServoTimer2 esc_left;
ServoTimer2 esc_right;

/* glocal variables for motor speed 
   PPM SCALE = 750 - 2250 */
volatile uint16_t M_SPEED_NOSE = 750;
volatile uint16_t M_SPEED_TAIL = 750;
volatile uint16_t M_SPEED_LEFT = 750;
volatile uint16_t M_SPEED_RIGHT = 750;

/* function prototypes */
void INIT_ESC_CONTROLLER();
int8_t set_nose(int8_t state);
int8_t set_tail(int8_t state);
int8_t set_left(int8_t state);
int8_t set_right(int8_t state);

/* init function */
void INIT_ESC_CONTROLLER(){
  /* sets the esc servo object to the correct pin for the motor */
  esc_nose.attach(PIN_MOTOR_NOSE);
  esc_nose.write(M_SPEED_NOSE);
  
  esc_tail.attach(PIN_MOTOR_TAIL);
  esc_tail.write(M_SPEED_TAIL);
  
  esc_left.attach(PIN_MOTOR_LEFT);
  esc_left.write(M_SPEED_LEFT);
  
  esc_right.attach(PIN_MOTOR_RIGHT);
  esc_right.write(M_SPEED_RIGHT);
  
  //Serial.begin(9600); //for testing
}

/* state machine that sets the speed for the nose motor to the global variable */
int8_t set_nose(int8_t state){
  /* states */
  enum states{UPDATE};
  /* state machine */
  switch(state){ //transitions
    case UPDATE:
    default:
      state = UPDATE;
      break;
  }
  switch(state){ //actions
    case UPDATE:
      esc_nose.write(M_SPEED_NOSE);
      break;
    default:
      break;
  }
  return state;
}

/* state machine that sets the speed for the tail motor to the global variable */
int8_t set_tail(int8_t state){
  /* states */
  enum states{UPDATE};
  /* state machine */
  switch(state){ //transitions
    case UPDATE:
    default:
      state = UPDATE;
      break;
  }
  switch(state){ //actions
    case UPDATE:
      esc_tail.write(M_SPEED_TAIL);
      break;
    default:
      break;
  }
  return state;
}

/* state machine that sets the speed for the left motor to the global variable */
int8_t set_left(int8_t state){
  /* states */
  enum states{UPDATE};
  /* state machine */
  switch(state){ //transitions
    case UPDATE:
    default:
      state = UPDATE;
      break;
  }
  switch(state){ //actions
    case UPDATE:
      esc_left.write(M_SPEED_LEFT);
      break;
    default:
      break;
  }
  return state;
}

/* state machine that sets the speed for the right motor to the global variable */
int8_t set_right(int8_t state){
  /* states */
  enum states{UPDATE};
  /* state machine */
  switch(state){ //transitions
    case UPDATE:
    default:
      state = UPDATE;
      break;
  }
  switch(state){ //actions
    case UPDATE:
      esc_right.write(M_SPEED_RIGHT);
      break;
    default:
      break;
  }
  return state;
}

#endif