CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = tictactoe
OBJS = main.o board.o player.o game.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

.PHONY : clean
clean:
	rm $(OBJS)

main.o : main.cpp game.h board.h player.h
board.o : board.cpp board.h
player.o : player.cpp player.h board.h
game.o : game.cpp game.h board.h player.h
