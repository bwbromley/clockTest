/*
 * ClockPart.h
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#ifndef CLOCKPART_H_
#define CLOCKPART_H_

#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::string;
using std::cout;
using std::endl;

class ClockPart {
public:
	ClockPart();
	virtual ~ClockPart();
	virtual void threadBody() = 0;
	virtual void start() = 0;
	void setWhatToDo(int command);
	virtual void performCommand(int command) = 0;
protected:
	std::thread thread;
	int whatToDo;
	std::mutex mutex;
};

#endif /* CLOCKPART_H_ */
