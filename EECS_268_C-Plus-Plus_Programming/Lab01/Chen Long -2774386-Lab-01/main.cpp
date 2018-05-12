#include<iostream>
#include<string>
#include"Colosseum.h"
#include"Pokemon.h"
int main()
{
	char again;	
	Pokemon p1,p2;
	Colosseum m;
	do
	{
		std::cout<<"Player 1, build your pokemon!"<<'\n'<<"=====================";
		m.userBuild(p1);
		std::cout<<"Player 2, build your pokemon!"<<'\n'<<"====================="<<std::endl;
		m.userBuild(p2);
		std::cout<<"Choosing which player to go first"<<std::endl;
		m.play(p1,p2);
		std::cout<<"Do you want to play again?(y/n):";
		std::cin>>again;
	}while(again=='y');
	std::cout<<"Thanks for playing";
}
		
