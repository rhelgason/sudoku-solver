backtrack: build-backtrack
	./backtrack board.txt

build-backtrack: src/Backtrack.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h src/Node.cpp src/Node.h
	g++ -std=c++11 -Wall -o backtrack src/Backtrack.cpp src/Grid.cpp src/Box.cpp src/Node.cpp

algorithmX: build-algorithmX
	./algorithmX board.txt

build-algorithmX: src/AlgorithmX.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h src/Node.cpp src/Node.h
	g++ -std=c++11 -Wall -o algorithmX src/AlgorithmX.cpp src/Grid.cpp src/Box.cpp src/Node.cpp

dancingLinks: build-dancingLinks
	./dancingLinks board.txt

build-dancingLinks: src/DancingLinks.cpp src/Grid.cpp src/Grid.h src/Box.cpp src/Box.h src/Node.cpp src/Node.h
	g++ -std=c++11 -Wall -o dancingLinks src/DancingLinks.cpp src/Grid.cpp src/Box.cpp src/Node.cpp

clean:
	rm -f *.exe