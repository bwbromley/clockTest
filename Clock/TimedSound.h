/*
 * TimedSound.h
 *
 *  Created on: Feb 22, 2016
 *      Author: bromley
 */

#ifndef TimedSound_H_
#define TimedSound_H_

#include <string>
#include <iostream>
#include <time.h>
#include <iostream>
#include <vector>
#include <thread>
//#include <stdlib.h>
#include "ClockPart.h"
#include "Clock.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class TimedSound : public ClockPart {
public:
	TimedSound();
	virtual ~TimedSound();
	void setClock(Clock* argument);
	void setChimeDisable(bool value);
	bool isChimeDisable();
	void setAlarm(int hourAndMinute);
	void enableAlarm(bool value);
	bool isAlarmEnabled();
	virtual void threadBody();
	virtual void start();
	virtual void performCommand(int command);
private:
	static string baseAudioPath; // where the chime files are
	Clock* clock;
	time_t localTime;
	int hour;
	int minute;
	int second;
	bool am; // time is in the  AM if true
	bool disableChime;
	int minuteLastChimed;
	int minuteLastAlarmed;
	vector<string> hourAudioPaths;
	vector<string> quarterAudioPaths;
	vector<string> chimePaths; // audio to play at this time
	vector<string> digitPaths;
	vector<string> alarmPaths;
	int alarmHour;
	int alarmMinute;
	bool alarmAm;
	bool alarmEnabled;
	void getLocalTime();
	void initialize();
	void initializeChimePaths();
	void initializeDigitPaths();
	void initializeAlarmPaths();
	void chime();
	void alarm();
};

#endif /* TimedSound_H_ */
