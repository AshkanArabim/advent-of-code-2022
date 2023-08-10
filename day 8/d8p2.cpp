#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int charToInt(char c) { return c - '0'; }

// check if a cell is visible
int scenicScore(int i, int j, vector<vector<int>>* gridptr) {
  int currentval = (*gridptr)[i][j];
  
  // check if cell is on edge
  if(
    i == 0 // on the top
    || i == gridptr->size() - 1 // on the bottom
    || j == 0 // on the left
    || j == (*gridptr)[i].size() - 1 // on the right
  ) {
    return 0; // 0 trees * anything is 0
  }

  // check top
  int topscore = 0;
  for (int k = i - 1; k >= 0; k--) {
    topscore++;
    if ((*gridptr)[k][j] >= currentval) {  // if taller tree
      break;
    }
  }

  // check bottom
  int bottomscore = 0;
  for (int k = i + 1; k < gridptr->size(); k++) {
    bottomscore++;
    if ((*gridptr)[k][j] >= currentval) {  // if taller tree
      break;
    }
  }

  // check left
  int leftscore = 0;
  for (int k = j - 1; k >= 0; k--) {
    leftscore++;
    if ((*gridptr)[i][k] >= currentval) {  // if taller tree
      break;
    }
  }

  // check right
  int rightscore = 0;
  for (int k = j + 1; k < (*gridptr)[i].size(); k++) {
    rightscore++;
    if ((*gridptr)[i][k] >= currentval) {  // if taller tree
      break;
    }
  }

  // yeah this could have been shorter...

  return topscore * bottomscore * leftscore * rightscore;
}

int main() {
  // phase 1: parse: works!

  // create grid with one empty row
  vector<vector<int>> grid;

  ifstream fs("adventofcode.com_2022_day_8_input.txt");
  string line;
  int lineidx = 0;
  while (getline(fs, line)) {
    // add a row for each line;
    vector<int> row;

    stringstream ss(line);
    char cell;
    int colidx = 0;
    while (ss >> noskipws >> cell) {
      row.push_back(charToInt(cell));
      colidx++;
    }
    grid.push_back(row);  // push row into the grid

    lineidx++;
  }

  // phase 2: traverse and count visible trees
  int maxScore = 0;
  for (int i = 0; i < grid.size(); i++) {       // iterate over rows
    for (int j = 0; j < grid[i].size(); j++) {  // iterate over cells

      int currentScore = scenicScore(i, j, &grid);
      if (currentScore > maxScore) {
        maxScore = currentScore;
      }
    }
  }

  cout << maxScore << endl;
}