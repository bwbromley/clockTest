/*
 * Clock.h
 *
 *  Created on: Feb 9, 2016
 *      Author: bromley
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include <time.h>


void render();
void moveUp();
void bottom();
static void setup_handlers();
void clear();
void showTime();
void showHour();
void showMinute();
void showSecond();
void showHourMarks();
void advanceSecond();
void getLocalTime();
void initialize();
void showPixel(int index);
void fastForward();


int hour;
int minute;
int second;
time_t localTime;
int pixelsToMinutes[60];

#endif /* CLOCK_H_ */
