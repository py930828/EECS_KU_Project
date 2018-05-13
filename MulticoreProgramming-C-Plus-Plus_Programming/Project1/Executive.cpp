#include "Executive.h"
#include <fstream>
using namespace std;
Executive::Executive(char* arg)
{
  ifstream fstream(arg);
  nTrains = 0; nStations = 0; stops = 0; //initializations
  fstream >> nTrains; fstream >> nStations;
  listptr = new TrainRecord<int>[nTrains];
  for(int i = -1; getline(fstream, mystr); i++){
    stringstream ss(mystr);
    listptr[i].setname(i);
    while(ss >> stops){
      listptr[i].setstops(stops);
    }
  }
  //now we have a 2D-matrix of size (nTrains, 2), value of -1
  v.resize( nTrains , vector<int>( 0 ) );
  TimeStepRecord.resize( nTrains , vector<int>( 0 ) );
  for( int i = 0; i < nTrains; i++)
  {
    CurrentTrain.push_back(i);
  }
  TimeStep = 0;

}

void Executive::ThreadInitial()
{
  while( CurrentTrain.size() != 0 )
  {
    thread** t = new thread*[nTrains];
    for(int i = 0; i < nTrains; i++)
    {
      t[i] = new thread(&Executive::run, this, CurrentTrain[i]);
    }
    for(int i = 0; i < nTrains; i++)
    {
      t[i] -> join();
    }
    nTrains = CurrentTrain.size();
    for( unsigned int i = 0; ( i < v.size() ); i++ ){ v[i].clear();} // clear the v value, doesn't need to be resized.
    TimeStep ++;
  }
  cout<<"Simulation complete.\n"<<endl;
  Finish_Print();
}

void Executive::run( int TrainNum )
{
    _mutex.lock();
    if( StopRepeat( listptr[TrainNum].GetNextStop(), listptr[TrainNum].GetCurrentStop() ) )
    {
      cout<<"train "<<listptr[TrainNum].getname()<<" must stay at station "<<listptr[TrainNum].GetCurrentStop()<<endl;
    }
    else
    {
      v[TrainNum].push_back( listptr[TrainNum].GetCurrentStop() ); // record the previous stop to the vector
      listptr[TrainNum].pop_front();
      v[TrainNum].push_back( listptr[TrainNum].GetCurrentStop() ); // record the current_stop to the vector
      cout<<"At time step: "<<TimeStep<<" train "<<listptr[TrainNum].getname()<<" is going from station "<<v[TrainNum].front()<<" to station "<<listptr[TrainNum].GetCurrentStop()<<endl;
      CheckArrived( TrainNum ); // if arrived, delete TrainNum from CurrentTrain vector;
    }
    _mutex.unlock();
    b.barrier(nTrains);
}

void Executive::CheckArrived( int TrainNum )
{
  if( listptr[TrainNum].size() == 1 ) // check if the train arrived at the final station
  {
    for( unsigned int i = 0; ( i < CurrentTrain.size() ); i++) // delete TrainNum from CurrentTrain vector;
    {
      if( TrainNum == CurrentTrain[i] )
      {
        CurrentTrain.erase( CurrentTrain.begin() + i );
        TimeStepRecord[TrainNum].push_back(TimeStep);
        return;
      }
    }
  }
}

void Executive::Finish_Print()
{
  for(unsigned int i = 0; i < v.size(); i++)
  {
    cout<<"Train "<<listptr[i].getname()<<" completed its route at time step "<<TimeStepRecord[i].front()<<endl;
  }
}

bool Executive::StopRepeat( int previous_stop, int current_stop )
{
  for ( unsigned int i = 0; i < v.size(); i++)
  {
    if( v[i].size() != 0 ) // to make sure the vector is initialized to prevent core dumped.
    {
      if( previous_stop == v[i].front() || previous_stop == v[i].back() )
      {
        if( current_stop == v[i].front() || current_stop == v[i].back() )
        {
          return true;
        }
      }
    }
  }
  return false;
}
