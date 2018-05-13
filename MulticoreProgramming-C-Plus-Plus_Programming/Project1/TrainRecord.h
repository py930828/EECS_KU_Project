using namespace std;
#ifndef TRAINRECORD_H_
#define TRAINRECORD_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
using namespace std;
template <class T> class TrainRecord{
private:
  list<T> *l;
  string name;

public:
  TrainRecord();
  void setstops(T stops);
  void setname(T name);
  void pop_front();
  string getname() const;
  int size() const;
  T GetCurrentStop() const;
  T GetNextStop() const;

};
#include "TrainRecord.hpp"
#endif
