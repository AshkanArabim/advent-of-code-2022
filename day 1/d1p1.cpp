#include <fstream>
#include <iostream>
using namespace std;

// c++ file I/O: https://cplusplus.com/doc/tutorial/files/

int main() {
  // parse the file, store it in 2d array

  ifstream inputFile("adventofcode.com_2022_day_1_input.txt");

  int max = 0;
  int sum = 0;
  string line;
  while (getline(inputFile, line)) {
    // check if this line is empty
    if (line.empty()){
        // cout << sum << endl;
        if (sum > max){
            max = sum;
        }
        sum = 0;
    } else {
        sum += stoi(line);
    }
  }

  cout << max << endl;

  inputFile.close();    

  return 0;
}