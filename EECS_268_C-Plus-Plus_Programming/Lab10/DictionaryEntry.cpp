#include "DictionaryEntry.h"

using namespace std;
DictionaryEntry::DictionaryEntry(string w, string d)
{
	word=w;
	defn=d;
	setword(word);
	setdefn(defn);
}
DictionaryEntry::DictionaryEntry()
{
}
void DictionaryEntry::setword(string wd)
{
	word=wd;
}
void DictionaryEntry::setdefn(string de)
{
	defn=de;
}
string DictionaryEntry::getword() const
{
	return word;
}
string DictionaryEntry::getdefn() const
{
	return defn;
}


bool DictionaryEntry::operator > (const DictionaryEntry D) const
{
	if(this->getword().length() > D.getword().length())
	{
		for(unsigned i=0;i<D.getword().length();i++)
		{
			if(tolower(this->getword().at(i))>tolower(D.getword().at(i)))
			{
				return true;
			}
			else if(tolower(this->getword().at(i))==tolower(D.getword().at(i)))
			{
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		for(unsigned i=0;i<this->getword().length();i++)
		{
			if(this->getword().at(i)>D.getword().at(i))
			{
				return true;
			}
			else if(tolower(this->getword().at(i))==tolower(D.getword().at(i)))
			{
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool DictionaryEntry::operator < (const string D) const
{
	if(this->getword().length() > D.length())
	{
		for(unsigned i=0;i<D.length();i++)
		{
			if(tolower(this->getword().at(i))>tolower(D.at(i)))
			{
				return false;
			}
			else if(tolower(this->getword().at(i))==tolower(D.at(i)))
			{
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		for(unsigned i=0;i<this->getword().length();i++)
		{
			if(this->getword().at(i)>D.at(i))
			{
				return false;
			}
			else if(tolower(this->getword().at(i))==tolower(D.at(i)))
			{
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

bool DictionaryEntry::operator == (const string D) const
{
	if(this->getword().length() == D.length())
	{
		for(unsigned i=0;i<D.length();i++)
		{
			if(tolower(this->getword().at(i))==tolower(D.at(i)))
			{
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
