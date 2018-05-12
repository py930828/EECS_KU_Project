#ifndef POKEMON_H
#define POKEMON_H
#include<string>
class Pokemon
{
public:
  Pokemon();
  void reduceHP(int amount);
  void setHP(int hp);
  void setattackLevel(int attacklevel);
  void setdefenseLevel(int defenselevel);
  void setname(std::string name);
  int getHP() const;
  int getattackLevel() const;
  int getdefenseLevel() const;
  std::string getname() const;
private:
	int m_hp;
	int m_attackLevel;
	int m_defenseLevel;
	std::string m_name;
};
#endif
