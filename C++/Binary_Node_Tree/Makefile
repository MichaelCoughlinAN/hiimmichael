CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = output
OBJS = main.o PrecondViolatedExcep.o NotFoundException.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	rm $(OBJS) output *~ *# 

main.o: main.cpp BinaryNodeTree.h BinaryTreeInterface.h \
 NotFoundException.h PrecondViolatedExcep.h BinaryNode.h BinaryNode.cpp \
 BinaryNodeTree.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.cpp PrecondViolatedExcep.h
NotFoundException.o: NotFoundException.cpp NotFoundException.h
