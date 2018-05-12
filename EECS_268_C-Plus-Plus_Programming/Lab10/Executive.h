#ifndef _EXECUTIVE_H_
#define _EXECUTIVE_H_

#include <fstream>
#include <string>
#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include "DictionaryEntry.h"
#include "Test.h"
class Executive
{
private:
  std::string words;
  std::string def;
  std::string str;
  std::ifstream infile;
  bool flag;
  DictionaryEntry* ptr;
public:
  Executive(char* arg);
  void run();
  static void visit(DictionaryEntry& de);
};

#endif
