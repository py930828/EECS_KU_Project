Trains:Executive.o main.o
	g++ -g -Wall -std=c++11 -o Trains Executive.o main.o -lpthread

main.o: Executive.h main.cpp
	g++ -c -g -std=c++11 -Wall main.cpp

Executive.o: Executive.h Executive.cpp TrainRecord.hpp
	g++ -c -g -std=c++11 -Wall Executive.cpp

clean:
	rm *.o Trains
