/*
 * Node.hpp
 *
 *  Created on: 2016/4/5
 *      Author: long
 */
using namespace std;
template <class T> Node<T>::Node()
{
	m_next=nullptr;
}
template <class T> void Node<T>::setValue(T val)
	{
		m_value=val;
	}
template <class T> void Node<T>::setNext(Node<T>* prev)
	{
		m_next=prev;
	}
template <class T> T Node<T>::getValue() const
	{
		return m_value;
	}
template <class T> Node<T>* Node<T>::getNext() const
	{
		return m_next;
	}
