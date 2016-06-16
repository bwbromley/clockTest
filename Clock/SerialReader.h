/*
 * SerialReader.h
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#ifndef SERIALREADER_H_
#define SERIALREADER_H_

#include "SerialStream.h"
#include "ClockPart.h"
#include <string>

class Clock;

using namespace LibSerial;

class SerialReader: public ClockPart {
public:
	SerialReader();
	virtual ~SerialReader();
	virtual void threadBody();
	virtual void start();
	virtual void performCommand(int command);
	void checkStatus(string message);
	void setClock(Clock* instance);
private:
	SerialStream serialStream;
	Clock* clock;
	string receivedBytes;
	void gotNewLine();
};

#endif /* SERIALREADER_H_ */
