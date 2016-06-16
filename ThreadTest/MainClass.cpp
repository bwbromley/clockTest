/*
 * MainClass.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#include "MainClass.h"
#include <unistd.h>

MainClass::MainClass() {
}

MainClass::~MainClass() {
}

int main(int argc, char** argv) {
	MainClass mainClass;
	mainClass.class1 = new Class1();
	mainClass.class2 = new Class2();
	mainClass.class1->start();
	mainClass.class2->start();
	usleep(10000000);
	mainClass.class1->setWhatToDo(-1);
	//delete &mainClass.class1;
	usleep(10000000);
	mainClass.class2->setWhatToDo(-1);
	return 0;
}

