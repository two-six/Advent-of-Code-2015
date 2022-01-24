#include <cstdio>
#include <functional>
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <regex>
#include <algorithm>

typedef struct Data {
    std::string person;
    int happiness;
} Data;

std::map<std::string, std::vector<Data>> read_from_file(std::string file_name) {
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    std::regex up("(\\w+) would gain (\\d+) happiness units by sitting next to (\\w+).");
    std::regex down("(\\w+) would lose (\\d+) happiness units by sitting next to (\\w+).");
    std::map<std::string, std::vector<Data>> people;
    auto insert = [&](bool const &up, std::smatch const &sm) {
        if(people.count(sm[1].str()) == 0) {
            std::vector<Data> tmp;
            people.insert(std::make_pair(sm[1].str(), tmp));
        }
        people.at(sm[1].str()).push_back(Data{sm[3].str(), 
            (up ? std::stoi(sm[2].str()) : -std::stoi(sm[2].str()))});
    };
    while(std::getline(input_file, line)) {
        std::smatch sm;
        if(std::regex_match(line, sm, up)) {
            insert(true, sm);
        } else if(std::regex_match(line, sm, down)) {
            insert(false, sm);
        }
    }
    input_file.close();
    return people;
}

std::vector<std::vector<std::string>> all_combinations(std::vector<std::string> names) {
    std::vector<std::vector<std::string>> combinations;
    std::sort(names.begin(), names.end());
    do {
        combinations.push_back(names);
    } while(std::next_permutation(names.begin(), names.end()));
    if(combinations.size()%2 == 0) 
        combinations.erase(combinations.begin()+(combinations.size()/2), combinations.end());
    return combinations;
}

int silver(std::map<std::string, std::vector<Data>> const people, 
    std::vector<std::vector<std::string>> combinations) {

    auto connection = [&](std::string n1, std::string n2) -> int {
        int sum(0);
        auto con = [&](std::string t1, std::string t2) {
            for(auto const &el : people.at(t1)) {
                if(el.person == t2) {
                    sum += el.happiness;
                    return;
                }
            }
        };
        con(n1, n2);
        con(n2, n1);

        return sum;
    };
    int m(0);
    for(auto const &el : combinations) {
        int sum(0);
        for(int i(0); i < el.size()-1; ++i) {
            sum += connection(el.at(i), el.at(i+1));
        }
        sum += connection(el.at(0), el.at(el.size()-1));
        if(m < sum)
            m = sum;
    }
    return m;
}

int gold(std::map<std::string, std::vector<Data>> people, 
    std::vector<std::vector<std::string>> combinations) {
    std::vector<Data> tmp;
    for(auto const &el : combinations.at(0)) 
        tmp.push_back(Data{el, 0});
    people.insert(std::make_pair("me", tmp));
    combinations.erase(combinations.begin(), combinations.end());
    std::vector<std::string> names;
    for(auto const &el : people) {
        names.push_back(el.first);
    }
    combinations = all_combinations(names);
    return silver(people, combinations);
}

int main() {
    auto people = read_from_file("input.txt");
    std::vector<std::string> names;
    for(auto const &el : people) {
        names.push_back(el.first);
    }
    auto combinations = all_combinations(names);
    std::cout << "Silver: " << silver(people, combinations) << '\n';
    std::cout << "Gold: " << gold(people, combinations) << '\n';
}