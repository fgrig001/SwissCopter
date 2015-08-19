#!/bin/bash

# Code refrences
# https://github.com/jrowberg/i2cdevlib
# https://github.com/nabontra/ServoTimer2
# https://github.com/GreyGnome/PinChangeInt
# https://github.com/GreyGnome/EnableInterrupt

# Location of arduino library folder 
LIBRARY=$HOME/sketchbook/libraries

# check to see if LIBRARY path variable is valid
if [ ! -e $LIBRARY ] ; then
   echo Path to Arduino library is not valid: check to see that the Arduino IDE is properly installed
   exit
fi

################ Install librarys #############################

# Install I2Cdev library
echo Checking I2Cdev library ...
if [ ! -e $LIBRARY/I2Cdev ] ; then
   echo not found: installing ...
   mkdir $LIBRARY/I2Cdev
   wget -q https://raw.githubusercontent.com/jrowberg/i2cdevlib/master/Arduino/I2Cdev/I2Cdev.cpp
   wget -q https://raw.githubusercontent.com/jrowberg/i2cdevlib/master/Arduino/I2Cdev/I2Cdev.h
   mv I2Cdev* $LIBRARY/I2Cdev
   echo done
else
   echo found
fi

# Install MPU6050 library
echo Checking MPU6050 library ...
if [ ! -e $LIBRARY/MPU6050 ] ; then
   echo not found: installing ...
   mkdir $LIBRARY/MPU6050
   wget -q https://raw.githubusercontent.com/jrowberg/i2cdevlib/master/Arduino/MPU6050/MPU6050.cpp
   wget -q https://raw.githubusercontent.com/jrowberg/i2cdevlib/master/Arduino/MPU6050/MPU6050.h
   mv MPU6050* $LIBRARY/MPU6050
   echo done
else
   echo found
fi

# Install ServoTimer2 library
echo Checking ServoTimer2 library ...
if [ ! -e $LIBRARY/ServoTimer2 ] ; then
   echo not found: installing ...
   mkdir $LIBRARY/ServoTimer2
   wget -q https://raw.githubusercontent.com/nabontra/ServoTimer2/master/ServoTimer2.cpp
   wget -q https://raw.githubusercontent.com/nabontra/ServoTimer2/master/ServoTimer2.h 
   mv ServoTimer2* $LIBRARY/ServoTimer2
   echo done
else
   echo found
fi

# Install PinChangeInt library
echo Checking PinChangeInt library ...
if [ ! -e $LIBRARY/PinChangeInt ] ; then
   echo not found: installing ...
   mkdir $LIBRARY/PinChangeInt
   wget -q https://raw.githubusercontent.com/GreyGnome/PinChangeInt/master/PinChangeInt.h 
   mv PinChangeInt* $LIBRARY/PinChangeInt
   echo done
else
   echo found
fi

# Install EnableInterrupt library
echo Checking EnableInterrupt library ...
if [ ! -e $LIBRARY/EnableInterrupt ] ; then
   echo not found: installing ...
   mkdir $LIBRARY/EnableInterrupt
   wget -q https://raw.githubusercontent.com/GreyGnome/EnableInterrupt/master/EnableInterrupt.hkj  
   mv EnableInterrupt* $LIBRARY/EnableInterrupt
   echo done
else
   echo found
fi




############### Link projcet files ############################
echo Linking project files ...

# Link RFController
echo Checking RFController linking ...
if [ ! -h $LIBRARY/RFController ] ; then
   echo not found: linking ...
   ln -s $(pwd)/RFController $LIBRARY
   echo done
else
   echo already linked
fi

# Link TimerOne 
echo Checking TimerOne linking ...
if [ ! -h $LIBRARY/TimerOne ] ; then
   echo not found: linking ...
   ln -s $(pwd)/TimerOne $LIBRARY
   echo done
else
   echo already linked
fi

# Link ArduinoDevSwissCopter.ino
echo Checking SwissCopter.ino linking ...
if [ ! -h $LIBRARY/SwissCopter ] ; then
   echo not found: linking ...
   ln -s $(pwd)/SwissCopter $LIBRARY/../
   echo done
else 
   echo already linked
fi

echo Setup finished successfully!
