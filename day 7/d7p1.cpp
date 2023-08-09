#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// one Node in file-tree
class Node {
 public:
  int size;
  string name;
  // children are accessed using their index
  Node* parent;
  vector<Node*> children;

  Node(int s, string n, Node* p) {
    // set size to -1 for dirs
    // cout << "------ created new Node" << endl; // DEBUG --> works!
    size = s;
    // cout << "size: " << size << endl; // DEBUG
    name = n;
    // cout << "name: " << name << endl; // DEBUG
    parent = p;
    // cout << "parent: " << parent << endl; // DEBUG
  }

  int getChildIndex(string childName) {
    // loop through children's names
    for (int i = 0; i < children.size(); i++) {
      if (childName == children[i]->name) {
        return i;
      }
    }

    return -1;
  }

  // function to add children
  void addChild(Node* nodePointer) { children.push_back(nodePointer); }
};

// function to traverse tree from root and add all folder sizes under 100,000
int getItemSize(Node* node, int* answer) {
  if (node->size != -1) { // base case: if it's a file
    // cout << "node size: " << node->size << endl; // DEBUG --> works
    return node->size; 
  } else { // recursive case
    // cout << node->name << endl; // DEBUG --> works
    int dirSize = 0;
    for (int i = 0; i < node->children.size(); i++) { // loop over children
      Node* currentChild = node->children[i];
      dirSize += getItemSize(currentChild, answer); // add item size to sum
    }

    // check size for activity answer
    if (dirSize <= 100000) {
      // cout << dirSize << endl; // DEBUG
      *answer += dirSize; 
    }

    return dirSize;
  }  
}

int main() {
  // phase 1: parser
  ifstream fs("adventofcode.com_2022_day_7_input.txt");
  string line;
  Node root(-1, "root", nullptr);
  Node* currentNode = &root; // point to root
  while (getline(fs, line)) {
    stringstream ss(line);
    string w1, w2, w3;
    ss >> w1 >> w2 >> w3;

    // if you see "$ cd", change the directory
    if (w1 == "$" && w2 == "cd") { 
      if (w3 == "..") {
        currentNode = currentNode->parent;
      } else if(w3 == "/") {
        currentNode = &root;
      }else {
        int childIndex = currentNode->getChildIndex(w3);
        currentNode = currentNode->children[childIndex];
      }
    } else if (w1 != "$") {
      // if not a command, it's a file / folder
      if (w1 == "dir") { // if it's a folder
        Node* newFolderPtr = new Node(-1, w2, currentNode);
        currentNode->addChild(newFolderPtr);
      } else { // if it's a file
        // cout << "w1: " << w1 << endl; // DEBUG
        Node* newNodePtr = new Node(stoi(w1), w2, currentNode);
        currentNode->addChild(newNodePtr);
      }
    }

    // we'll ignore "$ ls"
  }

  // phase 2: traverse and add valid sizes
  // quick and super nasty: just pass in a pointer
  int* answer = new int(0);
  getItemSize(&root, answer);
  // cout << getItemSize(&root, answer) << endl; // DEBUG --> works
  cout << *answer << endl;
  delete answer; // preventing memory leaks. just to practice. 
}
