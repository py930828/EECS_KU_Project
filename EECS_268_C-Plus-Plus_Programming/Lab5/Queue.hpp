using namespace std;
#include <iostream>
template <class T> Queue<T>::Queue()
{
	m_front=nullptr;
	m_size=0;
}
template <class T> Queue<T>::~Queue()
{
	while(isEmpty()==false)
	{
		dequeue();
	}
}
template <class T> bool Queue<T>::isEmpty() const
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
template <class T> bool Queue<T>::size() const
{
	if(m_size>1)
	{
		return true;
	}
	else if(m_size==1)
	{
		return false;
	}
}
template <class T>void Queue<T>::enqueue(const T& newEntry) throw (PrecondViolatedExcep)
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

template <class T>void Queue<T>::dequeue() throw (PrecondViolatedExcep)
{
	if(isEmpty()==true)
	{
		throw (PrecondViolatedExcep("No customer is being served"));
	}
	else
	{
		Node<T>* node1=m_front->getNext();
		delete m_front;
		m_front=node1;
		m_size--;
	}
}
template <class T>T Queue<T>::peekFront() const throw(PrecondViolatedExcep)
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
template <class T>T Queue<T>::peekNext() const throw(PrecondViolatedExcep)
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

