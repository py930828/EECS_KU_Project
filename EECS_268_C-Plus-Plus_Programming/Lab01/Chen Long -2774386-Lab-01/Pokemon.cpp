#include "Pokemon.h"
Pokemon::Pokemon()
{
		m_hp=0;
		m_attackLevel=0;
		m_defenseLevel=0;
		m_name="";
	}
	void Pokemon::setHP(int health)
	{
		m_hp=health;
	}
	void Pokemon::setattackLevel(int attacklevel)
	{
		m_attackLevel=attacklevel;
	}
	void Pokemon::setdefenseLevel(int defenselevel)
	{
		m_defenseLevel=defenselevel;
	}
	void Pokemon::setname(std::string name)
	{
		m_name=name;
	}
	void Pokemon::reduceHP(int amount)
	{
		m_hp=m_hp-amount;
	}
	int Pokemon::getHP() const
	{
		return m_hp;
	}
	int Pokemon::getattackLevel() const
	{
		return m_attackLevel;
	}
	int Pokemon::getdefenseLevel() const
	{
		return m_defenseLevel;
	}
	std::string Pokemon::getname() const
	{
		return m_name;
	}
