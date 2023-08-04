#include <fstream>
#include <iostream>

using namespace std;

// how many points you get for each move
int getMovePoints(char yourmove) {
  if (yourmove == 'X') return 1;  // rock
  if (yourmove == 'Y') return 2;  // paper
  if (yourmove == 'Z') return 3;  // scissors

  // in case if stupidity
  throw 20;
}

// how many points you get for the game's status
int getGamePoints(char elfmove, char yourmove) {
  // win scenarios
  if ((elfmove == 'B' && yourmove == 'Z') ||  // elf: paper, you: scissors
      (elfmove == 'C' && yourmove == 'X') ||  // elf: scissors, you: rock
      (elfmove == 'A' && yourmove == 'Y')     // elf: rock, you: paper
  ) {
    return 6;
  } else if ((int)elfmove + 23 == (int)yourmove) {  // tie scenario
    return 3;
  } else {  // lose scenario
    return 0;
  }
}

int main() {
  int score = 0;

  ifstream inputFile("./adventofcode.com_2022_day_2_input.txt");
  // ifstream inputFile("./test.txt");

  char elfmove;
  char yourmove;

  while (inputFile >> elfmove >> yourmove) {
    cout << elfmove << ' ' << yourmove << endl;  // DEBUG

    // get points
    score += getMovePoints(yourmove);
    score += getGamePoints(elfmove, yourmove);
  }

  cout << score << endl;

  return 0;
}