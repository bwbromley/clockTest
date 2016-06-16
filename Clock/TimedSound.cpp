/*
 * TimedSound.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: bromley
 */

#include "TimedSound.h"

 string TimedSound::baseAudioPath = "/home/bromley/audio/";

TimedSound::TimedSound() : clock(0) {
	initialize();
}

TimedSound::~TimedSound() {
}

void TimedSound::setClock(Clock* argument) {
	clock = argument;
}

void TimedSound::initialize() {
	initializeChimePaths();
	initializeDigitPaths();
	initializeAlarmPaths();
	minuteLastChimed = -1;
	disableChime = false;
}

void TimedSound::initializeAlarmPaths() {
	alarmPaths.push_back(baseAudioPath + "alarm/rooster3.wav");
}

void TimedSound::initializeChimePaths() {
	hourAudioPaths.push_back(baseAudioPath + "westminster/12hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/01hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/02hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/03hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/04hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/05hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/06hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/07hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/08hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/09hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/10hour.wav");
	hourAudioPaths.push_back(baseAudioPath + "westminster/11hour.wav");
	quarterAudioPaths.push_back(baseAudioPath + "westminster/Toll-1Quarter.wav");
	quarterAudioPaths.push_back(baseAudioPath + "westminster/Toll-2Quarter.wav");
	quarterAudioPaths.push_back(baseAudioPath + "westminster/Toll-3Quarter.wav");
	quarterAudioPaths.push_back(baseAudioPath + "westminster/Toll-4Quarter.wav");
}

void TimedSound::initializeDigitPaths() {
	digitPaths.push_back(baseAudioPath + "digits/zero.wav");
	digitPaths.push_back(baseAudioPath + "digits/one.wav");
	digitPaths.push_back(baseAudioPath + "digits/two.wav");
	digitPaths.push_back(baseAudioPath + "digits/three.wav");
	digitPaths.push_back(baseAudioPath + "digits/four.wav");
	digitPaths.push_back(baseAudioPath + "digits/five.wav");
	digitPaths.push_back(baseAudioPath + "digits/six.wav");
	digitPaths.push_back(baseAudioPath + "digits/seven.wav");
	digitPaths.push_back(baseAudioPath + "digits/eight.wav");
	digitPaths.push_back(baseAudioPath + "digits/nine.wav");
	digitPaths.push_back(baseAudioPath + "digits/ten.wav");
	digitPaths.push_back(baseAudioPath + "digits/eleven.wav");
	digitPaths.push_back(baseAudioPath + "digits/twelve.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/fifteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/sixteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/seventeen.wav");
	digitPaths.push_back(baseAudioPath + "digits/eighteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/nineteen.wav");
	digitPaths.push_back(baseAudioPath + "digits/twenty.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyOne.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyTwo.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyThree.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyFour.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyFive.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentySix.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentySeven.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyEight.wav");
	digitPaths.push_back(baseAudioPath + "digits/twentyNine.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirty.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyOne.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyTwo.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyThree.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyFour.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyFive.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtySix.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtySeven.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyEight.wav");
	digitPaths.push_back(baseAudioPath + "digits/thirtyNine.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourty.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyOne.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyTwo.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyThree.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyFour.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyFive.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtySix.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtySeven.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyEight.wav");
	digitPaths.push_back(baseAudioPath + "digits/fourtyNine.wav");
	digitPaths.push_back(baseAudioPath + "digits/fifty.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyOne.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyTwo.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyThree.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyFour.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyFive.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftySix.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftySeven.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyEight.wav");
	digitPaths.push_back(baseAudioPath + "digits/fiftyNine.wav");
}

void TimedSound::getLocalTime() {
	localTime = time(NULL);
	struct tm time = *localtime(&localTime);
	hour = time.tm_hour;
	am = true;
	if (hour >= 12)
		am = false;
	hour = hour % 12;
	minute = time.tm_min;
	second = time.tm_sec;
}

/**
 * Pure virtual implementation
 */
void TimedSound::threadBody() {
	alarmHour = 11;
	alarmMinute = 15;
	alarmAm = true;
	minuteLastAlarmed = -1;
	alarmEnabled = false;
	while (true) {
		sleep(1);
		getLocalTime();
		chime();
		alarm();
	}
}

void TimedSound::setAlarm(int hourAndMinute) {
	alarmHour = hourAndMinute / 100;
	if ((alarmHour > 23) || (alarmHour < 0)) {
		cout << "Invalid Alarm Hour " << alarmHour << endl;
		// Need to play an error message audio
		return;
	}
	alarmAm = true;
	if (alarmHour > 12) {
		alarmHour -= 12;
		alarmAm = false;
	}
	alarmMinute = hourAndMinute % 100;
	if ((alarmMinute > 59) || (alarmMinute < 0)) {
		cout << "Invalid Alarm Minute " << alarmMinute << endl;
		// Need an audio error message
		return;
	}
	vector<string> paths;
	paths.push_back(baseAudioPath + "commands/alarmSetFor.wav");
	paths.push_back(digitPaths[alarmHour]);
	// Speak a leading zero for minutes less than 10
	if (alarmMinute < 10)
		paths.push_back(digitPaths[0]);
	paths.push_back( digitPaths[alarmMinute]);
	if (alarmAm)
		paths.push_back(baseAudioPath + "commands/am.wav");
	else
		paths.push_back(baseAudioPath + "commands/pm.wav");
	clock->playAudio(paths);
}

void TimedSound::enableAlarm(bool value) {
	alarmEnabled = value;
}

bool TimedSound::isAlarmEnabled() {
	return alarmEnabled;
}

/**
 * Pure virtual implementation
 */
void TimedSound::start() {
	cout << "Westminster Chime thread started" << endl;
	thread = std::thread(&TimedSound::threadBody, this);
}
/**
 * Pure virtual implementation
 */
void TimedSound::performCommand(int command) {
	// do nothing
}

void  TimedSound::chime() {
	if (minuteLastChimed == minute)
		return;
	if (disableChime) {
		minuteLastChimed = -1;
		return;
	}
	int temp = minute % 15;
	if (temp)
		return;
	chimePaths.clear();
	temp = minute / 15;
	if (temp == 0) {
		chimePaths.push_back(hourAudioPaths[hour]);
	} else {
		chimePaths.push_back(quarterAudioPaths[temp - 1]);
	}
	clock->playAudio(chimePaths);
	minuteLastChimed = minute;
}

void TimedSound::alarm() {
	if (!alarmEnabled)
		return;
	if (minuteLastAlarmed == minute)
		return;
	minuteLastAlarmed = -1;
	if (alarmAm != am)
		return;
	if (alarmHour != hour)
		return;
	if (alarmMinute != minute)
		return;
	clock->playAudio(alarmPaths);
	minuteLastAlarmed = minute;
}

void TimedSound::setChimeDisable(bool value) {
	disableChime = value;
}

bool TimedSound::isChimeDisable() {
	return disableChime;
}
