all: src/main.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h
	g++ -Wall -o main src/main.cpp src/Grid.cpp src/Box.cpp

run: main.exe
	./main board.csv

clean:
	rm -f main.exe
