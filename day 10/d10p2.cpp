#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <array>

int main() {
  int x = 1;
  int cycle = 0;
  int remainingCycles = 0;
  std::ifstream fs("./adventofcode.com_2022_day_10_input.txt");
  std::string command = "noop";
  int argument = 0;

  std::array<std::array<char, 40>, 10> screen;
  while (true) {  // iterate over cycles
    cycle++;
    if (remainingCycles == 0) {
      if (command == "addx") {
        x += argument;
      }

      // get next command
      if (!(fs >> command)) {
        break; // if no more commands left, break loop
      }
      if (command == "addx") {
        fs >> argument;
        remainingCycles = 2;
      } else if (command == "noop") {
        remainingCycles = 1;
      } else {
        throw std::runtime_error("invalid command!");
      }
    }
    remainingCycles--;

    // screen logic
    int row = (cycle - 1) / screen[0].size(); // 40 in this case
    int col = (cycle - 1) % screen[0].size();
    if (x - 1 == col || x == col || x + 1 == col) {
      screen[row][col] = '#';
    } else {
      screen[row][col] = '.';
    }
  }

  for (int i = 0; i < screen.size(); i++) {
    for (int j = 0; j < screen[i].size(); j++) {
      std::cout << screen[i][j];
    }
    std::cout << std::endl;
  }

  return 0;
}