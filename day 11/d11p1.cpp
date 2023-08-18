//
//
// NOTE: I changed all ints to long longs to avoid overflow
// I was too lazy to see what was causing the overflow exactly
// I DON'T CARE WHAT YOU THINK!!!!!!
//
//

#include <array>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

class Monkey {
 private:
  char sign;            // either + or *
  std::string operand;  // number after sign
  long long divisibility;
  long long trueTarget;
  long long falseTarget;

  long long operate(char sign, long long left, std::string rightstring) {
    // handle the case of right being "old"
    long long right;
    if (rightstring == "old") {
      right = left;
    } else {
      right = std::stoi(rightstring);
    }

    if (sign == '+') {
      return left + right;
    } else if (sign == '*') {
      return left * right;
    } else {
      throw std::runtime_error("invalid operator!");
    }
  }

 public:
  std::vector<long long> items;
  long long activity = 0;

  // mainly for debugging: prints all monkey stats
  void printStats() {
    // print inventory
    std::cout << "Inventory: ";
    for (const long long& item : items) {
      std::cout << item << ", ";
    }
    std::cout << std::endl;

    // print operations
    std::cout << "Operations: " << sign << " " << operand << std::endl;
    std::cout << "divisibility: " << divisibility << std::endl;
    std::cout << "trueTarget: " << trueTarget << std::endl;
    std::cout << "falseTarget: " << falseTarget << std::endl;
  }

  std::tuple<long long, long long> examine(long long itemValue) {
    long long worryLevel = operate(sign, itemValue, operand);
    worryLevel /= 3;  // after inspection is done
    long long targetMonkey;
    if (worryLevel % divisibility == 0) {
      targetMonkey = trueTarget;
    } else {
      targetMonkey = falseTarget;
    }

    return {worryLevel, targetMonkey};
  }

  Monkey(std::vector<long long>& items,
         char sign,            // either + or *
         std::string operand,  // number after sign
         long long divisibility, long long trueTarget, long long falseTarget)
      : items(items),
        sign(sign),
        operand(operand),
        divisibility(divisibility),
        trueTarget(trueTarget),
        falseTarget(falseTarget) {}
};

void skip(std::ifstream& fs, long long count) {
  std::string trash;
  for (long long i = 0; i < count; i++) {
    fs >> trash;
  }
}

void parseVector(std::ifstream& fs, std::vector<long long>& vec) {
  char comma;
  long long num;
  while (fs >> num >> comma) {
    vec.push_back(num);
    if (comma != ',') {
      break;  // stop after reaching "O from Operation:"
    }
  }
}

// debug: prints each monkey's items
void printAllMonkeyStats(std::vector<Monkey>& monkeys) {
  for (long long i = 0; i < monkeys.size(); i++) {
    std::cout << "Monkey " << i << std::endl;
    monkeys[i].printStats();
    std::cout << "----------" << std::endl;
  }
}

int main() {
  std::vector<Monkey> monkeys;

  // phase 1: the file
  std::ifstream fs("./adventofcode.com_2022_day_11_input.txt");
  std::string keyword;
  std::string trash;
  long long monkeyIndex = 0;
  while (fs >> keyword) {
    if (keyword != "Monkey") {  // keyword must be monkey
      throw std::runtime_error("keyword not Monkey");
    }

    skip(fs, 3);  // skip ": Starting items:"
    std::vector<long long> monkeyItems;
    parseVector(fs, monkeyItems);  // get items

    skip(fs, 4);  // skip "peration: new = old"
    char sign;
    fs >> sign;
    std::string operand;
    fs >> operand;

    skip(fs, 3);  // skip "Test: divisible by"
    long long divisibility;
    fs >> divisibility;

    skip(fs, 5);  // skip "if true: throw to monkey"
    long long trueTarget;
    fs >> trueTarget;

    skip(fs, 5);  // skip "if false: throw to monkey"
    long long falseTarget;
    fs >> falseTarget;

    monkeys.push_back(Monkey(  // add new monkey to vector
        monkeyItems, sign, operand, divisibility, trueTarget, falseTarget));

    monkeyIndex++;
  }

  // phase 2: track activity
  long long roundCount = 20;
  for (long long round = 0; round < roundCount; round++) {
    for (long long monkeyIdx = 0; monkeyIdx < monkeys.size(); monkeyIdx++) {
      Monkey& monkey = monkeys[monkeyIdx];
      while (monkey.items.size() != 0) {
        long long worryLevel = monkey.items[0];    // get first value
        monkey.items.erase(monkey.items.begin());  // delete from items
        monkey.activity++;                         // increase monkey activity
        // select monkey to throw item at
        auto [newWorryLevel, targetMonkeyIdx] = monkey.examine(worryLevel);
        // give item to other monkey
        monkeys[targetMonkeyIdx].items.push_back(newWorryLevel);
      }
    }
  }

  // print monkey inventory
  // phase 3: get 2 most active monkeys
  std::array<long long, 2> top2;
  top2.fill(0);  // fill with zeros
  for (const Monkey& monkey : monkeys) {
    // print monkey activity
    std::cout << monkey.activity << std::endl;

    long long minIndex = -1;  // just in case
    if (top2[0] < top2[1]) {  // get smaller item in list
      minIndex = 0;
    } else {
      minIndex = 1;
    }

    if (top2[minIndex] < monkey.activity) {
      // replace smaller activity with current activity
      top2[minIndex] = monkey.activity;
    }
  }

  long long monkeyBusiness = top2[0] * top2[1];

  std::cout << monkeyBusiness << std::endl;
}