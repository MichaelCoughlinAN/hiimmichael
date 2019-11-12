CXX = g++
CXXFLAGS = -Wall -ansi -std=c++0x
TARGET = output
OBJS = main.o isPalindrome.o PrecondViolatedExcep.o

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	rm $(OBJS) output  

main.o: main.cpp isPalindrome.h LinkedStack.h StackInterface.h Node.h \
 Node.cpp PrecondViolatedExcep.h LinkedStack.cpp LinkedQueue.h \
 QueueInterface.h LinkedQueue.cpp
isPalindrome.o: isPalindrome.cpp isPalindrome.h LinkedStack.h \
 StackInterface.h Node.h Node.cpp PrecondViolatedExcep.h LinkedStack.cpp \
 LinkedQueue.h QueueInterface.h LinkedQueue.cpp
PrecondViolatedExcep.o: PrecondViolatedExcep.cpp PrecondViolatedExcep.h
