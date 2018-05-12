/*
 * Node.h
 *
 *  Created on: 2016/2/8
 *      Author: long
 */
#ifndef NODE_H_
#define NODE_H_
#include <iostream>
using namespace std;
class Node
{
private:
	int m_value;
	Node* m_next;
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
	void setvalue(int val);
/* @ pre m_next=nullptr
* @ post set the value of m_next to prev
* @ return none
*/
	void setNext(Node* prev);
/* @ pre none
* @ post return the value of m_value
* return m_value
*/
	int getvalue() const;
/* @ pre none
* @ post return the getNext pointer
* @ return the getNext pointer
*/
	Node* getNext() const;
};
#endif
