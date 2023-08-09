#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
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

int getSmallestValid(vector<int>* vec, int neededspace) { // works!
  // maximum amount that fits in int
  int smallestValid = numeric_limits<int>::max(); 

  for (int i = 0; i < vec->size(); i++) {
    int value = (*vec)[i];
    if (value >= neededspace && value < smallestValid) {
      smallestValid = value;
    }
  }

  return smallestValid;
}

// function to traverse tree from root and add all folder sizes under 100,000
int getItemSize(Node* node, vector<int>* sizes) {
  if (node->size != -1) { // base case: if it's a file
    // cout << "node size: " << node->size << endl; // DEBUG --> works
    return node->size; 
  } else { // recursive case: if it's a directory
    // cout << node->name << endl; // DEBUG --> works
    int dirSize = 0;
    for (int i = 0; i < node->children.size(); i++) { // loop over children
      Node* currentChild = node->children[i];
      dirSize += getItemSize(currentChild, sizes); // add item size to sum
    }

    // check size for activity answer
    // cout << dirSize << endl; // DEBUG
    (*sizes).push_back(dirSize);

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

  // phase 2: accumulate all valid sizes in a vector, then find the smallest
  // quick and super nasty: just pass in a pointer
  vector<int> sizes;
  // get size of all files combined
  int usedspace = getItemSize(&root, &sizes); 
  int freespace = 70000000 - usedspace;
  int neededspace = 30000000 - freespace;

  int answer = getSmallestValid(&sizes, neededspace);
  cout << answer << endl;
  
  return 0;
}
