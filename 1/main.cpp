#include <iostream>
#include <fstream>
#include <map>
#include <utility>

std::pair<int, int> solution() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string data;
    input_file >> data;
    input_file.close();
    std::map<char, int> dir;
    dir.insert(std::make_pair('(', 0));
    dir.insert(std::make_pair(')', 0));
    bool been_in_basement = false;
    int gold = 0;
    for(auto const &c : data) {
        dir.at(c)++;
        if(dir.at('(')-dir.at(')') < 0 && !been_in_basement) {
            been_in_basement = true;
            gold++;
        } else if(!been_in_basement) {
            gold++;
        }
    }
    return std::make_pair(dir.at('(')-dir.at(')'), gold);
}

int main() {
    auto sol = solution();
    std::cout << "Silver: " << sol.first << '\n';
    std::cout << "Gold: " << sol.second << '\n';
}