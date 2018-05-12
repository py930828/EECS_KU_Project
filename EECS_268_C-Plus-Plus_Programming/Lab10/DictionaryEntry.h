#ifndef _DICTIONARYENTRY_H
#define _DICTIONARYENTRY_H
#include <string>
#include <iostream>
#include <cctype>
#include <clocale>
#include "BinaryNode.h"
using namespace std;
class DictionaryEntry
{
private:
	string word;
	string defn;
public:
	DictionaryEntry(string w, string d);
	DictionaryEntry();
	string getword() const;
	string getdefn() const;
	void setword(string wd);
	void setdefn(string de);
	bool operator > (const DictionaryEntry D) const;
	bool operator < (const string D) const;
	bool operator == (const string D) const;

};
#endif
