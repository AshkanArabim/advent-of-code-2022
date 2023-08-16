#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  // keep a record of the number of cycles
  // keep a record of the value of X (some operations take 2 steps)
  // if cycle is 20, 60, 100, 140, 180, 220, add (cycle * X) to answer
  int cycle = 0;
  int x = 1;  // value of register
  int answer = 0;

  std::string line;
  std::ifstream fs("./adventofcode.com_2022_day_10_input.txt");
  // std::ifstream fs("./test_input.txt");
  bool recentlyAdded = false;
  while (std::getline(fs, line)) {
    // check what the first word is
    std::stringstream ls(line);
    std::cout << "----------------" << std::endl;  // DEBUg
    std::cout << "line: " << line << std::endl;    // DEBUG
    std::string operation;
    ls >> operation;                                       // get the first word
    std::cout << "operation: " << operation << std::endl;  // DEBUG
    if (operation == "addx") {
      cycle += 2;
      // get the amout to add to x
      int addtox;
      ls >> addtox;
      std::cout << "addtox: " << addtox << std::endl;  // DEBUG
      x += addtox;
      std::cout << "x: " << x << std::endl;  // DEBUG
    } else if (operation == "noop") {
      cycle++;
    } else {
      std::cout << "invalid command: " << operation << std::endl;  // DEBUG
      throw std::runtime_error("invalid command!!");  // just in case
    }

    // check if cycle matches. if so, add x * target cycle to answer
    if (!recentlyAdded) {
      for (int i = 0; i < 6; i++) {
        int target = (40 * i) + 20;  // from 0, to 220;
                                     // int target = 7; // DEBUG
        if (cycle == target - 1 || cycle == target - 2) {
          // DURING the cycle: if we are at 20 and we are supposed to finish
          // adding by 20, we are not finished yet.
          std::cout << "ADDED SIGNAL STRENGTH: ";
          std::cout << "after " << cycle << " = during " << target
                    << std::endl;  // DEBUG
          answer += (target * x);
          recentlyAdded = true;
          std::cout << "x: " << x << std::endl;
          std::cout << "target: " << target << std::endl;
          std::cout << "to add: " << target * x << std::endl;
          std::cout << "answer: " << answer << std::endl;
        }
      }
    } else {
      recentlyAdded = false;  // only skips one line
    }
  }

  std::cout << answer << std::endl;

  return 0;
}