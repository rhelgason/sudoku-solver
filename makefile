all: src/main.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h
	g++ -std=c++11 -Wall -o main src/main.cpp src/Grid.cpp src/Box.cpp

run: main
	./main board.txt

clean:
	rm -f main.exe
