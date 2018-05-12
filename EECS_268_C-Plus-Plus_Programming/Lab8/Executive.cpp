/*
 * Executive.cpp
 *
 *  Created on: 2016/4/5
 *      Author: long
 */
#include "Executive.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <locale> 
#include <cstring>
using namespace std;
Executive::Executive(char* arg)
{
	z="";
	ifstream fstream(arg);
	while(fstream>>z)
	{
		file.push_back(z);
	}
	run();
}
bool Executive::checktext(int n)
{
	for(unsigned i=0;i<file.at(n).size();i++)
	{
		if(!(isalpha(file.at(n)[i])||isdigit(file.at(n)[i])||file.at(n)[i]==','||file.at(n)[i]=='!'||file.at(n)[i]=='@'||file.at(n)[i]=='#'||file.at(n)[i]=='$'||file.at(n)[i]=='%'||file.at(n)[i]=='&'||file.at(n)[i]=='*'||file.at(n)[i]=='('||file.at(n)[i]==')'||file.at(n)[i]==' '||file.at(n)[i]=='\''))
		{
			cout<<file.at(n)[i];
			return false;
		}
	}
	return true;
}
bool Executive::stringtag()
{
	for(unsigned x=0;x<file.size();x++)
	{
		if(file.at(x)=="<tab>")
		{
			tab++;
		}
		if(Istag(x)&&!Istag(x+1)&&tab!=0)
		{
			s2.push("	");
		}
		if(x>0&&!Istag(x)&&!Isclosetag(x))
		{
			if(checktext(x))
			{
				s2.push(file.at(x)+" ");
			}
			else
			{
				cout<<"Illegal character of "<<file.at(x)<<endl;
				return false;
			}
		}
		if(file.at(x)=="</p>")
		{
			s2.push("\n");
			s2.push("\n");
		}
		if(file.at(x)=="<listItem>")
		{
			s2.push("*");
		}
		if(file.at(x)=="</listItem>")
		{
			s2.push("\n");
		}
		
		if(file.at(x)=="</tab>")
		{
			tab--;
			s2.push("\n");
		}
	}
	try
	{
		while(!s2.isEmpty())
		{
			s1.push(s2.peek());
			s2.pop();
		}
	}
	catch(exception& e)
	{
	}
	return true;
}
bool Executive::Istag(int x)
{
	if(file.at(x)=="<tab>")
	{
		return true;
	}
	if(file.at(x)=="<p>")
	{
		return true;
	}
	if(file.at(x)=="<listItem>")
	{
		return true;
	}
	return false;
}
bool Executive::tagchecker(int x)
{
	if(!s1.isEmpty())
	{
		if(s1.peek()=="<tab>")
		{
			if(file.at(x)=="</tab>")
			{
				return true;
			}
		}
		if(s1.peek()=="<p>")
		{
			if(file.at(x)=="</p>")
			{
				return true;
			}
		}
		if(s1.peek()=="<listItem>")
		{
			if(file.at(x)=="</listItem>")
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}
bool Executive::Isclosetag(unsigned x)
{
	if(file.at(x)=="</tab>")
	{	
		return true;
	}
	if(file.at(x)=="</p>")
	{
		return true;
	}
	if(file.at(x)=="</listItem>")
	{
		return true;
	}
	return false;
}

bool Executive::Stacktag(unsigned x)
{
	if(x<file.size()-1)
	{
		if(Istag(x))
		{
			s1.push(file.at(x));
			if(Stacktag(x+1))
			{
				return true;
			}
			return false;
		}
		else if(Isclosetag(x+1))
		{
			if(tagchecker(x+1))
			{
				s1.pop();
				if(Stacktag(x+1))
				{
					return true;
				}
				return false;
			}
			else
			{
				cout<<"Invalid XML file: unexpected closing "<<file.at(x+1)<<" tag encountered";
				return false;
			}
		}
		if(Stacktag(x+1))
		{
			return true;
		}
		return false;
	}
	try
	{
		s1.peek();
		cout<<"Invalid XML file: unexpected "<<s1.peek()<<" tag encountered.";
		return false;
	}
	catch(exception& e)
	{
		return true;
	}
}
void Executive::run()
{
	if(Stacktag(0))
	{
		if(stringtag())
		{
			try
			{
				while(!s1.isEmpty())
				{
					cout<<s1.peek();
					s1.pop();
				
				}
			}
			catch(exception& e)
			{
			}
		}
	}
}























/*
bool Executive::checkValid(unsigned x, unsigned y, string s)
{
	newtag=false;
	closetag=false;
	cout<<"find a open tag of "<<s<<"at "<<x<<"  ";
	for(unsigned i=x;i<=y;i++)//find the close tag;
	{
		if(Isclosetag(i,y,s))
		{
			cout<<"find a close tag of "<<file.at(i)<<" at"<<i<<"  ";
			closetag=true;
			cout<<"search starts at "<<x+1<<", ends at "<<i-1<<endl;
			for(unsigned j=x+1;j<=i-1;j++)//To find if there is a new opentag.
			{
				if(Istag(j))
				{
					cout<<"Find a new Tag of"<<file.at(j)<<"search starts at "<<j<<", ends at "<<i-1<<endl;
					if(checkValid(j,i-1, file.at(j)))
					{
						newtag=true;
						return true;
					}
					else
					{
						cout<<"can't find a closetag of "<<file.at(j)<<endl;
						return false;
					}
				}
			}
		}
		if(!newtag&&closetag)//Continues finding new tag;
		{
			cout<<i<<endl;
			if(Istag(i+1))
			{
				cout<<"Continues at "<<i+1<<endl;
				if(checkValid(i+1,y,file.at(i+1)))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			
		}
	}
	if(!closetag)
	{
		cout<<"can't find closetag"<<endl;
		return false;
	}
	return true;
}






bool Executive::isValid(string check, unsigned x)
{
	if(check=="<tab>")
	{
		for(unsigned i=x; i<file.size();i++)
		{
			if(file.at(i)=="</tab>")
			{
				closetab++;
				return true;
			}
		}
		return false;
	}	
	if(check=="<p>")
	{
		for(unsigned i=x; i<file.size();i++)
		{
			if(file.at(i)=="</p>")
			{
				closep++;
				return true;
			}
		}
		return false;
	}
	if(check=="<listItem>")
	{
		cout<<"get into listItem"<<endl;
		for(unsigned i=x; i<file.size();i++)
		{
			if(file.at(i)=="</listItem>")
			{
				closelistItem++;
				return true;
			}
		}
		cout<<"return false for listItem"<<endl;
		return false;
	}
	return true;

}

bool Executive::checktag(string check)
{
	if(check=="<tab>")
	{
		tab++;
		return true;
	}
	if(check=="<p>")
	{
		p++;
		return true;
	}
	if(check=="<listItem>")
	{
		listItem++;
		return true;
	}
	else
	{
		return false;
	}
}

bool Executive::run()
{
	for(unsigned i=0;i<file.size();i++)
	{
		if(checktag(file.at(i)))
		{
			if(!isValid(file.at(i),i))
			{
				cout<<"Invalid XML file: unexpected closing tab tag encountered."<<endl;
				return false;
			}
			else
			{
				
		}
		
	}
	cout<<tab<<" "<<closetab<<" "<<p<<" "<<closep<<" "<<listItem<<" "<<closelistItem<<endl;
	if(!(tab==closetab&&p==closep&&listItem==closelistItem))
	{
		cout<<"Invalid XML file: unexpected closing tab tag encountered."<<endl;
		return false;
	}
	cout<<"Valid input"<<endl;


	return true;
}*/
