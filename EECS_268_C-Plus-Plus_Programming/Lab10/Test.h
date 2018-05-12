#ifndef _TEST_H_
#define _TEST_H_
#include <string>
#include <iostream>
#include "BinarySearchTree.h"
#include "DictionaryEntry.h"
using namespace std;
class Test
{
private:
  string word;
  string defn;
  DictionaryEntry* ptr;
public:
  Test();
  void testAdds(BinarySearchTree<DictionaryEntry, string> bst);
  void testRemoves(BinarySearchTree<DictionaryEntry, string> bst);
  void testWriteToFile(BinarySearchTree<DictionaryEntry, string> bst);
  static void visit(DictionaryEntry& de);
};

#endif
