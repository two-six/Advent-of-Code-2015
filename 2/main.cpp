#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <utility>
#include <regex>

std::pair<unsigned long, unsigned long> solution() {
    auto split = [](std::string const &l) -> std::array<int, 3> {
        std::regex reg("(\\d+)x(\\d+)x(\\d+)");
        std::smatch sm;
        std::regex_match(l, sm, reg);
        std::cout << sm[0].str() << '\n';
        std::array<int, 3> res;
        for(int i = 0; i < 3; ++i) 
            res.at(i) = std::stoi(sm[i+1].str());
        return res;
    };
    std::fstream input_file("input.txt", std::ios::in);
    std::string data;
    unsigned long sum = 0; 
    unsigned long ribbon = 0;
    while(input_file >> data) {
        auto res = split(data);
        std::sort(res.begin(), res.end());
        sum += 2*(res.at(0)*res.at(1) + res.at(0)*res.at(2) + res.at(1)*res.at(2))
             + res.at(0)*res.at(1); 
        ribbon += (2*(res.at(0)+res.at(1)))+(res.at(0)*res.at(1)*res.at(2));
    }
    input_file.close();

    return std::make_pair(sum, ribbon);
}

int main() {
    auto sol = solution();
    std::cout << "Silver: " << sol.first << '\n';
    std::cout << "Gold: " << sol.second << '\n';
}