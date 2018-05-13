#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include "Barrier.h"
#include "TrainRecord.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class Executive
{
private:
	int nTrains;
	int nStations;
	int stops;
	int TimeStep; // Current timestep;
  string mystr;
	Barrier b;
	vector<int> CurrentTrain; // Keep track of how many trains are still running
	vector< vector<int> > TimeStepRecord; // Record the total timestep for each train
	vector< vector<int> > v; // v< previous_stop, current_stop >
public:
	mutex _mutex;
	Executive(char* x);
  TrainRecord<int> *listptr;
	void run(int TrainNum);
	void ThreadInitial();
	void printPrev();
	void CheckArrived( int TrainNum );
	void Finish_Print();
	bool StopRepeat( int previous_stop, int current_stop ); //check if the stop is repeating
};
#endif /* EXECUTIVE_H_ */
