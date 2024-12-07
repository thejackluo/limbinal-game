CXX = g++
CXXFLAGS = -std=c++17

all: game 

# Compile and run game
game: game.o
	$(CXX) $(CXXFLAGS) -o game game.o
	./game

game.o: game.cpp
	$(CXX) $(CXXFLAGS) -c game.cpp


# Clean up
clean:
	rm -f game *.o
