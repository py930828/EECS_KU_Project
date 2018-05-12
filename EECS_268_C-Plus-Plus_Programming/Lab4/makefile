Lab04: main.o Test.o  PreconditionViolationException.o Test_Stack.o
	g++ -g -std=c++11 -Wall -o Lab04 main.o Test.o  PreconditionViolationException.o Test_Stack.o

main.o: StackInterface.h Stack.h main.cpp Node.h Test.h
	g++ -g -std=c++11 -Wall -c main.cpp

Test.o: Test.h Stack.h Test.cpp
	g++ -c -g -std=c++11 -Wall Test.cpp

Test_Stack.o: Test_Stack.h Test_Stack.cpp
	g++ -c -g -std=c++11 -Wall Test_Stack.cpp

PreconditionViolationException.o: PreconditionViolationException.h PreconditionViolationException.cpp
	g++ -c -g -std=c++11 -Wall PreconditionViolationException.cpp

clean:
	rm *.o Lab04
