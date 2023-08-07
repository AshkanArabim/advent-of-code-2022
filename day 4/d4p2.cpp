#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int count = 0;
    // int tempcount = 0; // DEBUG
    ifstream file("./adventofcode.com_2022_day_4_input.txt");
    
    // string line;
    int beginElf1, beginElf2, endElf1, endElf2;
    char garbage;
    while(
        file >> beginElf1 
        >> garbage >> endElf1 
        >> garbage >> beginElf2
        >> garbage >> endElf2
    ){
        // cout << "-----------" << endl; // DEBUG
        // cout << "begin elf 1: " << beginElf1 << endl; // DEBUG
        // cout << "end elf 1: " << endElf1 << endl; // DEBUG
        // cout << "begin elf 2: " << beginElf2 << endl; // DEBUG
        // cout << "end elf 2: " << endElf2 << endl; // DEBUG

        if (
            (beginElf1 <= beginElf2 && endElf1 >= beginElf2) // starting endpoint of 2 is between 1
            || (beginElf2 <= beginElf1 && endElf2 >= beginElf1) // starting endpoint of 1 is between 2
        ) { 
            count++;
            // tempcount++; // DEBUG
            // cout << "found one!!" << endl; // DEBUG
        }

        // if (tempcount > 5) break; // DEBUG
    }

    cout << count << endl;
}