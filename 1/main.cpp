#include <iostream>
#include <fstream>
#include <map>
#include <utility>

int main() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string data;
    input_file >> data;
    std::map<char, int> dir;
    dir.insert(std::make_pair('(', 0));
    dir.insert(std::make_pair(')', 0));
    for(auto const &c : data) {
        dir.at(c)++;
    }
    std::cout << dir.at('(')-dir.at(')') << '\n';
}