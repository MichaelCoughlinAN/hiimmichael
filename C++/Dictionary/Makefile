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

PrecondViolatedExcep.o: PrecondViolatedExcep.cpp PrecondViolatedExcep.h
NotFoundException.o: NotFoundException.cpp NotFoundException.h
main.o: main.cpp ArrayDictionary.h DictionaryInterface.h \
 NotFoundException.h Entry.h Entry.cpp BinarySearchTree.h \
 BinaryTreeInterface.h PrecondViolatedExcep.h BinaryNode.h BinaryNode.cpp \
 BinaryNodeTree.h BinaryNodeTree.cpp BinarySearchTree.cpp \
 ArrayDictionary.cpp
