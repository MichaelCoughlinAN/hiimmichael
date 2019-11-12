CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = output
OBJS = main.o PrecondViolatedExcep.o Disc.o Track.o DiscList.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	rm $(OBJS) output  

PrecondViolatedExcep.o: PrecondViolatedExcep.cpp PrecondViolatedExcep.h
Track.o: Track.cpp Track.h Disc.h LinkedList.h ListInterface.h \
 PrecondViolatedExcep.h Node.h Node.cpp LinkedList.cpp
DiscList.o: DiscList.cpp DiscList.h
main.o: main.cpp LinkedList.h ListInterface.h PrecondViolatedExcep.h \
 Node.h Node.cpp LinkedList.cpp Disc.h Track.h DiscList.h
Disc.o: Disc.cpp Disc.h Track.h LinkedList.h ListInterface.h \
 PrecondViolatedExcep.h Node.h Node.cpp LinkedList.cpp DiscList.h
