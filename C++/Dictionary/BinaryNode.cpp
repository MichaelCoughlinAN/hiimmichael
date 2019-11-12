#include <algorithm>
#include <iostream>

using namespace std;

template<typename ItemType>
BinaryNode<ItemType>::BinaryNode()
  : leftChildPtr(nullptr),
    rightChildPtr(nullptr) {
    }

template<typename ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
				 BinaryNode<ItemType>* leftPtr,
				 BinaryNode<ItemType>* rightPtr ) {
  item = anItem;
  leftChildPtr = leftPtr;
  rightChildPtr = rightPtr;
}
