/*
 * main.cpp
 *
 *  Created on: 2016/3/7
 *      Author: long
 */
#include"Executive.h"
#include"Board.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(int arg, char* argv[])
{
        int ch[4];
        ch[0]=atoi(argv[1]);
        ch[1]=atoi(argv[2]);
        ch[2]=atoi(argv[3]);
        ch[3]=atoi(argv[4]);
        Executive exe(ch);
        return 0;
}

