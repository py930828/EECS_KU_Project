#include"LinkedList.h"
#include <iostream>
using namespace std;
LinkedList::LinkedList()
{
	m_front=nullptr;
	m_size=0;
}
LinkedList::~LinkedList()
{
	while(isEmpty()==false)
	{
		removeBack();
	}
}

bool LinkedList::isEmpty()  const
{
	if(m_size==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int LinkedList::size() const
{
	return m_size;
}
bool LinkedList::search(int value) const
{
	Node* node1=m_front;
	bool found=false;
	while(node1!=nullptr && !found)
	{
		if(node1->getvalue()==value)
		{
			found=true;
		}
		node1=node1->getNext();
	}
	return found;
}

void LinkedList::addFront(int value)
{
	if(isEmpty()==true)
	{
		Node* node1=new Node();
		node1->setvalue(value);
		m_front=node1;
		m_size++;
	}
	else
	{
		Node* node1=new Node();
		node1->setvalue(value);
		node1->setNext(m_front);
		m_front=node1;
		m_size++;
	}
}
void LinkedList::addBack(int value)
{
	if(isEmpty()==true)
	{
		Node* node1=new Node();
		node1->setvalue(value);
		m_front=node1;
		m_size++;
	}
	else
	{
		Node* node1=new Node();
		node1->setvalue(value);
		Node* tempptr=m_front;
		while(tempptr->getNext()!=nullptr)
		{
			tempptr=tempptr->getNext();
		}
		tempptr->setNext(node1);
		m_size++;
	}
}
void LinkedList::printList() const
{
	Node* node1=m_front;
	if(isEmpty()==false)
	{
		while(!(node1==nullptr))
		{
			cout<<node1->getvalue()<<" ";
			node1=node1->getNext();
		}
	}
	else
	{
		cout<<"";
	}
}
bool LinkedList::removeBack()
{
	if(m_size>1)
	{
		Node* node1=m_front;
		while(!(node1->getNext()->getNext()==nullptr))
		{
			node1=node1->getNext();
		}
		delete node1->getNext();
		node1->setNext(nullptr);
		m_size--;
		return true;
	}
	else if(m_size==1)
	{
		delete m_front;
		m_front=nullptr;
		m_size--;
		return true;
	}
	else
	{
		return false;
	}
}
bool LinkedList::removeFront()
{
	if(m_size>0)
	{
		Node* node1=m_front;
		m_front=m_front->getNext();
		delete node1;
		m_size--;
		return true;
	}
	else
	{
		return false;
	}
}
vector<int> LinkedList::toVector() const
{
	Node* node1=m_front;
	vector<int> vec;
	if(isEmpty()==false)
	{
		vec.push_back(node1->getvalue());
		while(!(node1->getNext()==nullptr))
		{
			node1=node1->getNext();
			vec.push_back(node1->getvalue());
			
		}
	}
	return vec;
}








