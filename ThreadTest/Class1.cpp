/*
 * Class1.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#include "Class1.h"
#include <unistd.h>

Class1::Class1(): whatToDo(0) {
}

Class1::~Class1() {
	whatToDo = -1;
	if(thread1.joinable())
		thread1.join();
	cout << "Class1 Destructor called -----------------" << endl;
}

void Class1::threadBody() {
	while (whatToDo != -1) {
		cout << "Class1 says Hello" << endl;
		mutex.lock();
		int temp = whatToDo;
		mutex.unlock();
		if (temp)
			performCommand(temp);
		usleep(1000000);
	}
	cout << "Class1 Exiting" << endl;
}

void Class1::start() {
	thread1 = std::thread(&Class1::threadBody, this);
}

void Class1::setWhatToDo(int command) {
	cout << "Class1 got command " << command << endl;
	mutex.lock();
	whatToDo = command;
	mutex.unlock();
}

void Class1::performCommand(int command) {
	mutex.lock();
	whatToDo = 0;
	mutex.unlock();
}
