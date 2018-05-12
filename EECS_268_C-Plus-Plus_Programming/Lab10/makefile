Lab10: main.o  Executive.o DictionaryEntry.o Test.o
	g++ -g -std=c++11 -Wall -o Lab10 main.o Executive.o DictionaryEntry.o Test.o

main.o: BinaryNode.h BinarySearchTree.h main.cpp NotFoundException.h Executive.h DictionaryEntry.h
	g++ -g -std=c++11 -Wall -c main.cpp

DictionaryEntry.o: DictionaryEntry.h DictionaryEntry.cpp BinaryNode.h BinarySearchTree.h Executive.h
	g++ -g -std=c++11 -Wall -c DictionaryEntry.cpp

Executive.o: Executive.h Executive.cpp BinarySearchTree.h DictionaryEntry.h BinaryNode.h
	g++ -g -std=c++11 -Wall -c Executive.cpp

Test.o: Test.h Test.cpp
	g++ -g -std=c++11 -Wall -c Test.cpp

clean:
	rm *.o Lab10
