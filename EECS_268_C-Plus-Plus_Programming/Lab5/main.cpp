#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "StackInterface.h"
#include "Stack.h"
#include "Queue.h"
#include "QueueInterface.h"
using namespace std;
int main(int argc, char* argv[])
{
	string temp="";
	bool stack=false;
	Stack<string> s1;
	Queue<string> q1;
	if(argc!=2)
	{
		cout<<"Need to input the inputfile"<<endl;
		return (0);
	}
	ifstream fstream(argv[1]);
	while(fstream>>temp)
	{
		if(temp.substr(0,3).compare("VIP") == 0)
		{
			if(s1.isEmpty())
			{
				s1.push(temp);
			}
			else if(stoi(temp.substr(3,1))>stoi(s1.peek().substr(3,1)))
			{
				s1.push(temp);
			}
			else
			{
				cout<<temp<<"See "<<s1.peek()<<" being served, immediately leaves."<<endl;
			}
		}
		else if(temp.compare("show")==0)
		{
			try
			{
				cout<<s1.peek()<<" is currently being served; "<<q1.peekFront()<<" is waiting at the front of the queue."<<endl;
			}
			catch(exception& e)
			{
				if(s1.isEmpty()&&q1.isEmpty()==false)
				{
					cout<<"No VIP customer is at the front of the stack, "<<q1.peekFront()<<" is currently being served; "<<endl;
				}
				else if(q1.isEmpty()&&s1.isEmpty()==false)
				{
					cout<<s1.peek()<<" is currently being served; no customer is at the front of the queue"<<endl;
				}
				else
				{

					cout<<"no one is waiting, Lydia rests"<<endl;
				}
			}


		}
		else if(temp.compare("done")==0)
		{
			try
			{
				stack=false;
				s1.peek();
				q1.peekFront();
				cout<<s1.peek()<<" is done; ";
				stack=true;
				s1.pop();
				cout<<s1.peek()<<" is resuming";
				
			}
			catch(exception& e)
			{
				cout<<"Test";
				if(s1.isEmpty()&&q1.isEmpty()==false&&stack)
				{
					cout<<q1.peekFront()<<" is resuming; "<<endl;
				}
				else if(s1.isEmpty()&&q1.isEmpty()==false&&stack==false)
				{
					cout<<q1.peekFront()<<" is done, ";
					q1.dequeue();
					if(!q1.isEmpty())
					{
						cout<<q1.peekFront()<<" is resuming."<<endl;
					}
					else
					{
						cout<<"No customer is waiting, Lydia rests"<<endl;
					}
				}
				else if(q1.isEmpty()&&s1.isEmpty()==false)
				{
					cout<<" no customer is at the front of the queue"<<endl;
				}
				else
				{

					cout<<"no one is waiting, Lydia rests"<<endl;
				}
			}

		}
		else
		{
			q1.enqueue(temp);
		}
	}
	return (0);
}


