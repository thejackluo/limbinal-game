CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = game.o Event.o EventManager.o Item.o People.o Player.o NPC.o Location.o Map.o metadata.o

all: game

game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f game $(OBJS)