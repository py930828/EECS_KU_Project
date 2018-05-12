Lab07: Executive.o main.o Board.o
	g++ -g -Wall -std=c++11 -o Lab07 Executive.o main.o Board.o

Board.o: Board.h Board.cpp
	g++ -c -g -std=c++11 -Wall Board.cpp

main.o: Executive.h main.cpp
	g++ -c -g -std=c++11 -Wall main.cpp

Executive.o: Executive.h Executive.cpp
	g++ -c -g -std=c++11 -Wall Executive.cpp

clean:
	rm *.o Lab07

