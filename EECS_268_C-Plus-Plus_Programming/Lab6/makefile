Lab06: main.o  PrecondViolatedExcep.o 
	g++ -g -std=c++11 -Wall -o Lab06 main.o  PrecondViolatedExcep.o 

main.o: StackInterface.h Stack.h main.cpp Node.h
	g++ -g -std=c++11 -Wall -c main.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.h PrecondViolatedExcep.cpp
	g++ -c -g -std=c++11 -Wall PrecondViolatedExcep.cpp

clean:
	rm *.o Lab06
