

all: game
	make run

game: main.o
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

main.o: main.cpp
	g++ -Wall -c main.cpp

run: 
	./game

clear:
	rm -rf *o game