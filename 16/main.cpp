#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <regex>
#include <string>
#include <system_error>
#include <utility>

std::array<std::map<std::string, int>, 500> read_from_file
(std::string file_name) {
    std::array<std::map<std::string, int>, 500> res;
    std::fstream input_file(file_name, std::ios::in);   
    std::regex reg("Sue (\\d+): (\\w+): (\\d+),"
    " (\\w+): (\\d+), (\\w+): (\\d+)");
    std::string line;
    while(std::getline(input_file, line)) {
        std::smatch sm;
        std::regex_match(line, sm, reg);
        auto id = std::stoi(sm[1].str())-1;
        std::map<std::string, int> tmp;
        tmp.insert(std::make_pair(sm[2].str(), std::stoi(sm[3].str())));
        tmp.insert(std::make_pair(sm[4].str(), std::stoi(sm[5].str())));
        tmp.insert(std::make_pair(sm[6].str(), std::stoi(sm[7].str())));
        res.at(id) = tmp;
    }
    return res;
} 

unsigned silver(std::map<std::string, int> orig,
std::array<std::map<std::string, int>, 500> arr) {
    for(auto i(0); i < 500; ++i) {
        int sum(0);
        for(auto const &el : arr.at(i)) {
            if(orig.at(el.first) == el.second)
                sum++;
        }
        if(sum == 3)
            return i+1;
    }
    return 0;
}
unsigned gold(std::map<std::string, int> orig,
std::array<std::map<std::string, int>, 500> arr) {
    for(auto i(0); i < 500; ++i) {
        int sum(0);
        for(auto const &el : arr.at(i)) {
            if(el.first == "cats" || el.first == "trees") {
                if(orig.at(el.first) < el.second)
                    sum++;
            } else if(el.first == "pomeranians" || el.first == "goldfish") {
                if(orig.at(el.first) > el.second)
                    sum++;
            } else {
                if(orig.at(el.first) == el.second)
                    sum++;
            }
        }
        if(sum == 3)
            return i+1;
    }
    return 0;
}

int main() {
    std::map<std::string, int> sue;
    sue.insert(std::make_pair("children", 3));
    sue.insert(std::make_pair("cats", 7));
    sue.insert(std::make_pair("samoyeds", 2));
    sue.insert(std::make_pair("pomeranians", 3));
    sue.insert(std::make_pair("akitas", 0));
    sue.insert(std::make_pair("vizslas", 0));
    sue.insert(std::make_pair("goldfish", 5));
    sue.insert(std::make_pair("trees", 3));
    sue.insert(std::make_pair("cars", 2));
    sue.insert(std::make_pair("perfumes", 1));

    auto res = read_from_file("input.txt");
    std::cout << "Silver: " << silver(sue, res) << '\n';
    std::cout << "Gold: " << gold(sue, res) << '\n';
}