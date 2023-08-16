#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  int x = 1;
  int cycle = 0;
  int remainingCycles = 0;
  std::ifstream fs("./adventofcode.com_2022_day_10_input.txt");
  std::string command = "noop";
  int argument = 0;

  int answer = 0;
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

    // logger logic
    for (int i = 0; i < 6; i++) {
      int target = (40 * i) + 20;  // from 0, to 220, intervals of 40
      if (cycle == target) {
        answer += (cycle * x);
      }
    }
  }

  std::cout << answer << std::endl;

  return 0;
}