 #include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include "StackInterface.h"
#include "Stack.h"
#include <locale> 
using namespace std;
int main(int argc, char* argv[])
{
	Stack<string> s1;
	Stack<string> s2;
	string x="";
	string q="";
	char word[50];
	string ctos="";
	do
	{
		s1.~Stack();
		s2.~Stack();
		cout<<"Enter a string: ";
		cin>>x;
		strcpy (word, x.c_str());
		for(int i=0;i<x.length();i++)
		{
			if(isalpha(word[i]))
			{
				string s(1, word[i]);
				s1.push(s);
			}
			else if((word[i]=='/'||word[i]=='+'||word[i]=='-'||word[i]=='*')&&i!=x.length()-1)
			{
				try
				{
					s2.push(")");
					s2.push(s1.peek());
					s1.pop();
					string s(1, word[i]);
					s2.push(s);
					s2.push(s1.peek());
					s1.pop();
					s2.push("(");
					try
					{
						ctos="";
						while(s2.peek()!="")
						{
							ctos+=s2.peek();
							s2.pop();
						}
					}
					catch(exception& e)
					{
					}
					s1.push(ctos);
				}
				catch(exception& e)
				{
					cout<<"You entered an invalid postfix string: it is missing operands"<<endl;
					x="";
					s1.~Stack();
					s2.~Stack();
				}
			}
			else if(i==x.length()-1)
			{
				if(word[i]=='/'||word[i]=='+'||word[i]=='-'||word[i]=='*')			{
					try
					{
						s2.push(")");
						s2.push(s1.peek());
						s1.pop();
						string s(1, word[i]);
						s2.push(s);
						s2.push(s1.peek());
						s1.pop();
						s2.push("(");
					}
					catch(exception& e)
					{
						cout<<"You entered an invalid postfix string: it is missing operands"<<endl;
						x="";
						s1.~Stack();
						s2.~Stack();
					}
				}
			}
			else
			{
				cout<<"You entered an invalid postfix string: it contains the illegal character "<<word[i]<<endl;
				x="";
				s1.~Stack();
				s2.~Stack();
			}
		}
		if(x!="")
		{
			try
			{
				s1.pop();
				cout<<"You entered an invalid postfix string: it is missing one or more operators"<<endl;
				x="";
				s1.~Stack();
				s2.~Stack();
			}
			catch(exception& e)
			{
				try
				{
					cout<<"You entered a valid postfix string. The equivalent infix: ";
					while(s2.peek()!="")
					{
						cout<<s2.peek();
						s2.pop();
					}
				}
				catch(exception& e)
				{
				}
			}
			cout<<endl;
		}
	}while(q!="y");
	return (0);
}


