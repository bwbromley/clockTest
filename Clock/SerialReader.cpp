/*
 * SerialReader.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#include "SerialReader.h"
#include "Clock.h"

SerialReader::SerialReader() : clock(0) {
}

SerialReader::~SerialReader() {
}

void  SerialReader::setClock(Clock* instance) {
	clock = instance;
}

void SerialReader::gotNewLine() {
	//cout << receivedBytes; // has \n
	if (clock != 0)
		clock->serialCommand(receivedBytes);
	receivedBytes.clear();
}
/**
 * Override pure virtual method.
 */
void SerialReader::threadBody() {
	while(whatToDo != -1) {
		char nextByte = 0;
		serialStream.get(nextByte);
		if (nextByte != 0) {
			receivedBytes += nextByte;
		}
		if (nextByte == '\n')
				gotNewLine();
		//std::cout << (unsigned char) nextByte;
		usleep(10000);
	}
}
/**
 * Override pure virtual method.
 */
void SerialReader::start() {
	serialStream.Open("/dev/ttyAMA0");
	checkStatus( "Error: Could not open serial port.");
	serialStream.SetBaudRate(SerialStreamBuf::BAUD_9600);
	checkStatus("Error: Could not set the baud rate.");
	serialStream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	checkStatus( "Error: Could not set the character size.");
	serialStream.SetParity(SerialStreamBuf::PARITY_NONE);
	checkStatus("Error: Could not disable the parity.");
	serialStream.SetNumOfStopBits(1);
	checkStatus("Error: Could not set the number of stop bits.");
	serialStream.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
	checkStatus("Error: Could not use hardware flow control.");
	cout << "Serial Reader Started" << endl;
	thread = std::thread(&SerialReader::threadBody, this);
}
/**
 * Override pure virtual method.
 */
void SerialReader::performCommand(int command) {
	cout << "SerialReader got command " << command << endl;
	mutex.lock();
	whatToDo = command;
	mutex.unlock();
}

void SerialReader::checkStatus(string message) {
	if (!serialStream.good()) {
		cout << "Serial Reader Error " << message << endl;
	}
}
