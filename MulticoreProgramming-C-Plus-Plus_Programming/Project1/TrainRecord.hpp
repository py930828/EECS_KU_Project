using namespace std;
template <class T> TrainRecord<T>::TrainRecord(){
  l = new list<T>;
  name = "";
}

template <class T> void TrainRecord<T>::setstops(T stops){
  l->push_back(stops);
}

template <class T> T TrainRecord<T>::GetCurrentStop() const{
  return l->front();
}

template <class T> int TrainRecord<T>::size() const{
  return l->size();
}

template <class T> T TrainRecord<T>::GetNextStop() const{
  auto it = l->begin();
  auto nx = next( it, 1 );
  return *nx;
}

template <class T> void TrainRecord<T>::pop_front() {
  l->pop_front();
}

template <class T> string TrainRecord<T>::getname() const{
  return name;
}

template <class T> void TrainRecord<T>::setname( T num) {
  if( num == 0 )
  {
    name = "A";
  }
  else if( num == 1 )
  {
    name = "B";
  }
  else if( num == 2 )
  {
    name = "C";
  }
  else if( num == 3 )
  {
    name = "D";
  }
  else if( num == 4 )
  {
    name = "E";
  }
  else if( num == 5 )
  {
    name = "F";
  }
}
