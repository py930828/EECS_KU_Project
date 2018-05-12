Lab04:Stack.o  Node.o main.o Test.o Test_LinkedList.o PreconditionViolationException.o
	g++ -g -std=c++11 -Wall -o Lab04 LinkedList.o  Node.o main.o Test.o Test_LinkedList.o PreconditionViolationException.o

Stack.o: Stack.h Stack.cpp
	g++ -c -g -std=c++11 -Wall Stack.cpp

main.o: Test_LinkedList.h main.cpp
	g++ -c -g -std=c++11 -Wall main.cpp

Node.o: Node.h Node.cpp
	g++ -c -g -std=c++11 -Wall Node.cpp

Test.o: Test.h Test.cpp
	g++ -c -g -std=c++11 -Wall Test.cpp

Test_LinkedList.o: Test_LinkedList.h Test_LinkedList.cpp
	g++ -c -g -std=c++11 -Wall Test_LinkedList.cpp
clean:
	rm *.o Lab03
