#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <tuple>

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
			return left + right;
		} else if (sign == '*') {
			return left * right;
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

	std::tuple<long long, int> examine(long long itemValue) {
		long long worryLevel = operate(sign, itemValue, operand);
		int targetMonkey;
		worryLevel /= 3; // after inspection is done
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
	std::string keyword;
	std::string trash;
	int phase1MonkeyIndex = 0;
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

		// DEBUG
		// for (int i = 0; i < monkeyItems.size(); i++) {
		// 	std::cout << monkeyItems[i] << std::endl;
		// }
		// std::cout << "-------------" << std::endl;

		phase1MonkeyIndex++;
	}

	// std::cout << "Before: ==============================" << std::endl; // DEBUG
	// printAllMonkeyStats(monkeys); // DEBUG


	// phase 2: track activity
	// std::cout << "Between: ==============================" << std::endl; // DEBUG
	int roundCount = 20;
	// int roundCount = 15; // FIXME: revert to original
	for (int round = 0; round < roundCount; round++) {
		for (int monkeyIdx = 0; monkeyIdx < monkeys.size(); monkeyIdx++) {
			Monkey& monkey = monkeys[monkeyIdx];
			// std::cout << "Monkey " << monkeyIdx << "'s turn" << std::endl; // DEBUG
			// printAllMonkeyStats(monkeys); // DEBUG
			// std::cout << "##########" << std::endl; // DEBUG
			while (monkey.items.size() != 0) {
				int worryLevel = monkey.items[0]; // get first value
				monkey.items.erase(monkey.items.begin()); // delete from items
				monkey.activity++; // increase monkey activity
				// select monkey to throw item at
				auto [newWorryLevel, targetMonkeyIdx] = monkey.examine(worryLevel); 
				// give item to other monkey
				monkeys[targetMonkeyIdx].items.push_back(newWorryLevel);
			}
		}
	}

	std::cout << "After: ==============================" << std::endl; // DEBUG
	printAllMonkeyStats(monkeys); // DEBUG

	// print monkey inventory
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