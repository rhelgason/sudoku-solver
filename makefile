build-backtrack: src/backtrack.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h
	g++ -std=c++11 -Wall -o backtrack src/backtrack.cpp src/Grid.cpp src/Box.cpp

backtrack: build-backtrack
	./backtrack board.txt

clean:
	rm -f *.exe
