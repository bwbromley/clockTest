/*
 * MainClass.h
 *
 *  Created on: Feb 18, 2016
 *      Author: bromley
 */

#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include "Class1.h"
#include "Class2.h"

class MainClass {
public:
	MainClass();
	virtual ~MainClass();
	Class1* class1;
	Class2* class2;
};

#endif /* MAINCLASS_H_ */
