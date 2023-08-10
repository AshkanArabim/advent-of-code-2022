#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int charToInt(char c) { return c - '0'; }

// check if a cell is visible
bool isVisible(int i, int j, vector<vector<int>>* gridptr) {
  int currentval = (*gridptr)[i][j];
  
  // check if cell is on edge
  if(
    i == 0 // on the top
    || i == gridptr->size() - 1 // on the bottom
    || j == 0 // on the left
    || j == (*gridptr)[i].size() - 1 // on the right
  ) {
    return true;
  }

  // check top
  for (int k = i - 1; k >= 0; k--) {
    if ((*gridptr)[k][j] >= currentval) {  // if not visible
      break;
    }

    if(k == 0) {
      return true; // if traversal reached edge
    }
  }

  // check bottom
  for (int k = i + 1; k < gridptr->size(); k++) {
    if ((*gridptr)[k][j] >= currentval) {  // if not visible
      break;
    }

    if(k == gridptr->size() - 1) {
      return true; // if traversal reached edge
    }
  }

  // check left
  for (int k = j - 1; k >= 0; k--) {
    if ((*gridptr)[i][k] >= currentval) {  // if not visible
      break;
    }

    if(k == 0) {
      return true; // if traversal reached edge
    }
  }

  // check right
  for (int k = j + 1; k < (*gridptr)[i].size(); k++) {
    if ((*gridptr)[i][k] >= currentval) {  // if not visible
      break;
    }

    if(k == (*gridptr)[i].size() - 1) {
      return true; // if traversal reached edge
    }
  }

  // yeah this could have been shorter...

  return false;
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
  int visible = 0;
  for (int i = 0; i < grid.size(); i++) {       // iterate over rows
    for (int j = 0; j < grid[i].size(); j++) {  // iterate over cells

      // cout << i << " " << j << endl;  // DEBUG
      // if (i == 21 && j == 17) { // DEBUG
      //   cout << "aha!" << endl;
      // }

      if (isVisible(i, j, &grid)) { // sus: 21, 17 is wrong
        visible++;  // if visible, add to visible count
      }
    }
  }

  cout << visible << endl;
}