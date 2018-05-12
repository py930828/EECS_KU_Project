/*
 * DriversLicenseRecord.h
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
using namespace std;
#ifndef DRIVERSLICENSERECORD_H_
#define DRIVERSLICENSERECORD_H_

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class DriversLicenseRecord
{
private:
	string m_fn;
	string m_ln;
	int m_age;
	string m_regv;
	int m_dln;

public:
	DriversLicenseRecord();
	void setfn(string fn);
	void setln(string ln);
	void setage(int age);
	void setregv(string regv);
	void setdln(int dln);
	string getfn() const;
	string getln() const;
	int getage() const;
	string getregv() const;
	int getdln() const;
};
#endif /* DRIVERSLICENSERECORD_H_ */

