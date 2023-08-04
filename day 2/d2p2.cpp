#include <fstream>
#include <iostream>

using namespace std;

// how many points you get for each move
int getMovePoints(char yourmove) {
  // cout << "your move: " << yourmove << endl;

  if (yourmove == 'X') return 1;  // rock
  if (yourmove == 'Y') return 2;  // paper
  if (yourmove == 'Z') return 3;  // scissors

  // DEBUG --> read this line please
  // cout << yourmove << endl;

  // in case if stupidity
  throw runtime_error("your move is invalid in get move points: ");
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

// what move to make based on elf move and target game status
char suggestMove(char elfmove, char gamestatus) {
  if (gamestatus == 'Y') { // draw
    return (char)(elfmove + 23);
  } else if (gamestatus == 'Z') { // win
    if (elfmove == 'B') return 'Z';// elf: paper, you: scissors
    if (elfmove == 'C') return 'X';// elf: scissors, you: rock
    if (elfmove == 'A') return 'Y';// elf: rock, you: paper
    throw runtime_error("elfmove is invalid in suggestmove"); // in case of stupidity
  } else if (gamestatus == 'X') { // lose
    if (elfmove == 'B') return 'X';// elf: paper, you: rock
    if (elfmove == 'C') return 'Y';// elf: scissors, you: paper
    if (elfmove == 'A') return 'Z';// elf: rock, you: scissors
    throw runtime_error("elfmove is invalid in suggestmove"); // in case of stupidity
  }

  throw runtime_error("gamestatus is invalid in suggestmove"); // in case of stupidity
}

int main() {
  int score = 0;

  ifstream inputFile("./adventofcode.com_2022_day_2_input.txt");
  // ifstream inputFile("./test.txt");

  char elfmove;
  char gamestatus;
  char yourmove;

  while (inputFile >> elfmove >> gamestatus) {
    cout << "-----------------" << endl;
    cout << elfmove << ' ' << gamestatus << endl; // DEBUG

    // get points
    yourmove = suggestMove(elfmove, gamestatus);
    score += getMovePoints(yourmove);
    score += getGamePoints(elfmove, yourmove);

    cout << elfmove << ' ' << yourmove << ' ' << gamestatus << endl;  // DEBUG
  }

  cout << score << endl;

  return 0;
}