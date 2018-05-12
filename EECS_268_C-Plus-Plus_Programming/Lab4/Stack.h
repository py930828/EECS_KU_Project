/*
 * Node.h
 *
 *  Created on: 2016/2/15
 *      Author: long
 */
#ifndef Stack_H_
#define Stack_H_
#include "StackInterface.h"
#include "Node.h"
#include "PreconditionViolationException.h"
#include <vector>
using namespace std;
template <class T> class Stack:public StackInterface <T>{
public:
/*
 *@pre: none
 *@post:initialize private varaible
 *@return:pointer and int
*/
Stack();
/* 
 *@pre:might be some garbage vable
 *@post:clean all value in the stack and member valaible
 *@return:empty pointer and int;
 */
~Stack();
/*  
 *@pre:none
 *@post:return true or false depend on the stack
 *@return:boolean value
 */
bool isEmpty() const;
/*  
 *@pre:none
 *@post:add one node before the stack
 *@return:none
 */
void push(const T value);
/*  
 *@pre:none
 *@post:remove one nodel on the top of the stack
 *@return:none
 */
void pop() throw(PreconditionViolationException);
/*  
 *@pre:none
 *@post:print the value of nodel of the top stack
 *return:Type T depend on the value
 */
T peek() const throw(PreconditionViolationException);
/*  
 *@pre:none
 *@post:distribute the node into vector
 *return:vector value
 */
vector<T> toVector() const;
/*  
 *@pre:int value
 *@post:update m_size value;
 *@return:m_size
 */
int size() const;
private:
/*  
 *@pre:the status of previous position
 *@post:update m_front
 *@return:pointer m_front
 */
Node<T>* m_front;
/*  
 *@pre:int
 *@post:int
 *@return:int
 */
int m_size;
};
#include "Stack.hpp"
#endif