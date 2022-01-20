#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <algorithm>
#include <utility>

std::pair<unsigned long, unsigned long> solution() {
    auto split = [](std::string const &l) -> std::array<int, 3> {
        std::stringstream ss;
        std::size_t first = l.find("x");
        std::size_t second = l.find("x", first+1);
        ss << l.substr(0, first) +  " "; 
        ss << l.substr(first+1, second-first-1) + " ";
        ss << l.substr(second+1);
        std::array<int, 3> res;
        ss >> res.at(0);
        ss >> res.at(1);
        ss >> res.at(2);
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