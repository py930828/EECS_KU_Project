#ifndef StackINTERFACE_H_
#define StackINTERFACE_H_
#include <vector>
#include "PreconditionViolationException.h"
using namespace std;
template <typename T> 
class StackInterface
{
public:
virtual ~StackInterface(){};
virtual bool isEmpty() const=0;
virtual void push(const T value)=0;
virtual void pop() throw (PreconditionViolationException)=0;
virtual T peek() const throw (PreconditionViolationException)=0;
virtual int size() const=0;
virtual vector<T> toVector() const = 0;
};
#endif

