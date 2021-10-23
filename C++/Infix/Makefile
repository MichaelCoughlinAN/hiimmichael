CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = output
OBJS = main.o DivideByZeroExcep.o Infix.o 

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : clean
clean :
	rm $(OBJS) output  

main.o : main.cpp StackInterface.h LinkedStack.h LinkedStack.cpp Node.h Node.cpp Infix.h DivideByZeroExcep.h  
DivideByZeroExcep.o :  DivideByZeroExcep.cpp  DivideByZeroExcep.h
Infix.o : Infix.cpp Infix.h StackInterface.h LinkedStack.h Node.h Node.cpp 
