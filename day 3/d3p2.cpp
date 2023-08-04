#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// notes:
// guaranteed that one item is shared in each backpack

vector<string> split(string s) {  // checked
  int len = s.length();
  string left = s.substr(0, len / 2);
  string right = s.substr(len / 2, len);
  vector<string> output = {left, right};

  return output;
}

// check for common items
// option 1: for loops --> not very efficient lmao
char getCommon(string one, string two, string three) {
  for (int i = 0; i < one.length(); i++) {
    for (int j = 0; j < two.length(); j++) {
      for (int k = 0; k < three.length(); k++) {
        if (one[i] == two[j] && one[i] == three[k]) {
          return one[i];
        }
      }
    }
  }
  return '?';
}

// get priority of common item
int getPriority(char c) {
  int charnum = (int)c;
  // lowercase: from a(97) to z(122)
  if (charnum > 96 && charnum < 123) {
    return charnum - 96;
  }

  // uppercase: from A(65) to Z(90)
  if (charnum > 64 && charnum < 91) {
    return charnum - 64 + 26;  // they come after lowercase
  }

  // in case of bad character
  string errorString = string("bad character passed: ") + string(1, c);
  throw runtime_error(errorString);
}

int main() {
  int sum = 0;
  ifstream file("./adventofcode.com_2022_day_3_input.txt");

  string one, two, three;
  while (file >> one >> two >> three) {
    char common = getCommon(one, two, three);

    // get priority of common item --> func
    int priority = getPriority(common);

    // DEBUG
    // cout << line << endl;
    // cout << common << endl;
    // cout << priority << endl;

    sum += priority;
  }

  // print sum
  cout << sum << endl;

  return 0;
}