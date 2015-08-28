/////////////////////////////////////////////////////////////////////
// AUTHOR:  Henry Wu
// DATE: 20 AUGUST 2014
// TITLE: sensor_update.h
// DESCRIPTION: A header to update the variables containing
//						  IMU sensor information
/////////////////////////////////////////////////////////////////////
// sensor_update.h is free software: you can redistribute it and/or modify
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

#ifndef SENSOR_UPDATE_H
#define SENSOR_UPDATE_H

#include <I2Cdev.h>
#include <MPU6050.h>

/////////////////////////////////////////////////////////////////////
// Read from these global variables in order to get xyz rotation and 
// acceleration The gyro senses rotational velocity from
// -250 deg/s to +250 deg/s on a scale from -32768 to 32767 
//
// The accelerometer senses forces along each axis from
// -2g to +2g on a scale from -32768 to 32767.* global variables */
/////////////////////////////////////////////////////////////////////
int16_t X_ROTATION;
int16_t Y_ROTATION;
int16_t Z_ROTATION;
int16_t X_ACCELERATION;
int16_t Y_ACCELERATION;
int16_t Z_ACCELERATION;
/////////////////////////////////////////////////////////////////////

/* MPU6050 sensor object declaration */
MPU6050 sensor;

/* set desired sample rate of accelerometer and gyro */
/* sample rate is calculated by 1khz/set_hz (ex. 1khz/200 = 5hz) */
void init_sensor(int set_hz){ 
  sensor.initialize();
  sensor.setDLPFMode(3);
  sensor.setRate(set_hz-1);
}

/* state machine to update the sensor variables */
int8_t sensor_update_sm(int8_t state){
	enum sensor_update_states {Collect_data};
	switch(state){ // state transitions
		case Collect_data:
			state = Collect_data;
			break;
		default:
			state = Collect_data;
			break;
	}
	switch(state){ // state actions
		case Collect_data:
			//collect and update the datas
			sensor.getAcceleration(&X_ACCELERATION,&Y_ACCELERATION,&Z_ACCELERATION);
			sensor.getRotation(&X_ROTATION,&Y_ROTATION,&Z_ROTATION);
			break;
		default:
			break;
	}
	return state;
}

#endif 
