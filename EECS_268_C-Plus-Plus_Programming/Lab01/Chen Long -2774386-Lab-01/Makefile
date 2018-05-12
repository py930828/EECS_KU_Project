Lab01:Dice.o Colosseum.o Pokemon.o main.o
	g++ -g -Wall -o Lab01 Dice.o Colosseum.o Pokemon.o main.o

Colosseum.o: Colosseum.h Colosseum.cpp
	g++ -c -g -Wall Colosseum.cpp

main.o: Colosseum.h main.cpp
	g++ -c -g -Wall main.cpp

Pokemon.o: Pokemon.h Pokemon.cpp
	g++ -c -g -Wall Pokemon.cpp

Dice.o: Dice.h Dice.cpp
	g++ -c -g -Wall Dice.cpp

clean:
	rm *.o Lab01
