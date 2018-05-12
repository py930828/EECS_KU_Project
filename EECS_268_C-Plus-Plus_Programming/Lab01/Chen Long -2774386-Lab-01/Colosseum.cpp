#include"Colosseum.h"
using namespace std;
Colosseum::Colosseum()
{
	d20=Dice(20);
	d6=Dice(6);
}
void Colosseum::userBuild(Pokemon&p)
{
	std::string name="";
	int hp=0;
	int attackLevel=0;
	int defenseLevel=0;
	cout<<"Please name your pokemon:"<<endl;
	cin>>name;
	p.setname(name);
	std::cout<<"How many hit points will it have? (1-50):"<<endl;
	do
	{
		cin>>hp;
		if((hp<1)||(hp>50))
		{
			std::cout<<"the hp must be between 1-50.";
			std::cin>>name;
		}
	}while((hp<1)||(hp>50));
	std::cout<<endl;
	p.setHP(hp);
	std::cout<<"Split fifty points between attack level and defense level."<<'\n'<<"Enter your attack level (1-49)"<<endl;
	do
	{
		std::cin>>attackLevel;
		if((attackLevel<1)||(attackLevel>49))
		{
			std::cout<<"Sorry. The defense level must be between 1 and 15: ";
			std::cin>>attackLevel;
		}
	}while((attackLevel<1)||(attackLevel>49));
	p.setattackLevel(attackLevel);
	std::cout<<"Enter your defense level (1- "<<(50-attackLevel)<<"): ";
	do
	{
		cin>>defenseLevel;
		if((defenseLevel<1)||(defenseLevel>(50-attackLevel)))
		{
			std::cout<<"Sorry. THe defense level should be between (1- "<<(50-attackLevel)<<")";
			std::cin>>defenseLevel;
		}
	}while((defenseLevel<1)||(defenseLevel>(50-attackLevel)));
	p.setdefenseLevel(defenseLevel);
	std::cout<<endl;
}
bool Colosseum::attack(const Pokemon&attacker, Pokemon&defender)
	{
		int a=0;
		int b=0;
		int c=0;
		std::cout<<attacker.getname()<<" is attacking "<<defender.getname()<<endl;
		int ra=d20.roll();
		std::cout<<attacker.getname()<<" rolls an attack bonus of "<<ra<<endl;
		int rd=d20.roll();
		std::cout<<defender.getname()<<" rolls a defense bonus of "<<rd<<endl;
		if((ra+attacker.getattackLevel())>(rd+defender.getdefenseLevel()))
		{
			std::cout<<"The attack hits dealing 3-D6 damage!";
			a=d6.roll();
			b=d6.roll();
			c=d6.roll();
			cout<<"The rols are "<<a<<", "<<b<<" and "<<c<<"totaling: "<<a+b+c<<" damage!"<<endl;
		defender.reduceHP(a+b+c);
			if(defender.getHP()>0)
			{
				cout<<defender.getname()<<" has "<<defender.getHP()<<" hit points left"<<endl;//fix
			}
		}
		if((ra+attacker.getattackLevel())<(rd+defender.getdefenseLevel()))
		{
			cout<<"The attack missed!"<<endl;
		}
		if(defender.getHP()<=0)
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}
void Colosseum::play(Pokemon& p1, Pokemon&p2)
	{
		Dice d2(2);
		int x=d2.roll();
		bool over=0;
		if(x==0)
		{
			std::cout<<"player 1"<<" will go first"<<endl;
		}
		else
		{
			std::cout<<"player 2"<<" will go first"<<endl;
		}
		if(x==0)
		{
			for(int i=1;i<=10&&over==0;i++)
			{
				cout<<"Round "<<i<<"!"<<'\n'<<endl;
				if(attack(p1,p2)==1)
				{
					cout<<p2.getname()<<" has been defeated!"<<endl;
					over=1;
				}
				if(p2.getHP()>0)
				{
					if(attack(p2,p1)==1)
					{
					cout<<p1.getname()<<" has been defeated!"<<endl;
					over=1;
					}
				}
				if(i==10)
				{
					cout<<"Both fighters are still standing! It's a draw!"<<endl;
				}
				cout<<endl;
			}
		}
		else
		{
			for(int i=1;i<=10&&over==0;i++)
			{
				cout<<"Round "<<i<<"!"<<'\n'<<endl;
				if(attack(p1,p2)==1)
				{
					cout<<p2.getname()<<" has been defeated!"<<endl;
					over=1;
				}
				if(p2.getHP()>0)
				{
					if(attack(p2,p1)==1)
					{
						cout<<p1.getname()<<" has been defeated!"<<endl;
						over=1;
					}
				}
				if(i==10)
				{
					cout<<"Both fighters are still standing! It's a draw!"<<endl;
				}
			}
		}
			

}



		
		
	
		
		
	
		
	
