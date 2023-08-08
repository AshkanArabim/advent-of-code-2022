#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// C++ IS ALWAYS PASS BY VALUE UNLESS SPECIFIED!!!!

bool isStackPosition(int i) { return (i - 1) % 4 == 0; }

bool isUppercaseChar(char c) {
  int ascii = (int)c;
  return ascii > 64 && ascii < 91;
}

bool isNumber(char c) {
  int ascii = (int)c;
  return ascii > 47 && ascii < 58;
}

int colToStackIndex(int i) { return (i - 1) / 4; }

stack<char> reverseStack(stack<char> original) {
  stack<char> reversed;

  while (!original.empty()) {
    reversed.push(original.top());  // copy first element
    original.pop();                 // remove first element
  }

  return reversed;
}

template <typename T>
stack<T> copyStack(stack<T> s) {
  // reverse stuff into tempstack
  stack<T> tempstack;
  while (!s.empty()) {
    tempstack.push(s.top());
    s.pop();
  }

  // reverse tempstack into newstack and original
  stack<T> newstack;
  while (!tempstack.empty()) {
    newstack.push(tempstack.top());
    s.push(tempstack.top());
    tempstack.pop();
  }

  return newstack;
}

// prints the contents of a stack without modifying it
template <typename T>
void printStack(stack<T> s) {         // passed by reference
  stack<T> tempstack = copyStack(s);  // very sus

  cout << "stack items:" << endl;
  while (!tempstack.empty()) {
    cout << tempstack.top() << endl;
    tempstack.pop();
  }
}

template <typename T>
void move(stack<T> &origin, stack<T> &destination) {
  destination.push(origin.top());
  origin.pop();
}

template <typename T>
void multipleMove(stack<T> &origin, stack<T> &destination, int count) {
  stack<T> tempstack;

  // move items normally from origin to tempstack (flipped)
  for (int i = 0; i < count; i++) {
    move(origin, tempstack);
  }

  // move items normally from tempstack to destination (flipped of flipped = normal)
  for (int i = 0; i < count; i++) {
    move(tempstack, destination);
  }
}

int main() {
  // phase 1: extract initial state

  ifstream file("./adventofcode.com_2022_day_5_input.txt");

  // create vector of stacks
  // remember that anything stored here is upside down
  vector<stack<char>> stackVector;

  // parse character by character
  char c;
  int i = 0;
  while (file >> noskipws >> c) {
    // if uppercase letter and in right position
    if (isNumber(c)) {
      break;
    }  // break once numbers are reached
    // cout << c; // DEBUG
    if (isStackPosition(i)) {
      int stackIndex = colToStackIndex(i);

      // cout << stackVector.size() << endl; // DEBUG

      // add stack to stack vector in necessary
      if (stackIndex == stackVector.size()) {
        // cout << "adding stack to vector" << endl; // DEBUG
        // if this index is out of bounds, add a char stack
        stack<char> newStack;
        stackVector.push_back(newStack);
      }

      // if it's a character, add it to appropriate stack
      if (isUppercaseChar(c)) {
        // cout << "found stack item " << c << " at position " << i << endl; //
        // DEBUG cout << "column number: " << colToStackIndex(i) << endl; //
        // DEBUG
        stackVector[stackIndex].push(c);
      }
    }

    // cout << "col index: " << i << endl;// DEBUG
    i++;
    if (c == '\n') {
      i = 0;
    }  // reset column counter for each line
  }

  // reverse stacks
  // cout << "stack vector size: " << stackVector.size() << endl; // DEBUG
  for (int i = 0; i < stackVector.size(); i++) {
    stackVector[i] = reverseStack(stackVector[i]);
    // printStack(stackVector[i]);  // DEBUG
  }

  // phase 2: move the stuff around

  // skip to the commands
  string trash;
  getline(file, trash);
  getline(file, trash);

  int count, from, to;
  file >> skipws;  // now it skips whitespace
  while (file >> trash >> count >> trash >> from >> trash >> to) {
    // cout << "------" << endl; // DEBUG
    // cout << "count: " << count << endl; // DEBUG
    // cout << "from: " << from << endl; // DEBUG
    // cout << "to: " << to << endl; // DEBUG

    // the input file is 1-indexed, so we subtract 1 from "form" & "to"
    from--;
    to--;

    multipleMove(stackVector[from], stackVector[to], count);
  }

  // program output
  for (int i = 0; i < stackVector.size(); i++) {
    cout << stackVector[i].top();
  }

  return 0;
}