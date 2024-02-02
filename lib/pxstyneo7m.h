/*
 * neo7m.h
 *
 *  Created on: Feb 2, 2024
 *      Author: kokmu
 */
#ifndef PXSTYNEO7M_H_
#define PXSTYNEO7M_H_
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define _io static

/****************USR functions******************/

int readData(char nmea[1024]); // Reading RMC data

int getHours(void);
int getMinutes(void);
int getSeconds(void);

float getLatitude(void);
float getLongitude(void);

int getSpeed(int type);

int getDay(void);
int getMonth(void);
int getYear(void);

/****************USR functions******************/

#endif
