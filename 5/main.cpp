#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

unsigned silver() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string line;
    unsigned sum(0);
    while(input_file >> line) {
        auto cou = [&](char c) -> unsigned {
            return std::count(line.begin(), line.end(), c);
        };
        unsigned vowels = cou('a')+cou('e')+cou('i')+cou('o')+cou('u');

        bool row = false;
        for(int i = 0; i < line.size()-1; ++i) {
            if(line[i] == line[i+1]) {
                row = true;
                break;
            }
        }

        auto exists = [&](std::string const &f) -> bool {
            return line.find(f) == std::string::npos;
        };
        bool contains_disallowed = exists("ab") && exists("cd") && exists("pq") && exists("xy");
        if(vowels >= 3 && row && contains_disallowed)
            sum++;
    }
    input_file.close();
    return sum;
}

unsigned gold() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string line;
    unsigned sum(0);
    while(input_file >> line) {
        auto pair = [&]() -> bool {
            std::map<std::string, int> pairs;
            for(auto i = 0; i < line.size()-1; ++i) {
                if(pairs.count(line.substr(i, 2)) == 0)
                    pairs.insert(std::make_pair(line.substr(i, 2), i));
                else {
                    if(pairs.at(line.substr(i, 2)) != i-1)
                        return true;
                }
            }
            return false;
        };
        auto neighbours = [&]() -> bool {
            for(auto i = 0; i < line.size()-2; ++i) {
                if(line[i] == line[i+2])
                    return true;
            }
            return false;
        };
        if(pair() && neighbours())
            sum++;
    }
    input_file.close();
    return sum;
}

int main() {
    std::cout << "Silver: " << silver() << '\n';
    std::cout << "Gold: " << gold() << '\n';
}