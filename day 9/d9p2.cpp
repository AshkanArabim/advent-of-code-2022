#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// NOTE: this would have been more efficient with std::deque

// draws the whole grid
void drawGrid(vector<vector<int>>* gridptr,
              array<array<int, 2>, 10>* knotsptr) {
  // clear the screen --> VERY COOL GRAPHICS!!
  // system("cls");
  cout << "grid size: " << gridptr->size() << ", " << gridptr->at(0).size()
       << endl;

  for (int i = 0; i < gridptr->size(); i++) {
    for (int j = 0; j < gridptr->at(0).size(); j++) {
      char c;

      // if covered: #, if not, .
      if (gridptr->at(i)[j] == 1) {
        c = '#';
      } else {
        c = '.';
      }

      // loop over knots, see if position matches the position of any of them
      // if it does, print i (from 0 to 9)
      for (int k = 0; k < knotsptr->size(); k++) {
        array<int, 2>& knotpos = knotsptr->at(k); // reference
        if (knotpos[0] == i && knotpos[1] == j) {
          c = (char) k + 48; // print k in char form
          break;
        }
      }

      cout << c;
    }
    cout << endl;
  }
}

void extendGrid(vector<vector<int>>* gridptr,
                array<array<int, 2>, 10>* knotsptr) {
  int colSize = gridptr->size();
  int rowSize = gridptr->at(0).size();

  // knotsptr->at(0) is the position of the head

  // head exceeds top limit
  if (knotsptr->at(0)[0] < 0) {
    // add row to beginning of grid
    gridptr->insert(gridptr->begin(), vector<int>(rowSize));
    // shift rope down
    for (int i = 0; i < knotsptr->size(); i++) {
      knotsptr->at(i)[0]++;
    }
  }

  // head exceeds bottom limit
  if (knotsptr->at(0)[0] >= colSize) {
    gridptr->push_back(vector<int>(rowSize));
  }

  // head exceeds left limit
  if (knotsptr->at(0)[1] < 0) {
    // add item to beginning of every row (add column)
    for (int i = 0; i < colSize; i++) {
      gridptr->at(i).insert(gridptr->at(i).begin(), 0);
    }
    // shift rope right
    for (int i = 0; i < knotsptr->size(); i++) {
      knotsptr->at(i)[1]++;
    }
  }

  // head exceeds right limit
  if (knotsptr->at(0)[1] >= rowSize) {
    // add column
    for (int i = 0; i < colSize; i++) {  // iterate over rows
      gridptr->at(i).push_back(0);       // add one element
    }
  }
}

// we assume headpos & tailpos have size 2
void updateRope(array<array<int, 2>, 10>* grid) {
  // NOTE: it starts at 1 because head doesn't change
  // loop over each pair starting from head,
  // update the tail immediately following knot
  for (int i = 1; i < grid->size(); i++) {
    // create references for head and tail position
    array<int, 2>& headpos = grid->at(i - 1);
    array<int, 2>& tailpos = grid->at(i);

    int diffX = headpos[0] - tailpos[0];
    int diffY = headpos[1] - tailpos[1];

    if (diffX / 2 != 0 && diffY / 2 != 0) { // if movement of 2, 2
      // move half of that in any axis
      tailpos[0] += diffX / 2;
      tailpos[1] += diffY / 2; 
    } else { // smaller movements are handled here
      // check for diff of 2 in rows.
      // if tail moves in row direction, add column movement to it
      int tailXmovement = diffX / 2;
      tailpos[0] += tailXmovement;
      if (tailXmovement != 0) {
        tailpos[1] += diffY;
      }

      // same as previous, but reversed
      int tailYmovement = diffY / 2;
      tailpos[1] += tailYmovement;
      if (tailYmovement != 0) {
        tailpos[0] += diffX;
      }
    }
  }
}

// bainstrom
// use an array to keep track of each node.
// loop over the array to run updateTrail for every pair

int main() {
  // initialize grid with 1 because tail starts here
  vector<vector<int>> grid = {{1}};

  // set position of all knots to (0, 0)
  array<array<int, 2>, 10> knots;
  for (int i = 0; i < knots.size(); i++) {
    knots[i] = array<int, 2>{0, 0};
  }

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
        knots[0][0]--;  // one cell up
      } else if (direction == 'D') {
        knots[0][0]++;  // one cell down
      } else if (direction == 'L') {
        knots[0][1]--;  // one cell left
      } else if (direction == 'R') {
        knots[0][1]++;  // one cell right
      } else {
        throw runtime_error("Invalid direction!");
      }

      // extend grid if necessary
      extendGrid(&grid, &knots);

      // update tail position
      updateRope(&knots);

      // set last knotposition value to 1
      int lastindex = knots.size() - 1;
      grid[knots[lastindex][0]][knots[lastindex][1]] = 1;

      // drawGrid(&grid, &knots);  // DEBUG
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