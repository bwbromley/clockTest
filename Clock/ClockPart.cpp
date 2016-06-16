/*
 * ClockPart.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#include "ClockPart.h"
#include <unistd.h>

ClockPart::ClockPart(): whatToDo(0) {
}

ClockPart::~ClockPart() {
	whatToDo = -1;
	if(thread.joinable())
		thread.join();
	cout << "ClockPart Destructor called -----------------" << endl;
}

/*void ClockPart::threadBody() {
	while (whatToDo != -1) {
		cout << "ClockPart says Hello" << endl;
		mutex.lock();
		int temp = whatToDo;
		mutex.unlock();
		if (temp)
			performCommand(temp);
		usleep(1000000);
	}
	cout << "ClockPart Exiting" << endl;
}*/

/*void ClockPart::start() {
	thread = std::thread(&ClockPart::threadBody, this);
}*/

void ClockPart::setWhatToDo(int command) {
	cout << "ClockPart got command " << command << endl;
	mutex.lock();
	whatToDo = command;
	mutex.unlock();
}

/*void ClockPart::performCommand(int command) {
	mutex.lock();
	whatToDo = 0;
	mutex.unlock();
}*/
