#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// NOTE: this would have been more efficient with std::deque

// draws the whole grid
void drawGrid(vector<vector<int>>* gridptr, array<int, 2>* headpos,
              array<int, 2>* tailpos) {
  cout << "grid size: " << gridptr->size() << ", " << gridptr->at(0).size()
       << endl;

  for (int i = 0; i < gridptr->size(); i++) {
    for (int j = 0; j < gridptr->at(0).size(); j++) {
      char c;
      if (i == headpos->at(0) && j == headpos->at(1)) {
        c = 'H';
      } else if (i == tailpos->at(0) && j == tailpos->at(1)) {
        c = 'T';
      } else {
        c = (char)gridptr->at(i)[j] + 48;
      }
      cout << c;
    }
    cout << endl;
  }
}

void extendGrid(vector<vector<int>>* gridptr, array<int, 2>* headpos,
                array<int, 2>* tailpos) {
  int colSize = gridptr->size();
  int rowSize = gridptr->at(0).size();

  // head exceeds top limit
  if (headpos->at(0) < 0) {
    // add row to beginning of grid
    gridptr->insert(gridptr->begin(), vector<int>(rowSize));
    // shift headpos down
    headpos->at(0)++;
    // shift tailpos down
    tailpos->at(0)++;
  }

  // head exceeds bottom limit
  if (headpos->at(0) >= colSize) {
    gridptr->push_back(vector<int>(rowSize));
  }

  // head exceeds left limit
  if (headpos->at(1) < 0) {
    // add item to beginning of every row (add column)
    for (int i = 0; i < colSize; i++) {
      gridptr->at(i).insert(gridptr->at(i).begin(), 0);
    }
    // shift headpos right
    headpos->at(1)++;
    // shift tailpos right
    tailpos->at(1)++;
  }

  // head exceeds right limit
  if (headpos->at(1) >= rowSize) {
    // add column
    for (int i = 0; i < colSize; i++) {  // iterate over rows
      gridptr->at(i).push_back(0);       // add one element
    }
  }
}

// we assume headpos & tailpos have size 2
void updateTail(array<int, 2>* headpos, array<int, 2>* tailpos) {
  int diffX = headpos->at(0) - tailpos->at(0);
  int diffY = headpos->at(1) - tailpos->at(1);

  // check for diff of 2 in rows.
  // if tail moves in row direction, add column movement to it
  int tailXmovement = diffX / 2;
  tailpos->at(0) += tailXmovement;
  if (tailXmovement != 0) {
    tailpos->at(1) += diffY;
  }

  // same as previous, but reversed
  int tailYmovement = diffY / 2;
  tailpos->at(1) += tailYmovement;
  if (tailYmovement != 0) {
    tailpos->at(0) += diffX;
  }
}

int main() {
  // initialize grid with 1 because tail starts here
  vector<vector<int>> grid = {{1}};
  // initialize coords
  array<int, 2> headpos = {0, 0};
  array<int, 2> tailpos = {0, 0};

  int linecounter = 0;  // DEBUG

  ifstream fs("./adventofcode.com_2022_day_9_input.txt");
  // ifstream fs("./test_input.txt");
  char direction;
  int distance;
  while (fs >> direction >> distance) {
    linecounter++;                           // DEBUG
    cout << "line " << linecounter << endl;  // DEBUG
    cout << direction << distance << endl;   // DEBUG

    for (int i = 0; i < distance; i++) {  // change one unit at a time
      // update head position
      if (direction == 'U') {
        headpos[0]--;  // one cell up
      } else if (direction == 'D') {
        headpos[0]++;  // one cell down
      } else if (direction == 'L') {
        headpos[1]--;  // one cell left
      } else if (direction == 'R') {
        headpos[1]++;  // one cell right
      } else {
        throw runtime_error("Invalid direction!");
      }

      // extend grid if necessary
      extendGrid(&grid, &headpos, &tailpos);

      // update tail position
      updateTail(&headpos, &tailpos);

      // set tail position value to 1
      grid[tailpos[0]][tailpos[1]] = 1;

      // drawGrid(&grid, &headpos, &tailpos);  // DEBUG
    }
  }

  // count 1s in grid
  int tailcount = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 1) {
        tailcount++;
      }
    }
  }

  // answer
  cout << tailcount << endl;
  return 0;
}