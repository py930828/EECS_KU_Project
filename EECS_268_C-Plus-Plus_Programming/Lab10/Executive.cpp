 #include "Executive.h"
 #include <iostream>
 #include <stdexcept>
 Executive::Executive(char* arg)
 {
   words="";
   def="";
   str=arg;
 }
void Executive::visit(DictionaryEntry& de)
 {
   cout<<de.getword()<<endl;
 }

void Executive::run()
{
  ifstream infile(str);
  BinarySearchTree<DictionaryEntry, string> bst;
  DictionaryEntry de("rock", "a hard object often found on the ground");
	bst.add(de);
	while(infile>>str)
	{
    words=str;
    getline(infile,str);
    def=str;
    ptr=new DictionaryEntry(words,def);
    bst.add(*ptr);
    words="";
    def="";
	}
  Test t;
  t.testRemoves(bst);
  /*std::cout<<"Which mode do you wish to enter?(1,2)"<<'\n'<<"1. print mode"<<'\n'<<"2. Test mode"<<endl;
  int x=0;
  std::cin>>x;
  if(x==1)
  {
    std::cout<<"Which Traversal order do you want?(Inorder,Preorder,Postorder)"<<endl;
    std::cin>>str;
    if(str=="Inorder"||str=="inorder")
  	{
  		bst.inorderTraverse(visit);
  	}
  	if(str=="Preorder"||str=="preorder")
  	{
  		bst.preorderTraverse(visit);
  	}
  	if(str=="Postorder"||str=="postorder")
  	{
  		bst.postorderTraverse(visit);
  	}
  }
  else if(x==2)
  {
    std::cout<<"Please name the file you want to copy on:"<<endl;
    std::cin>>str;
    ofstream outfile(str);
    std::cout<<"Please select the mode you want to test (1,2)'\n'1. Add Word'\n'2. Remove Word"<<endl;
    std::cin>>x;
    Test t;
    if(x==1)
    {
      t.testAdds(bst);
    }
    if(x==2)
    {
      t.testRemoves(bst);
    }
  }
  else
  {
    std::cout<<"Invalid input, please check again.";
  }
  bst.~BinarySearchTree();*/
  cout<<"finished???"<<endl;
}
