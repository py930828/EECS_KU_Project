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
template <class T> int Stack<T>::size() const
{
	return m_size;
}
template <class T>void Stack<T>::push(const T value)
{
	if(isEmpty()==true)
	{
		Node<T>* node1=new Node<T>();
		node1->setValue(value);
		m_front=node1;
		m_size++;
	}
	else
	{
		Node<T>* node1=new Node<T>();
		node1->setValue(value);
		node1->setNext(m_front);
		m_front=node1;
		m_size++;
	}
}

template <class T>void Stack<T>::pop() throw(PreconditionViolationException)
{
	if(isEmpty()==true)
	{
		throw (PreconditionViolationException("Pop attempted on an empty stack"));
	}
	else
	{
		Node<T>* node1=m_front->getNext();
		delete m_front;
		m_front=node1;
		m_size--;
		//cout<<m_front->getValue();
	}
}
template <class T>T Stack<T>::peek() const throw(PreconditionViolationException)
{
	if(isEmpty()==true)
	{
		throw (PreconditionViolationException("Peek attempted on an empty stack"));
	}
	else
	{
		return m_front->getValue();
	}
}
template <class T>std::vector<T> Stack<T>::toVector() const
{
	Node<T>* node1=m_front;
	vector<int> vec;
	if(isEmpty()==false)
	{
		vec.push_back(node1->getValue());
		while(!(node1->getNext()==nullptr))
		{
			node1=node1->getNext();
			vec.push_back(node1->getValue());
			
		}
	}
	return vec;
}

