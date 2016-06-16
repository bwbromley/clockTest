/*
 * Clock.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: bromley
 */

#include "Clock.h"
#include <signal.h>

#include "board_info.h"
#include "ws2811.h"

#define ARRAY_SIZE(stuff) (sizeof(stuff) / sizeof(stuff[0]))

#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 5

#define HEIGHT 60
#define LED_COUNT (HEIGHT)

ws2811_t ledstring = { .freq = TARGET_FREQ, .dmanum = DMA, .channel =
  { [0] = { .gpionum = GPIO_PIN, .count = LED_COUNT, .invert = 0, .brightness = 255, } ,
	[1] = { .gpionum = 0, .count = 0, .invert = 0, .brightness = 0, }, }, };

ws2811_led_t clockArray[HEIGHT];
/**
 * This array maps an index into this array into the "minute" position of
 * that LED.
 */
int pixelsToMinutes[] = {59, 58, 57, 56,55,54, 53, 52, 51, 50, 49,  48, 47, 46, \
		45, 44, 43, 42,  41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, \
		27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, \
		10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
/**
 * Don't really need this.  Could just set ledstring.channel[0].leds[i] directly
 */
void render() {
	int i;
	for (i = 0; i < HEIGHT; i++) {
		ledstring.channel[0].leds[i] = clockArray[i];
	}
}

static void controlC(int signum) {
	ws2811_fini(&ledstring);
}

static void setupHandlers() {
	struct sigaction sa = { .sa_handler = controlC, };
	sigaction(SIGKILL, &sa, NULL);
}

void clear() {
	int i;
	for (i = 0; i < HEIGHT; i++)
		clockArray[i] = 0;
}

void advanceSecond() {
	int i;
	int status;
	for (i = 0; i < 60; i++) {
		clear();
		showHourMarks();
		showSecond(i);
		render();
		status = ws2811_render(&ledstring);
		uint32_t sleepTime = 1000000;
		usleep(sleepTime);
	}
}

void showTime() {
	getLocalTime();
	clear();
	showHour(hour);
	showHourMarks();
	showMinute(minute);
	showSecond(second);
	render();
	ws2811_render(&ledstring);
}

void showHour() {
	if (hour == 12)
		hour = 0;
	int temp = hour * 5;
	temp += minute / 12;
	int index = pixelsToMinutes[temp];
	if (index == 0) {
		clockArray[0] = 0xf000f0; // set this pixel to blue
		clockArray[59] = 0x200020;
		clockArray[1] = 0x200020;
		return;
	}
	if (index == 59) {
		clockArray[59] = 0xf000f0; // set this pixel to blue
		clockArray[58] = 0x200020;
		clockArray[0] = 0x200020;
		return;
	}
	clockArray[index] = 0xf000f0; // set this pixel to blue
	clockArray[index - 1] = 0x200020;
	clockArray[index + 1] = 0x200020;
}

void showMinute() {
	if (minute == 60)
		minute = 0;
	int index = pixelsToMinutes[minute];
	clockArray[index] = 0x00ff00; // set this pixel to green
}

void showSecond() {
	if (second == 60)
		second = 0;
	int index = pixelsToMinutes[second];
	clockArray[index] = 0xff0000; // set this pixel to red
}

void getLocalTime() {
	localTime = time(NULL);
	struct tm time = *localtime(&localTime);
	hour = time.tm_hour;
	hour = hour % 12;
	minute = time.tm_min;
	second = time.tm_sec;
}

void showPixel(int index) {
	clear();
	clockArray[index] = 0xff0000;	render();
	ws2811_render(&ledstring);
}
void fastForward() {
	hour = 0;
	minute = 0;
	second = 0;
	int i;
	while(1) {
		second++;
		if ((second % 60 == 0) && (second != 0)) {
			second = 0;
			minute ++;
		}
		if ((minute % 60 == 0) && (minute != 0)) {
			minute = 0;
			hour ++;
		}
		if ((hour %12 == 0) && (hour != 0))
			hour = 0;
		clear();
		showHour(hour);
		showHourMarks();
		showMinute(minute);
		showSecond(second);
		render();
		ws2811_render(&ledstring);
		usleep(10000);
	}
}

/**
 * Mark the hours
 */
void showHourMarks() {
	int i;
	for (i = 0; i < 12; i++) {
		int index =pixelsToMinutes[ i * 5];
		clockArray[index] = 0x202020; // light white
	}
}
int main(int argc, char *argv[]) {
	int ret = 0;
	int status = board_info_init();
	if (status < 0) {
		return -1;
	}
	setupHandlers();
	status = ws2811_init(&ledstring);
	if (status) {
		return -1;
	}
	while (1) {
		//showPixel(6);
		//fastForward();
		showTime();
		usleep(1000000);
	}
	ws2811_fini(&ledstring);
	return ret;
}


