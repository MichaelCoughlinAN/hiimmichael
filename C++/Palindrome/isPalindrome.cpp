#include "isPalindrome.h"

bool isPalindrome(const string& str) {
  bool palindrome = true;
  int length = str.length();
  StackInterface<char>* aStack = new LinkedStack<char>();
  QueueInterface<char>* aQueue = new LinkedQueue<char>();

  for(int i = 0; i < length; i++) {
    aQueue->enqueue(str.at(i));
    aStack->push(str.at(i));
  }
  while(!aQueue->isEmpty() ) {
    char queueFront = aQueue->peekFront();
    char stackTop = aStack->peek();

    if(queueFront == stackTop) {
     aQueue->dequeue();
     aStack->pop();
    }
    else {
     palindrome = false;
     break;
    }
  }
  delete aStack;
  delete aQueue;
  aStack = NULL;
  aQueue = NULL;

  return palindrome;
}

