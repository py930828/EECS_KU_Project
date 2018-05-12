/*
 * Node.h
 *
 *  Created on: 2016/2/15
 *      Author: long
 */
#ifndef NODE_H_
#define NODE_H_
using namespace std;
template <class T> class Node
{
private:
	T m_value;
	Node<T>* m_next;
public:
/* @ pre none
* @ post initialize m_next to null pointer and m_value to 0
* return none
*/
	Node();
/* @ pre m_value=0
* @ post set the value of m_value to val
* @ return none
*/
	void setValue(T val);
/* @ pre m_next=nullptr
* @ post set the value of m_next to prev
* @ return none
*/
	void setNext(Node<T>* prev);
/* @ pre none
* @ post return the value of m_value
* return m_value
*/
	T getValue() const;
/* @ pre none
* @ post return the getNext pointer
* @ return the getNext pointer
*/
	Node<T>* getNext() const;
};
#include "Node.hpp"
#endif
