CXX = g++
CXXFLAGS = -std=c++17
OBJS = game.o Event.o People.o Item.o Location.o metadata.o

all: game

game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o game $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f game $(OBJS)
