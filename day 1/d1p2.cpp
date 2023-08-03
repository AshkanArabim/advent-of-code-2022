#include <fstream>
#include <iostream>
#include <limits>
using namespace std;

// c++ file I/O: https://cplusplus.com/doc/tutorial/files/

// return sum of int array
int getArraySum(const int arr[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

// check if sum is greater than any array element. if so, return index,
// if not, return -1
int getSmallestIndex(const int arr[], int size, int num) {
  int min = numeric_limits<int>::max();
  int minIndex = 0;

  // find min number and index
  for (int i = 0; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
      minIndex = i;
    }
  }

  // compare num with num number. if larger, return min index
  if (num > min) {
    return minIndex;
  }

  return -1;
}

int main() {
  // parse the file, store it in 2d array

  ifstream inputFile("adventofcode.com_2022_day_1_input.txt");

  // make an array of three, if a total is greater than all three, replace the
  // smallest one with the new one
  int top_3_total[3] = {0, 0, 0};

  int sum = 0;
  string line;
  while (getline(inputFile, line)) {
    // check if this line is empty
    if (line.empty()) {
      // get index of smallest
      int smallestIndex = getSmallestIndex(top_3_total, 3, sum);

      // -1 means it's smaller than all, so we don't care
      if (smallestIndex != -1) {
        // replace smallest position with new sum
        top_3_total[smallestIndex] = sum;
      }

      sum = 0;  // reset sum for next round
    } else {
      sum += stoi(line);
    }
  }

  cout << getArraySum(top_3_total, 3) << endl;

  inputFile.close();

  return 0;
}