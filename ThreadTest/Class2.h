/*
 * Class2.h
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#ifndef CLASS2_H_
#define CLASS2_H_

#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::string;
using std::cout;
using std::endl;

class Class2 {
public:
	Class2();
	virtual ~Class2();
	void threadBody();
	void start();
	void setWhatToDo(int command);
private:
	std::thread thread2;
	int whatToDo;
	void performCommand(int command);
	std::mutex mutex;
};

#endif /* CLASS2_H_ */
