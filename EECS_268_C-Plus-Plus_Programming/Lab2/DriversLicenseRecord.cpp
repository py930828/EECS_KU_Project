/*
 * DriversLicenseRecord.cpp
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
#include "DriversLicenseRecord.h"
using namespace std;
DriversLicenseRecord::DriversLicenseRecord()
{
	m_fn="";
	m_ln="";
	m_age=0;
	m_regv="";
	m_dln=0;
}
	void DriversLicenseRecord::setfn(string fn)
	{
		m_fn=fn;
	}
	void DriversLicenseRecord::setln(string ln)
	{
		m_ln=ln;
	}
	void DriversLicenseRecord::setage(int age)
	{
		m_age=age;
	}
	void DriversLicenseRecord::setregv(string regv)
	{
		m_regv=regv;
	}
	void DriversLicenseRecord::setdln(int dln)
	{
		m_dln=dln;
	}
	string DriversLicenseRecord::getfn() const
	{
		return m_fn;
	}
	string DriversLicenseRecord::getln()const
	{
		return m_ln;
	}
	int DriversLicenseRecord::getage() const
	{
		return m_age;
	}
	string DriversLicenseRecord::getregv() const
	{
		return m_regv;
	}
	int DriversLicenseRecord::getdln() const
	{
		return m_dln;
	}


