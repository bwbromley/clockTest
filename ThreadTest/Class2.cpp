/*
 * Class2.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#include "Class2.h"
#include <unistd.h>

Class2::Class2(): whatToDo(0) {
}

Class2::~Class2() {
	whatToDo = -1;
	if(thread2.joinable())
		thread2.join();
	cout << "Class2 Destructor called ----------------" << endl;
}

void Class2::threadBody() {
	while (whatToDo != -1) {
		cout << "Class2 says Hello" << endl;
		mutex.lock();
		int temp = whatToDo;
		mutex.unlock();
		if (temp)
			performCommand(temp);
		usleep(1000000);
	}
	cout << "Class2 Exiting" << endl;
}

void Class2::start() {
	thread2 = std::thread(&Class2::threadBody, this);
}

void Class2::setWhatToDo(int command) {
	cout << "Class2 got command " << command << endl;
	mutex.lock();
	whatToDo = command;
	mutex.unlock();
}

void Class2::performCommand(int command) {
	mutex.lock();
	whatToDo = 0;
	mutex.unlock();
}
