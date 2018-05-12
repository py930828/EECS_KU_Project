#include<iostream>
#include<string>
#include"Pokemon.h"
#include"Dice.h"
class Colosseum
{
private:
	Dice d20;
	Dice d6;
public:
	Colosseum();
	void userBuild(Pokemon& p);
	bool attack(const Pokemon&attacker, Pokemon& defender);
	void play(Pokemon& p1, Pokemon&p2);
};
