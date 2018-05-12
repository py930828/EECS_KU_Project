#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include "bubbleSort.cpp"
#include "insertionSort.cpp"
#include "mergeSort.cpp"
#include "quickSort.cpp"
#include "selectionSort.cpp"
using namespace std;
double algorithmSelect(string algorithm,double array[],int size)
{
	clock_t start=0;
	double duration=0;
	if(algorithm=="bubble")
	{
		start=clock();
		bubbleSort<double> (array,size);
		duration=(clock()-start);
		duration=duration/CLOCKS_PER_SEC;
	}
	else if(algorithm=="insertion")
	{
		start=clock();
		insertionSort<double> (array,size);
		duration=(clock()-start);
		duration=duration/CLOCKS_PER_SEC;
	}
	else if(algorithm=="merge")
	{
		start=clock();
		mergeSort<double> (array,size);
		duration=(clock()-start);
		duration=duration/CLOCKS_PER_SEC;
	}
	else if(algorithm=="quick")
	{
		start=clock();
		quickSort<double> (array,0,size);
		duration=(clock()-start);
		duration=duration/CLOCKS_PER_SEC;
	}
	else if(algorithm=="selection")
	{
		start=clock();
		selectionSort<double> (array,size);
		duration=(clock()-start);
		duration=duration/CLOCKS_PER_SEC;
	}
	else
	{
		cout<<"Invalid algorithm type, please try again"<<endl;
	}
	return duration;
}
int main(int argc, char* argv[])
{
	int size=atoi(argv[1]);
	string order=argv[2];
	string algorithm=argv[3];
	double array[size];
	srand48(5);
	if(order=="ascending")
	{
		for(int i=0;i<size;i++)
		{
			array[i] = 0.001*static_cast<double>(i);
		}
		cout<<algorithmSelect(algorithm,array,size);
	}
	else if(order=="descending")
	{
		for(int i=0;i<size;i++)
		{
			array[i] = 0.001*static_cast<double>(size - i - 1);
		}
		cout<<algorithmSelect(algorithm,array,size);
	}
	else if(order=="random")
	{
		for(int i=0;i<size;i++)
		{
			array[i] = drand48() * 100000.0;
		}
		cout<<algorithmSelect(algorithm,array,size);
	}
}
