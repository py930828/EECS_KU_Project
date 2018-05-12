#include"Node.h"
#include <iostream>
using namespace std;
Node::Node()
{
	//m_value=0;
	m_next=nullptr;
}
	void Node::setvalue(int val)
	{
		m_value=val;
	}
	void Node::setNext(Node* prev)
	{
		m_next=prev;
	}
	int Node::getvalue() const
	{
		return m_value;
	}
	Node* Node::getNext() const
	{
		return m_next;
	}
