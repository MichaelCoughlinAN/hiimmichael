CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = PowerCalculator
OBJS = main.o PowerCalculator.o

&(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.0 : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ @<

.PHONY : clean
clean:
	rm $(OBJS)

main.o : main.cpp PowerCalculator.h
PowerCalculator.o : PowerCalculator.cpp PowerCalculator.h 
