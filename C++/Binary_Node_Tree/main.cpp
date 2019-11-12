#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "BinaryNodeTree.h"

void visit(int& item) {
  cout << item << " ";
}


void visitStr(string& item) {
  cout << item << " ";
}


int main() {
  cout << endl
       << "///////////////////////////////////////////"
       << endl
       << "//Testing Integer ADT Binary Tree Methods//\n"
       << "///////////////////////////////////////////"
       << endl
       << endl;
 
  BinaryNodeTree<int> tree; // Binary Search Tree
  BinaryNodeTree<int> tree1; // Binary Search Tree
  BinaryNodeTree<int> tree2; // Not A Binary Search Tree
  BinaryNodeTree<int> tree3; // Binary Search Tree
  BinaryNodeTree<int> tree4; // Binary Search Tree
  BinaryNodeTree<int> tree5; // Not A Binary Search Tree
  BinaryNodeTree<int> tree6; // Binary Search Tree
  BinaryNodeTree<int> tree7; // Empty Binary Search Tree
  BinaryNodeTree<int> tree8; // Binary Search Tree
  BinaryNodeTree<string> strTree; // Binary Search Tree
  BinaryNodeTree<string> strTree1; // Binary Search Tree
  BinaryNodeTree<string> strTree2; // Binary Search Tree
 
  tree.add(3);
  tree.add(2); 
  tree.add(4);

  tree1.add(3);
  tree1.add(2);
  tree1.add(4);

  tree2.add(2);
  tree2.add(7);
  tree2.add(1);
 
  tree3.add(3);
  tree3.add(2); 
  tree3.add(4);
  tree3.add(1);
 
  tree4.add(4);
  tree4.add(3); 
 
  tree5.add(5);
  tree5.add(11); 
  tree5.add(4);
  tree5.add(12);

  tree6.add(1);
 
  tree8.add(3);
  tree8.add(2); 
  tree8.add(4);
  tree8.add(1);
  
  strTree.add("Michael");
  strTree.add("Joe");
  strTree.add("Jeff");
  strTree.add("Alex");
  strTree.add("Kayle");
  
  strTree1.add("Michael");
  strTree1.add("Joe");
  strTree1.add("Jeff");
  strTree1.add("Alex");
  strTree1.add("Kayle");

  strTree2.add("Panda");
  strTree2.add("Shark");
  strTree2.add("Dog");
  strTree2.add("Cat");

  cout << "Preorder Traverse: ";  
  tree.preorderTraverse(visit);
  cout << endl
       << "Postorder Traverse: ";  
  tree.postorderTraverse(visit);
  cout << endl
       << "Inorder Traverse: ";  
  tree.inorderTraverse(visit);
  cout << endl
       << endl
       << "Preorder after flip method: ";
  tree.flip();
  tree.preorderTraverse(visit);
  cout << endl
       << "Postorder after flip method: ";
  tree.postorderTraverse(visit); 
  cout << endl 
       << "Inorder after flip method: ";
  tree.inorderTraverse(visit);

  cout << endl
       << endl
       << "Preorder Traverse: ";  
  tree8.preorderTraverse(visit);
  cout << endl
       << "Postorder Traverse: ";  
  tree8.postorderTraverse(visit);
  cout << endl
       << "Inorder Traverse: ";  
  tree3.inorderTraverse(visit);
  cout << endl
       << endl
       << "Preorder after flip method: ";
  tree8.flip();
  tree8.preorderTraverse(visit);
  cout << endl
       << "Postorder after flip method: ";
  tree8.postorderTraverse(visit); 
  cout << endl 
       << "Inorder after flip method: ";
  tree8.inorderTraverse(visit);
 
  cout << endl
       << endl
       << "//////////////////////////////////////////"
       << endl
       << "//Are the following binary search trees?//\n"
       << "//////////////////////////////////////////"
       << endl
       << endl 
       << "Tree1 Preorder Traverse: ";  
 
  tree1.preorderTraverse(visit);
  cout << endl;
 
 if(tree1.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree2 Preorder Traverse: "; 

  tree2.preorderTraverse(visit);
  cout << endl;
 
 if(tree2.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree3 Preorder Traverse: ";
 
  tree3.preorderTraverse(visit);
  cout << endl;

 if(tree3.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree4 Preorder Traverse: "; 

  tree4.preorderTraverse(visit);
  cout << endl;
 
 if(tree4.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree5 Preorder Traverse: ";
 
  tree5.preorderTraverse(visit);
  cout << endl;

 if(tree5.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree6 Preorder Traverse: ";

  tree6.preorderTraverse(visit);
  cout << endl;

  if(tree6.isBinTree() == false)
    cout << "False - tree is not at BST.\n\n";
  else 
    cout << "True - tree is a BST.\n\n";
    cout << "Tree7 An empty tree: ";

  tree7.preorderTraverse(visit);
  cout << endl;

  if(tree7.isBinTree() == false)
    cout << "False - tree is not at BST.\n";
  else 
    cout << "True - tree is a BST.\n";
          
 
  cout << endl
       << "////////////////////////////////////////////"
       << endl
       << "//What are the minimum and maximum values?//\n"
       << "////////////////////////////////////////////"
       << endl
       << endl
       << "Tree1 - Preorder Traverse: ";

  tree1.preorderTraverse(visit);

  cout << endl;
  cout << "Maximum value of tree: ";
  cout << tree1.maxValue();
  cout << endl;
  cout << "Minimum value of tree: ";
  cout << tree1.minValue();
  cout << endl
       << endl
       << "Tree4 - Preorder Traverse: ";

  tree4.preorderTraverse(visit);

  cout << endl;
  cout << "Maximum value of tree: ";
  cout << tree4.maxValue();
  cout << endl;
  cout << "Minimum value of tree: ";
  cout << tree4.minValue();
  cout << endl
       << endl
       << "Tree3 - Preorder Traverse: ";

  tree3.preorderTraverse(visit);

  cout << endl;
  cout << "Maximum value of tree: ";
  cout << tree3.maxValue();
  cout << endl;
  cout << "Minimum value of tree: ";
  cout << tree3.minValue();
  cout << endl;
 
 
  cout << endl
       << "////////////////////////////////"
       << endl 
       << "//Printing root to path method//\n"
       << "////////////////////////////////"
       << endl
       << endl
       << "Tree1 - Preorder Traverse: ";

  tree1.preorderTraverse(visit);

  cout << endl;
  cout << "Tree path(s):\n";

  tree1.printPaths();
  cout << endl
       << "Tree3 - Preorder Traverse: ";

  tree3.preorderTraverse(visit);

  cout << endl;
  cout << "Tree path(s):\n";

  tree3.printPaths();

  cout << endl
       << "////////////////////////"
       << endl
       << "//Testing sum of paths//\n"
       << "////////////////////////"
       << endl
       << endl
       << "Tree1 - Preorder Traverse: ";

  tree1.preorderTraverse(visit);

  cout << endl
       << "Do any of the following paths sum to 100?\n";

  tree1.pathSum(100);

  cout << endl
       << "Do any of the following paths sum to 7?\n";

  tree1.pathSum(7);
 
 cout  << endl
       << "Tree3 - Preorder Traverse: ";

  tree3.preorderTraverse(visit);

  cout << endl
       << "Do any of the following paths sum to 7?\n";

    tree3.pathSum(7);
  
  cout << endl
       << "Do any of the following paths sum to 6?\n";

  tree3.pathSum(6);
 
    cout << endl
       << "//////////////////////////////////////////"
       << endl
       << "//Testing String ADT Binary Tree Methods//\n"
       << "//////////////////////////////////////////"
       << endl
       << endl;

  cout << "Preorder Traverse: ";  
  strTree.preorderTraverse(visitStr);
  cout << endl
       << "Postorder Traverse: ";  
  strTree.postorderTraverse(visitStr);
  cout << endl
       << "Inorder Traverse: ";  
  strTree.inorderTraverse(visitStr);
  cout << endl
       << endl
       << "Preorder after flip method: ";
  strTree.flip();
  strTree.preorderTraverse(visitStr);
  cout << endl
       << "Postorder after flip method: ";
  strTree.postorderTraverse(visitStr); 
  cout << endl 
       << "Inorder after flip method: ";
  strTree.inorderTraverse(visitStr);

  cout << endl
       << endl
       <<"Preorder Traverse: ";  
  strTree2.preorderTraverse(visitStr);
  cout << endl
       << "Postorder Traverse: ";  
  strTree2.postorderTraverse(visitStr);
  cout << endl
       << "Inorder Traverse: ";  
  strTree2.inorderTraverse(visitStr);
  cout << endl
       << endl
       << "Preorder after flip method: ";
  strTree2.flip();
  strTree2.preorderTraverse(visitStr);
  cout << endl
       << "Postorder after flip method: ";
  strTree2.postorderTraverse(visitStr); 
  cout << endl 
       << "Inorder after flip method: ";
  strTree2.inorderTraverse(visitStr);
  
  cout << endl
       << endl
       << "////////////////////////////////"
       << endl 
       << "//Printing root to path method//\n"
       << "////////////////////////////////"
       << endl
       << endl
       << "strTree - Preorder Traverse: ";

  strTree1.preorderTraverse(visitStr);
  cout << endl;
 
  strTree1.printPaths();

  cout << endl
       << "strTree2 - Preorder Traverse: ";
  strTree2.preorderTraverse(visitStr);
  cout << endl;
 
  strTree2.printPaths();
   
  cout << endl
       << "////////////////////////////////////////////"
       << endl
       << "//What are the minimum and maximum values?//\n"
       << "////////////////////////////////////////////"
       << endl
       << endl
       << "strTree1 - Preorder Traverse: ";

  strTree1.preorderTraverse(visitStr);
  
  cout << endl;
  cout << "Maximum value of tree: ";
  cout << strTree1.maxValue();
  cout << endl;
  cout << "Minimum value of tree: ";
  cout << strTree1.minValue();
  cout << endl
       << endl
       << "strTree2 - Preorder Traverse: ";

  strTree2.preorderTraverse(visitStr);

  cout << endl;
  cout << "Maximum value of tree: ";
  cout << strTree2.maxValue();
  cout << endl;
  cout << "Minimum value of tree: ";
  cout << strTree2.minValue();
  cout << endl
       << endl
       << "TESTS SUCCESSFUL\n"
       << endl;

 return EXIT_SUCCESS;
}
