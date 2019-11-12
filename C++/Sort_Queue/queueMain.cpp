/*
 * File:   queueMain.cpp
 * Author: Michael Coughlin
 * Honors Computer Science I, Fall 2013
 * Created on December 3, 2010
 */

#include <stdlib.h>
#include <iostream>
#include <assert.h>
using namespace std;

/*
 * A queue node structure contains an integer item and a pointer
 * to the next node in the queue.
 */
struct node {
  int item;
  node* next;
};

typedef node* nodePtr;   // type definition for node pointer

typedef nodePtr* queue;  // a queue is a 2-element array of node pointers

/*
 * This makes and returns a dynamic 2-element array of node pointers
 * representing the start and tail of the queue.  The start and tail
 * are initialized to NULL to indicate an empty queue.
 */
queue makeQueue() {
  queue q = new nodePtr[2];
  q[0] = NULL;         // NULL is a constant for zero, or pointer to nothing
  q[1] = NULL;
  return q;
}

/*
 * An accessor for the node at the start of the queue.
 */
nodePtr start(queue q) {
  return q[0];
}

/*
 * An accessor for the node at the tail of the queue.
 */
nodePtr tail(queue q) {
  return q[1];
}

/*
 * A setter for the node at the start of the queue.
 */
void setStart(queue q, nodePtr newNode) {
  q[0] = newNode;
}

/*
 * A setter for the node at the tail of the queue.
 */
void setTail(queue q, nodePtr newNode) {
  q[1] = newNode;
}

/*
 * Tests for whether the queue is empty, which happens when the
 * start of the queue is null.
 */
bool emptyQueue(queue q) {
  return q[0] == NULL;
}

/*
 * Returns the item, that is the integer, at the head of the queue.
 * It is an error to take the head of an empty queue.
 * The queue is not modified.
 */
int head(queue q) {
  if ( emptyQueue(q) ) {
    cout << "Attempt to take head of an empty queue.\n";
    exit(1);
  }
  return start(q)->item;
}

/*
 * Adds a new item, an integer, to the queue at its tail.
 * A new node must be dynamically created to hold the item, with
 * appropriate locations updated accordingly.
 * enqueue is called for side effect and returns nothing.
 */
void enqueue(queue q, int newItem) {
    nodePtr newNode = new node;
    newNode->item=newItem;
    newNode->next=NULL;
    nodePtr begin = tail(q);
    if(emptyQueue(q)){
        setStart(q,newNode);
        setTail(q,newNode);
     } else {
        begin->next=newNode;
        setTail(q,newNode);
}
}

/*
 * Removes the node at the start of the queue, with appropriate locations
 * updated accordingly.
 * It is an error to dequeue from an empty queue.
 * dequeue is called for side effect and returns nothing.
 */
void dequeue(queue q) {
    nodePtr begin = start(q);
    if(begin!=NULL)
 {
     nodePtr temp=begin;
     begin=begin->next;
     delete temp;
     setStart(q,begin);
 }
 else cout << "Error: Attempt to Dequeue and empty queue.";
}

/*
 * The main function tests the queue.  Testing succeeds if
 * main executes with no assertion errors and the only output
 * is "Exercise 12.2 Passed".
 */
int main(int argc, char** argv) {

  // Testing Exercise 13.2
  queue q = makeQueue();                // make a new queue

  assert( emptyQueue(q) );              // queue should be empty

  for (int item = 1; item <= 6; item++) // enqueue 6 items
    enqueue(q, item);
  assert( !emptyQueue(q) );             // queue should not be empty
  assert( head(q) == 1 );               // 1 should be at head

  for (int i = 1; i <= 4; i++)          // dequeue 4 items
    dequeue(q);
  assert( head(q) == 5 );               // 5 should be at head

  for (int item = 11; item <= 16; item++) // enqueue 6 more items
    enqueue(q, item);
  assert( head(q) == 5 );               // 5 should still be head

  for (int i = 1; i <= 5; i++)          // dequeue 5 items
    dequeue(q);
  assert( head(q) == 14 );              // 14 should be at head

  for (int i = 1; i <= 3; i++)          // dequeue 3 items
    dequeue(q);
  assert( emptyQueue(q) );              // queue should be empty

  cout << "Exercise 13.2 Passed" << endl;
}

