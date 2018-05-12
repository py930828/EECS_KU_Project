Lab08: Executive.o main.o PrecondViolatedExcep.o
	g++ -g -Wall -std=c++11 Executive.o main.o PrecondViolatedExcep.o -o Lab08

main.o: Executive.h main.cpp StackInterface.h Stack.h Node.h
	g++ -c -g -std=c++11 -Wall main.cpp

Executive.o: Executive.h Executive.cpp StackInterface.h Stack.h Node.h PrecondViolatedExcep.h
	g++ -c -g -std=c++11 -Wall Executive.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.h PrecondViolatedExcep.cpp
	g++ -c -g -std=c++11 -Wall PrecondViolatedExcep.cpp

clean:
	rm *.o Lab08
