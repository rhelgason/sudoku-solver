backtrack: build-backtrack
	./backtrack board.txt

build-backtrack: src/Backtrack.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h
	g++ -std=c++11 -Wall -o backtrack src/Backtrack.cpp src/Grid.cpp src/Box.cpp

algorithmX: build-algorithmX
	./algorithmX board.txt

build-algorithmX: src/AlgorithmX.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h
	g++ -std=c++11 -Wall -o algorithmX src/AlgorithmX.cpp src/Grid.cpp src/Box.cpp

clean:
	rm -f *.exe
