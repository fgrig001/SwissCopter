/////////////////////////////////////////////////////////////////////
// AUTHOR: Frederick Grigsby
// DATE: 19 AUGUST 2014
// TITLE: Scheduler.h
// DESCRIPTION: A task scheduler for running synchronous state machines
/////////////////////////////////////////////////////////////////////
// Scheduler.h is free software: you can redistribute it and/or modify
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

#ifndef SCHEDULER_H
#define SCHEDULER_H

/* GCD function */
uint32_t get_GCD(uint32_t a,uint32_t b){
	if(a < b){ a = a^b; b = a^b; a = a^b; }
	if(a%b == 0){ return b; }
	return get_GCD(b,a%b);
}

 /* task structure definition*/
typedef struct _task_{
	int8_t state;
	uint32_t period;
	uint32_t elapsedTime;
	int8_t (*TickFct)(int8_t);
}task;

#endif
