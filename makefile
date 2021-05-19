all: main.o btermios.o
	g++ -Wall main.o btermios.o -o prog

main.o: main.cpp
	g++ -c main.cpp

btermios.o: btermios.cpp
	g++ -c btermios.cpp
