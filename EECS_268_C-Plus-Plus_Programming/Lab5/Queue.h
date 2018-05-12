 /*
 * Node.h
 *
 *  Created on: 2016/2/21
 *      Author: long
 */
#ifndef QUEUE_H_
#define QUEUE_H_
#include "QueueInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
using namespace std;
template <class T> class Queue:public QueueInterface <T>{
public:
/*
 *@pre: none
 *@post:initialize private varaible
 *@return:pointer and int
*/
Queue();
/* 
 *@pre:might be some garbage vable
 *@post:clean all value in the stack and member valaible
 *@return:empty pointer and int;
 */
~Queue();
/*  
 *@pre:none
 *@post:return true or false depend on the stack
 *@return:boolean value
 */
bool isEmpty() const;
/*  
 *@pre:none
 *@post:check if the size of the stack is equal or bigger than 1
 *@return:True if is bigger than 1, false if it's equal to 1
 */
bool size() const;
/*  
 *@pre:none
 *@post:add one node before the stack
 *@return:none
 */
void enqueue(const T& newEntry) throw (PrecondViolatedExcep);
/*  
 *@pre:none
 *@post:remove one nodel on the top of the stack
 *@return:none
 */
void dequeue() throw (PrecondViolatedExcep);
/*  
 *@pre:none
 *@post:print the value of nodel of the top stack
 *@return:Type T depend on the value
 */
T peekFront() const throw(PrecondViolatedExcep);
/*  
 *@pre:none
 *@post:print the value of nodel of the second stack
 *@return:Type T depend on the value
 */
T peekNext() const throw(PrecondViolatedExcep);


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
#include "Queue.hpp"
#endif
