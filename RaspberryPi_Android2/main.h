#ifndef __MAIN_H__
#define __MAIN_H__

#define KEYPAD_I2C_ADDRESS 0x20
#include <stdlib.h> 
#include "socket.h"
#include "sensor.h"
#include "json.h"
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

void init_sensor();

#endif

