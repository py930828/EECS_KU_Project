/*
 * Executive.h
 *
 *  Created on: 2016/4/5
 *      Author: long
 */
#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include<iostream>
#include<string>
#include<fstream>
#include "Stack.h"
#include "StackInterface.h"
#include "PrecondViolatedExcep.h"
#include "Node.h"
#include <vector>
using namespace std;
class Executive
{
private:
	string z;
	bool newtag=false;
	bool closetag=false;
	vector <string> file;
	int tab=0;
public:
	/* @ pre none
	* @ post call the method in Executive class to accomplish this programm.
	* return none
	*/
	void run();
	/* @ pre none
	* @ post initialize the private varaible and put the value into the vector
	* return none
	*/
	Executive(char* arg);
	/* @ pre false
	* @ post implement the characteristic of each tag
	* return true if all charater are successed checking.
	*/
	bool stringtag();
	/* @ pre false
	* @ post put all the contents into stack 
	* return true if all charater are successed checking.
	*/
	bool Stacktag(unsigned x);
	/* @ pre none
	* @ post check if it is a closetag
	* return true if it is a closetag, false if it isn't
	*/
	bool Isclosetag(unsigned x);
	/* @ pre none
	* @ post check if it is a open tag
	* return true if it is a open tag, false if it isn't
	*/
	bool Istag(int n);
	/* @ pre none
	* @ post check if the opentag and closetag fit with each other
	* return true if it matches up, false elsewise
	*/
	bool tagchecker(int x);
	/* @ pre none
	* @ post check if the character fits the limitation of this programm.
	* return true if yes, false elsewise
	*/
	bool checktext(int x);
	Stack<string> s1;
	Stack<string> s2;
};
#endif
