#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

bool hasDuplicates(queue<char> charqueue) {
  int uniqueCount = 0;
  int size = 4;
  char uniques[size];

  while(!charqueue.empty()) {
    // get first element
    char c = charqueue.front();
    charqueue.pop();

    // check against all uniques
    for (int j = 0; j < uniqueCount; j++) {
      if (c == uniques[j]) {
        return true;
      }
    }

    // add to existing uniques
    uniques[uniqueCount] = c;
    uniqueCount++;
  }

  return false;
}

int main() {
  // create a queuen of size 4
  // int i = 0;
  // for each character received
  // i++;
  // if the queue is not filled, continue;
  // if there are similarities (func), continue;
  // break; // here, it's both full and there is no repetition

  // print output

  int charcount = 0;
  char c;
  queue<char> charqueue;
  ifstream fs("./adventofcode.com_2022_day_6_input.txt");
  while (fs >> c) {
    charcount++;

    // append the char to the queue
    charqueue.push(c);

    // check if queue has size less than 5 with new element. if not, it needs
    // more chars.
    if (charqueue.size() < 14) {
      continue;
    }

    // check if there are similarities. if so, go to next iteration
    if (hasDuplicates(charqueue)) {
      // remove the oldest element before sending back into loop: queue never exceeds 4 elements
      charqueue.pop();
      continue;
    }

    // if all checks passed, stop loop
    break;
  }

  // print total characters received
  cout << charcount << endl;

  return 0;
}