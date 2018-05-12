Lab05: main.o  PrecondViolatedExcep.o 
	g++ -g -std=c++11 -Wall -o Lab05 main.o  PrecondViolatedExcep.o 

main.o: StackInterface.h Stack.h main.cpp Node.h QueueInterface.h Queue.h
	g++ -g -std=c++11 -Wall -c main.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.h PrecondViolatedExcep.cpp
	g++ -c -g -std=c++11 -Wall PrecondViolatedExcep.cpp

clean:
	rm *.o Lab05
