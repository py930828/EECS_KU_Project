using namespace std;
#include <iostream>
template <class T> Stack<T>::Stack()
{
	m_front=nullptr;
	m_size=0;
}
template <class T> Stack<T>::~Stack()
{
	while(isEmpty()==false)
	{
		pop();
	}
}

template <class T> bool Stack<T>::isEmpty() const
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
template <class T> bool Stack<T>::size() const
{
	if(m_size>1)
	{
		return true;
	}
	if(m_size==1)
	{
		return false;
	}
}
template <class T>void Stack<T>::push(const T& newEntry) throw (PrecondViolatedExcep)
{
	if(isEmpty()==true)
	{
		Node<T>* node1=new Node<T>();
		node1->setValue(newEntry);
		m_front=node1;
		m_size++;
	}
	else
	{
		Node<T>* node1=new Node<T>();
		node1->setValue(newEntry);
		node1->setNext(m_front);
		m_front=node1;
		m_size++;
	}
}
template <class T>void Stack<T>::pop() throw(PrecondViolatedExcep)
{
	if(isEmpty()==true)
	{
		throw (PrecondViolatedExcep("No VIP is being served"));
	}
	else
	{
		Node<T>* node1=m_front->getNext();
		delete m_front;
		m_front=node1;
		m_size--;
	}
}
template <class T>T Stack<T>::peek() const throw(PrecondViolatedExcep)
{
	if(isEmpty()==true)
	{
		throw (PrecondViolatedExcep("No customer is being served"));
	}
	else
	{
		return m_front->getValue();
	}
}
template <class T>T Stack<T>::peekNext() const throw(PrecondViolatedExcep)
{
	if(isEmpty()==true)
	{
		throw (PrecondViolatedExcep("No customer is being served"));
	}
	else
	{
		return (m_front->getNext())->getValue();
	}
}


