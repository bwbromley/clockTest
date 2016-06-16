/*
 * Class1.h
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#ifndef CLASS1_H_
#define CLASS1_H_

#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::string;
using std::cout;
using std::endl;

class Class1 {
public:
	Class1();
	virtual ~Class1();
	void threadBody();
	void start();
	void setWhatToDo(int command);
private:
	std::thread thread1;
	int whatToDo;
	std::mutex mutex;
	void performCommand(int command);
};

#endif /* CLASS1_H_ */
