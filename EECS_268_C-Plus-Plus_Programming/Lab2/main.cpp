/*
 * main.cpp
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
#include"Executive.h"
#include"DriversLicenseRecord.h"
#include<iostream>
int main(int argc, char* argv[])
{
    Executive exec(argv[1]);
    exec.run();
    return 0;
}
