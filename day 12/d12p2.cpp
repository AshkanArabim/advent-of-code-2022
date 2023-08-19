#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

class Cell {
 private:
  std::array<int, 2> coords;
  int height = 0;

 public:
  // I divide just to make it fit for debugging
  int distance = std::numeric_limits<int>::max() / 10000; 
  bool visited = false;

  std::array<int, 2> getTop() {
    return std::array<int, 2>{coords[0] - 1, coords[1]};
  }
  std::array<int, 2> getBottom() {
    return std::array<int, 2>{coords[0] + 1, coords[1]};
  }
  std::array<int, 2> getLeft() {
    return std::array<int, 2>{coords[0], coords[1] - 1};
  }
  std::array<int, 2> getRight() {
    return std::array<int, 2>{coords[0], coords[1] + 1};
  }

  std::array<int, 2> getCoords() { return coords; }

  int getHeight() { return height; }

  Cell(int i, int j, int height) : coords{i, j}, height(height){};
};

int getHeightNum(char c) {
  // a is 0, and so on.
  int charHeight = (int)c - 97;

  // exceptions for S and E
  if (c == 'S') {
    charHeight = 0;
  } else if (c == 'E') {
    charHeight = 25;
  }

  // catch any errors
  if (charHeight < 0 || charHeight > 25) {
    throw std::runtime_error("Invalid character!");
  }

  return charHeight;
}

// debug: see if grid is correct
void printGrid(std::vector<std::vector<Cell>>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      std::cout << grid[i][j].getHeight();
    }
    std::cout << std::endl;
  }
}

// debug: draws the distance of all cells
void distanceMapper(std::vector<std::vector<Cell>>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      std::cout << grid[i][j].distance << '\t';
    }
    std::cout << std::endl;
  }
}

void gridStats(std::vector<std::vector<Cell>>& grid) {
  std::cout << "grid height: " << grid.size() << std::endl;
  std::cout << "grid width: " << grid[0].size() << std::endl;
}

// debug: print cell's information
void cellStats(Cell& cell) {
  std::cout << "memory location: " << &cell << std::endl;
  std::cout << "height: " << cell.getHeight() << std::endl;
  std::cout << "distance: " << cell.distance << std::endl;
  std::cout << "visited: " << cell.visited << std::endl;
  std::array<int, 2> coords = cell.getCoords();
  std::cout << "coords: " << coords[0] << ", " << coords[1] << std::endl;
  std::cout << "----------" << std::endl;
}

bool coordsEqual(const std::array<int, 2>& one, const std::array<int, 2>& two) {
  for (int i = 0; i < one.size(); i++) {
    if (one[i] != two[i]) {  // if an element doesn't match
      return false;
    }
  }

  return true;
}

bool outOfBounds(std::vector<std::vector<Cell>>& grid,
                 const std::array<int, 2>& coords) {
  if (coords[0] < 0  // check top
                     // check bottom: also handles the case of an empty last row
      || (coords[0] >= grid.size() || grid[coords[0]].size() == 0) ||
      coords[1] < 0                   // check left
      || coords[1] >= grid[0].size()  // check right
  ) {
    return true;
  }

  return false;
}

Cell& getCell(std::vector<std::vector<Cell>>& grid,
              std::array<int, 2>& coords) {
  int i = coords[0];
  int j = coords[1];
  return grid[i][j];
}

int main() {
  // phase 1: parse
  std::vector<std::vector<Cell>> grid(1);  // defaluts to one row, no cols
  std::array<int, 2> startCoords;
  char c;
  int rowCount = 0;
  int colCount = 0;
  std::ifstream fs("./adventofcode.com_2022_day_12_input.txt");
  while (fs >> std::noskipws >> c) {
    if (c == '\n') {
      grid.push_back(std::vector<Cell>());
      rowCount++;
      colCount = 0;
    } else {
      int height = getHeightNum(c);
      Cell newCell = Cell(rowCount, colCount, height);
      if (c == 'E') {
        startCoords = newCell.getCoords();
        newCell.visited = true;
        newCell.distance = 0;  // set distance of first cell to 0
      }
      grid[rowCount].push_back(newCell);
      colCount++;
    }
  }

  // printGrid(grid);  // DEBUG
  // gridStats(grid);  // DEBUG

  // phase 2: calculate distance
  std::vector<Cell> cellsToVisit = {getCell(grid, startCoords)};
  int shortest = std::numeric_limits<int>::max();  // stores shortest path to 0
  while (cellsToVisit.size() != 0) {
    Cell& currentCell = cellsToVisit[0];
    // std::cout << &currentCell << std::endl; // DEBUG: get memory location
    // currentCell.visited = true;  // mark cell as visited

    // std::cout << "current cell: vvv ======================== "  // DEBUG
    // << std::endl;                                     // DEBUG
    // cellStats(currentCell);                                     // DEBUG
    // std::cout << "^^^" << std::endl;                            // DEBUG

    // if current cell is lowest elevation
    if (currentCell.getHeight() == 0 && currentCell.distance < shortest) {
      shortest = currentCell.distance;
    }

    // check children
    std::array<std::array<int, 2>, 4> neighbors = {
        currentCell.getTop(), currentCell.getBottom(), currentCell.getLeft(),
        currentCell.getRight()};
    for (int i = 0; i < neighbors.size(); i++) {
      // if child is out of bounds, skip
      if (outOfBounds(grid, neighbors[i])) {
        continue;
      }

      Cell& nextCell = getCell(grid, neighbors[i]);

      // if unclimbable, skip
      if (nextCell.getHeight() < currentCell.getHeight() - 1) {
        continue;
      }

      // check if next cell is not visited or distance is shorter than before
      if (!nextCell.visited || nextCell.distance > currentCell.distance + 1) {
        // std::cout << "added to cellsToVisit" << std::endl;  // DEBUG
        // std::cout << "was it visited? " << nextCell.visited << std::endl;  // DEBUG 
        // std::cout << "old distance: " << nextCell.distance << std::endl;  // DEBUG 
        // std::cout << "new distance: " << currentCell.distance + 1 << std::endl; // DEBUG

        nextCell.distance = currentCell.distance + 1;
        nextCell.visited = true;
        cellsToVisit.push_back(nextCell);  // changes currentCell
        // cellStats(nextCell);               // DEBUG
      }
    }
    // delete currentCell from cellsToVisit after done
    cellsToVisit.erase(cellsToVisit.begin());
  }

  // distanceMapper(grid);  // DEBUG
  // printGrid(grid);       // DEBUG
  // gridStats(grid);       // DEBUG

  std::cout << shortest << std::endl;
}