#include "Test.h"
using namespace std;
Test::Test()
{
  word="";
  defn="";
}

void Test::visit(DictionaryEntry& de)
 {
   cout<<de.getword()<<"  "<<de.getdefn()<<endl;
 }

void Test::testAdds(BinarySearchTree<DictionaryEntry, string> bst)
{
  cout<<"Please input the word you wish to define"<<endl;
  cin>>word;
  cout<<"Please input the definition you wish to define for "<<word<<"."<<endl;
  cin>>defn;
  ptr=new DictionaryEntry(word,defn);
  bst.add(*ptr);
  bst.inorderTraverse(visit);
}
void Test::testRemoves(BinarySearchTree<DictionaryEntry, string> bst)
{
  string words="";
  cout<<"Please input the word you wish to remove"<<endl;
  cin>>words;
  cout<<"after the word???";
  while(!bst.contains(words))
  {
    cout<<words<<" is not contained in the dictionary, please try again."<<endl;
    cin>>words;
  }
  bst.removeNode(bst.getPtr(words));
  cout<<"Test????"<<endl;
  bst.inorderTraverse(visit);
}
void Test::testWriteToFile(BinarySearchTree<DictionaryEntry, string> bst)
{

}
