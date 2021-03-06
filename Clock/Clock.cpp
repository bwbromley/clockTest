/*
 * Clock.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#include "Clock.h"
#include <unistd.h>
#include <stdlib.h>
#include "TimedSound.h"

// Initialize class variables
int Clock::stateIdle = 0;
int Clock::stateError = -1;
int Clock::stateGetAlarmTime = 1;
int Clock::stateSetAlarmTime = 2;
int Clock::stateGetAlarmAm = 3;
int Clock::statePlayMenu = 4;

Clock::Clock() {
	initialize();
}

Clock::~Clock() {
	delete timedSound;
	timedSound = 0;
}
void Clock::initialize() {
	// On the raspberry pi zero, we need to disable updating the neopixels
	// while audio is playing as audio causes the pixles to flash randomly.
	disablePixelUpdate = false;
	clockState = stateIdle;
	numDigitsReceived = 0;
	ambientLightIntensity = 1024;
	volume = 75;
}
void Clock::setDisablePixelUpdate(bool value) {
	disablePixelUpdate = value;
}
bool Clock::getDisablePixelUpdate() {
	return disablePixelUpdate;
}
/**
 * Start the threads of this application.
 */
void Clock::start() {
	pixelRing.start();
	serialReader.setClock(this);
	serialReader.start();
	audioPlayer.setVolume(volume);
	timedSound = new TimedSound();
	timedSound->setClock(this);
	timedSound->start();
}
/**
 * On the pi zero, playing audio sometimes causes the pixels to flash like crazy.  Turn
 * off updating the pixels while playing sound if desired.
 */
void Clock::playAudio(string pathName) {
	if (disablePixelUpdate)
		pixelRing.setDisabled(true);
	while(audioPlayer.isPlaying())
		sleep(1);
	audioPlayer.setFilePath(pathName);
	audioPlayer.play();
	while (audioPlayer.isPlaying())
		sleep(1);
	if (disablePixelUpdate)
		pixelRing.setDisabled(false);
}

void Clock::playAudio(vector<string> filePaths) {
	if (disablePixelUpdate)
		pixelRing.setDisabled(true);
	while(audioPlayer.isPlaying())
		sleep(1);
	for (size_t i = 0; i < filePaths.size(); i++) {
		audioPlayer.setFilePath(filePaths[i]);
		cout << "Setting Audio path to " << filePaths[i] << endl;
		audioPlayer.play();
		while (audioPlayer.isPlaying())
			sleep(1);
	}
	if (disablePixelUpdate)
		pixelRing.setDisabled(false);
}
/**
 * Get the digit from the IR remote control value sent via serial from
 * the Arduino / Teensy
 */
int Clock::getDigit(string value) {
	string junk = "Zero";
	size_t position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 0;
	}
	junk = "One";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 1;
	}
	junk = "Two";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 2;
	}
	junk = "Three";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 3;
	}
	junk = "Four";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 4;
	}
	junk = "Five";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 5;
	}
	junk = "Six";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 6;
	}
	junk = "Seven";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 7;
	}
	junk = "Eight";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 8;
	}
	junk = "Nine";
	position = value.find(junk);
	if (position != std::string::npos) {
		numDigitsReceived ++;
		return 9;
	}
	return -1; // Not a digit
}
/**
 * We received a "command" over the serial link from the Arduino.
 * Execute the the function supporting this command.
 */
void Clock::serialCommand(string& command) {
	cout << "Clock Got Serial Command " << command;
	string value = "Mute"; // Received command to mute the chime
	size_t position = command.find(value);
	if (position != std::string::npos) {
		toggleMuteChime();
		clockState = stateIdle;
		return;
	}
	value = "Light: ";  // Received ligth intensity from CdS cell
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(7);
		if (clockState == stateSetAlarmTime)
			return;
		parseLightIntensity(substring);
		clockState = stateIdle;
		return;
	}
	value = "Power";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(7);
		toggleMuteAlarm();
		return;
	}
	value = "Source";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(8);
		// do something
		return;
	}
	value = "Record";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(8);
		// do something
		return;
	}
	value = "Ch+";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(5);
		// do something
		return;
	}
	value = "TimeShift"; // get digits --set the alarm
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(11);
		clockState = stateSetAlarmTime;
		alarmValue = 0;
		return;
	}
	value = "Vol-"; // Turn down the "Master" volume
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(6);
		volume -= 2;
		if (volume < 50)
			volume = 50;
		while(audioPlayer.isPlaying())
			sleep(1);
		audioPlayer.setVolume(volume);
		return;
	}
	value = "FullScreen";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(12);
		// do something
		return;
	}
	value = "Vol+"; // Turn up the "Master" volume
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(6);
		volume += 2;
		if (volume > 95)
			volume = 95;
		while(audioPlayer.isPlaying())
			sleep(1);
		audioPlayer.setVolume(volume);
		return;
	}
	value = "Ch-";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(5);
		// do something
		return;
	}
	value = "Recall";
	position = command.find(value);
	if (position != std::string::npos) {
		string substring = command.substr(8);
		// do something
		return;
	}
	if (clockState != stateSetAlarmTime) {
		return;
	}
	int temp = getDigit(command);
	cout << "State is stateSetAlarmTime and got digit " << temp << endl;
	if (temp == -1) {
		cout << "Expected a digit and did not get one\n";
		clockState = stateIdle;
		numDigitsReceived = 0;
		// Say there was an error
	}
	int multiplier = 1000;
	if (numDigitsReceived == 2)
		multiplier = 100;
	if (numDigitsReceived == 3)
		multiplier = 10;
	if (numDigitsReceived == 4)
		multiplier = 1;
	alarmValue += temp * multiplier;
	if (numDigitsReceived != 4)
		return;
	cout << "Setting alarm time to " << alarmValue << endl;
	setAlarm();
	alarmValue = 0;
	numDigitsReceived = 0;
	clockState = stateIdle;
}
/**
 * Set the time the alarm will sound.  Must enter time as 4 digit 24 hour
 * time value.
 */
void Clock::setAlarm() {
	if (alarmValue > 2359) {
		cout << "Invalid Alarm Time " << alarmValue << endl;
		return;
	}
	// Need to say "Enter 4 digit alarm time"
	timedSound->setAlarm(alarmValue);
}

void Clock::parseLightIntensity(string valueString) {
	//cout << "Light Substring is " << valueString << endl;
	int value = atoi(valueString.c_str());
	//cout << "Light value is " << value << endl;
	ambientLightIntensity = value;
}
/**
 * Answer the text digit contained in the string (received from the serial
 * port) or -1 if the string did not contain a digit.
 */
int Clock::parseDigit(string digitString) {
	int value = -1;
	if (digitString.compare("Zero") == 0)
		value = 0;
	if (digitString.compare("One") == 0)
		value = 1;
	if (digitString.compare("Two") == 0)
		value = 2;
	if (digitString.compare("Three") == 0)
		value = 3;
	if (digitString.compare("Four") == 0)
		value = 4;
	if (digitString.compare("Five") == 0)
		value = 5;
	if (digitString.compare("Six") == 0)
		value = 6;
	if (digitString.compare("Seven") == 0)
		value = 7;
	if (digitString.compare("Eight") == 0)
		value = 8;
	if (digitString.compare("Nine") == 0)
		value = 9;
	return value;
}
/**
 * Enable or disable the Westminster chime on the quarter hour.
 */
void Clock::toggleMuteChime() {
	bool state = timedSound->isChimeDisable();
	state = !state;
	if (state == true) {
		audioPlayer.setFilePath("/home/bromley/audio/commands/chimeIsDisabled.wav");
		audioPlayer.play();
	} else {
		audioPlayer.setFilePath("/home/bromley/audio/commands/chimeIsEnabled.wav");
		audioPlayer.play();
	}
	timedSound->setChimeDisable(state);
}
/**
 * Enable or disable playing the alarm clock sound.
 */
void Clock::toggleMuteAlarm() {
	bool state = timedSound->isAlarmEnabled();
	state = !state;
	if (state == true) {
		audioPlayer.setFilePath("/home/bromley/audio/commands/alarmIsEnabled.wav");
		audioPlayer.play();
	} else {
		audioPlayer.setFilePath("/home/bromley/audio/commands/alarmIsDisabled.wav");
		audioPlayer.play();
	}
	timedSound->enableAlarm(state);
}
/**
 * Scale the brightness of all pixels on the clock.
 */
void Clock::setBrightness(unsigned char brightness) {
	pixelRing.setBrightness(brightness);
}
/*
 * This is calibrated for a Teensy v3.2 with a CdS photo resistor and
 * a 1k ohm resistor.  YMMV
 */
void Clock::scaleBrightnessToAmbientLight() {
	int temp = ambientLightIntensity / 4;
	if (temp > 255)
		temp = 255;
	if (temp < 10)
		temp = 10;
	setBrightness((unsigned char)temp);
}

int main(int argc, char** argv) {
	Clock* clock = new Clock();
	clock->start();
	unsigned char brightness = 255;
	while(true) {
		sleep(1);
		clock->scaleBrightnessToAmbientLight	();
	}
	return 0;
}
