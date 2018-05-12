/*
 * Executive.h
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include<iostream>
#include<string>
#include<fstream>
#include"DriversLicenseRecord.h"
using namespace std;
class Executive
{
private:
	DriversLicenseRecord* arrayptr;
	int line;
	int tempint;
	string tempname;
	string tempregv;
public:
	void run();
	Executive(char* x);
	void arrname();
	void arrage();
	void arrregv();
};
#endif /* EXECUTIVE_H_ */
