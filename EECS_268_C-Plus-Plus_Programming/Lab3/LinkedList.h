/*
 * LinkedList.h
 *
 *  Created on: 2016/2/8
 *      Author: long
 */
using namespace std;
#include <iostream>
#include<vector>
#include "Node.h"
class LinkedList
{
private:
Node* m_front;
int m_size;

public:
/* @pre none
* @post initialize the size and front pointer
*
*/ 
LinkedList();
/* @pre none
* @post delete every node in the ist
* @return nothing
*/
~LinkedList();
/* @ pre false
* @ post 
* @return the boolean value for true
*/
bool isEmpty() const;
/* @ pre none
* @post none
* @return the value of size
*/
int size() const;
/* @ pre none
* post none
* return the boolean value of found if found a value
*/
bool search (int value) const;
/* @ pre none
* @post printing each node in the list
* @return none
*/
void printList() const;
/* @ pre none
* @ post adding the node to the end of the list
* @return none
*/
void addBack(int value);
/* @ pre none
* @post adding node to the beginning of the list
* @return none
*/
void addFront(int value);
/* @ pre false
* @ post removing node from the back 
* @ return true if it's removed, return false if the list is empty
*/
bool removeBack();
/* @ pre false
* @ post remving node from front
* return true if it's removed, return false if the list is empty 
*/
bool removeFront();
/* @ pre none
* post distributing each node to a vector and name an int to each vector
*return an array of vector
*/
vector<int>toVector() const;
};
