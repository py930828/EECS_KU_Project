/*
 * Executive.cpp
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
#include"Executive.h"
#include<fstream>
#include<iostream>
#include"DriversLicenseRecord.h"
using namespace std;
Executive::Executive(char* arg)
{
	ifstream fstream(arg);
	line=0;
	tempint=0;
	tempname="";
	tempregv="";
	fstream>>line;
	arrayptr=new DriversLicenseRecord[line];
	for(int i=0;i<line;i++)
	{
		fstream >> tempname;
		arrayptr[i].setfn(tempname);
		fstream >> tempname;
		arrayptr[i].setln(tempname);
		fstream >> tempint;
		arrayptr[i].setage(tempint);
		fstream >> tempregv;
		arrayptr[i].setregv(tempregv);
		fstream >> tempint;
		arrayptr[i].setdln(tempint);
	}
}
void Executive::arrname()
{
	string name="";
	cout<<"Enter last name: ";
	cin>>name;
	cout<<endl;
	for(int i=0;i<line;i++)
	{
		if(arrayptr[i].getln()==name)
		{
			cout<<"Records: "<<arrayptr[i].getfn()<<" "<<arrayptr[i].getln()<<" "<<arrayptr[i].getage()<<" "<<arrayptr[i].getregv()<<" "<<arrayptr[i].getdln();
			cout<<endl;
		}
	}
}
void Executive::arrage()
{
	int age=0;
	cout<<"Enter age: ";
	cin>>age;
	cout<<endl;
	for(int i=0;i<line;i++)
	{
		if(arrayptr[i].getage()==age)
		{
			cout<<"Records: "<<arrayptr[i].getfn()<<" "<<arrayptr[i].getln()<<" "<<arrayptr[i].getage()<<" "<<arrayptr[i].getregv()<<" "<<arrayptr[i].getdln();
			cout<<endl;
		}
	}
}
void Executive::arrregv()
{
	string vote="";
	cout<<"Enter vote status(Y or N):";
	cin>>vote;
	cout<<endl;
	for(int i=0;i<line;i++)
	{
		if(arrayptr[i].getregv()==vote)
		{
			cout<<"Records: "<<arrayptr[i].getfn()<<" "<<arrayptr[i].getln()<<" "<<arrayptr[i].getage()<<" "<<arrayptr[i].getregv()<<" "<<arrayptr[i].getdln();
			cout<<endl;
		}
	}

}
void Executive::run()
{
	int x=0;
	do
	{
	cout<<"1: Query lastname"<<endl<<"2: Query age range"<<endl<<"3: Query registered voters"<<endl<<"4: Quit"<<endl;
	cin>>x;
	switch(x)
	{
		case 1:
			arrname();
			break;
		case 2:
			arrage();
			break;
		case 3:
			arrregv();
			break;
		case 4:
			break;
		default:cout<<"input should be between 1-4."<<endl;
		cin>>x;
	}
	}while(x!=4);
	cout<<"Thanks for using our system!"<<endl;
}
