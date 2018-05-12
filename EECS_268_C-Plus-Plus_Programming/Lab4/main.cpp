#include "StackInterface.h"
#include "Stack.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <math.h> 
using namespace std;
int main()
{
	int x;
	int y;
	int z;
	int i;
	string q="";
		do
		{
			i=0;
			x=0;
			y=0;
			z=0;
			Stack<int> si;
			cout<<"Input a number: ";
			cin>>x;
			y=x;
			cout<<x<<" backwards is ";
			if(x<0)
			{
				y=x*(1-2);
				cout<<"-";
			}
			if(x==0)
			{
				cout<<" 0";
			}
			while(!y==0)
			{
				z=y%10;
				cout<<z;
				si.push(z);
				y=y/10;
			}
			z=0;
			while(!si.isEmpty())
			{
				y=y+(si.peek()*pow(10,z));
				si.pop();
				z++;
			}
			cout<<endl;
			if(x<0)
			{
				if(x==(-y))
				{
					cout<<x<<" is a palindrome";
				}
				else
				{
					cout<<x<<" is not a palindrome";
				}
			}
			else if(x-y==0)
			{
				cout<<x<<" is a palindrome";
			}
			else
			{
				cout<<x<<" is not a palindrome";
			}
			cout<<endl;
			si.~Stack();
			cout<<"Do you want to quit (y/n)?: ";
			cin>>q;
			while(!((q.compare("y"))||(q.compare("n"))))
			{
				cout<<"Please type in valid input(y/n)";
				cin>>q;
			}
			i++;
		}while(q=="n");
	return(0);
}
		
