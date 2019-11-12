CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = output
OBJS = main.o isFloatingPoint.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	rm $(OBJS)

main.o : main.cpp isFloatingPoint.h
isFloatingPoint.o : isFloatingPoint.cpp isFloatingPoint.h
