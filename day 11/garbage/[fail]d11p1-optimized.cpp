#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <tuple>

std::vector<int> getPrimes(int n) {
  std::vector<int> primes;
  for (int i = 2; i <= n; i++) {
    bool addedToPrimes = false;
    while (n % i == 0) { // while divisible
      if (!addedToPrimes) {
        primes.push_back(i);
        addedToPrimes = true;
      }
      // std::cout << n << std::endl;
      n = n / i; // divide until no more left
    }
  }
  return primes;
}

int multiplyVector(std::vector<int> vec) {
	int result = 1;
	for (int i =0; i < vec.size(); i++) {
		result *= vec[i];
	}
	return result;
}

// returns the common elements of two vectors
std::vector<int> vectorIntersection(std::vector<int> vec1, std::vector<int> vec2) {
	std::vector<int> intersection;
	for (int i = 0; i < vec1.size(); i++) {
		for (int j = 0; j < vec2.size(); j++) {
			if (vec1[i] == vec2[j]) {
				intersection.push_back(vec2[j]);
				continue; // next item in vec1
			}
		}
	}

	return intersection;
}

class Monkey {
 private:
	char sign; // either + or *
	std::string operand; // number after sign
	int divisibility; 
	int trueTarget;
	int falseTarget;

	long long operate(char sign, long long left, std::string rightstring) {
		// handle the case of right being "old"
		long long right;
		if (rightstring == "old") {
			right = left;
		} else {
			right = std::stoi(rightstring);
		}

		if (sign == '+') {
			// return left + right; // TODO: revert
			long long var = left + right;
			return var;
		} else if (sign == '*') {
			// return left * right; // TODO: revert
			long long var = left * right;
			return var;
		} else {
			throw std::runtime_error("invalid operator!");
		}
	}
 
 public:
	std::vector<long long> items;
	int activity = 0;

	// mainly for debugging: prints all monkey stats
	void printStats() {
		// print inventory
		std::cout << "Inventory: ";
		for (const int& item : items) {
			std::cout << item << ", ";
		}
		std::cout << std::endl;

		// print operations
		std::cout << "Operations: " << sign << " " << operand << std::endl;
		std::cout << "divisibility: " << divisibility << std::endl;
		std::cout << "trueTarget: " << trueTarget << std::endl;
		std::cout << "falseTarget: " << falseTarget << std::endl;
	}

	std::tuple<long long, int> examine(long long itemValue, int supermod) {
		long long worryLevel = operate(sign, itemValue, operand);
		worryLevel /= 3; // after inspection is done
		// replace worryLevel as with the multiple of needed primes
		// worryLevel %= supermod; // FIXME: bring back supermod
		int targetMonkey;
		if (worryLevel % divisibility == 0) {
			targetMonkey = trueTarget;
		} else {
			targetMonkey = falseTarget;
		}

		return {worryLevel, targetMonkey};
	}

	Monkey(
		std::vector<long long>& items,
		char sign, // either + or *
		std::string operand, // number after sign
		int divisibility, 
		int trueTarget,
		int falseTarget
	) : 
		items(items),
		sign(sign),
		operand(operand),
		divisibility(divisibility),
		trueTarget(trueTarget),
		falseTarget(falseTarget)
	{}
};

void skip(std::ifstream& fs, int count) {
	std::string trash;
	for (int i = 0; i < count; i++) {
		fs >> trash;
	}
}

void parseVector(std::ifstream& fs, std::vector<long long>& vec) {
	char comma;
	long long num;
	while(fs >> num >> comma) {
		vec.push_back(num); 
		if (comma != ',') {
			break; // stop after reaching "O from Operation:"
		}
	}
}

// debug: prints each monkey's items
void printAllMonkeyStats(std::vector<Monkey>& monkeys) {
	for (int i = 0; i < monkeys.size(); i++) {
		std::cout << "Monkey " << i << std::endl;
		monkeys[i].printStats();
		std::cout << "----------" << std::endl;
	}
}

int main() {
	std::vector<Monkey> monkeys;

	// phase 1: the file
	std::ifstream fs("./adventofcode.com_2022_day_11_input.txt");
	// std::ifstream fs("./test_input.txt"); // FIXME:
	// std::ifstream fs("./test_input_2.txt"); // FIXME:
	std::string keyword;
	std::string trash;
	std::vector<int> inputPrimes;
	int monkeyIndex = 0;
	while (fs >> keyword) {
		if (keyword != "Monkey") { // keyword must be monkey
			throw std::runtime_error("keyword not Monkey");
		}

		skip(fs, 3); // skip ": Starting items:"
		std::vector<long long> monkeyItems;
		parseVector(fs, monkeyItems); // get items 

		skip(fs, 4); // skip "peration: new = old"
		char sign;
		fs >> sign; 
		std::string operand; 
		fs >> operand; 
		
		skip(fs, 3); // skip "Test: divisible by"
		int divisibility;
		fs >> divisibility;
		inputPrimes.push_back(divisibility);

		skip(fs, 5); // skip "if true: throw to monkey"
		int trueTarget;
		fs >> trueTarget;

		skip(fs, 5); // skip "if false: throw to monkey"
		int falseTarget;
		fs >> falseTarget;

		monkeys.push_back(Monkey( // add new monkey to vector
			monkeyItems,
			sign,
			operand,
			divisibility,
			trueTarget,
			falseTarget
		));

		monkeyIndex++;
	}

	// phase 2: track activity
	int roundCount = 20;
	// int roundCount = 1; // FIXME: use original roundCount
	for (int round = 0; round < roundCount; round++) {
		for (int monkeyIdx = 0; monkeyIdx < monkeys.size(); monkeyIdx++) {
			Monkey& monkey = monkeys[monkeyIdx];
			while (monkey.items.size() != 0) {
				int worryLevel = monkey.items[0]; // get first value
				monkey.items.erase(monkey.items.begin()); // delete from items
				monkey.activity++; // increase monkey activity
				// select monkey to throw item at
				auto [
					newWorryLevel, 
					targetMonkeyIdx
				] = monkey.examine(worryLevel, multiplyVector(inputPrimes));
				// give item to other monkey
				monkeys[targetMonkeyIdx].items.push_back(newWorryLevel);
			}
		}
	}

	// print monkey inventory
	printAllMonkeyStats(monkeys); // DEBUG

	// phase 3: get 2 most active monkeys
	std::array<int, 2> top2;
	top2.fill(0); // fill with zeros
	for (const Monkey& monkey: monkeys) {

			// print monkey activity
			std::cout << monkey.activity << std::endl;

		int minIndex = -1; // just in case
		if (top2[0] < top2[1]) { // get smaller item in list
			minIndex = 0;
		} else {
			minIndex = 1;
		}

		if (top2[minIndex] < monkey.activity) {
			// replace smaller activity with current activity
			top2[minIndex] = monkey.activity;
		}
	}

	int monkeyBusiness = top2[0] * top2[1];

	std::cout << monkeyBusiness << std::endl;
}