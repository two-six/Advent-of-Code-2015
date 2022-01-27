/*
I just want to add I really don't like how this code looks like. 
*/


#include <cmath>
#include <iostream>
#include <fstream>
#include <locale>
#include <regex>
#include <string>
#include <utility>

typedef struct Ingredient {
    std::string name;
    std::array<int, 5> prop;
} Ingredient;

std::vector<Ingredient> read_data(std::string file_name) {
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    std::regex reg("(\\w+): capacity (-?\\d+), durability "
    "(-?\\d+), flavor (-?\\d+), texture (-?\\d+),"
    " calories (-?\\d+)");

    std::vector<Ingredient> ings;
    while(std::getline(input_file, line)) {
        std::smatch sm;
        std::regex_match(line, sm, reg);
        Ingredient tmp;
        tmp.name = sm[1].str();
        for(auto i(2); i <= 6; ++i)
            tmp.prop.at(i-2) = std::stoi(sm[i].str());
        ings.push_back(tmp);
    } 
    return ings;
}

long unsigned solve(std::vector <Ingredient> ings, bool gold=false) {
    auto count = [&](std::vector<std::pair<int, int>> val, 
    std::vector<Ingredient> ing) -> unsigned long {
        std::array<int, 5> res;
        res.fill(0);
        for(auto const &el : val) {
            for(auto i(0); i < 5; ++i) {
                res.at(i) += el.second*ing.at(el.first).prop.at(i);
            }
        }
        unsigned long sum(1);
        if(gold) {
            if(res.at(4) != 500)
                return 0;
        }
        for(auto i(0); i < 4; ++i) {
            if(res.at(i) < 0)
                return 0;
            sum *= res.at(i);
        }
        return sum;
    };

    auto biggest = [&](std::vector<Ingredient> ing) -> unsigned long {
        unsigned long m(0);
        if(ing.size() == 2) {
            for(auto i(1); i <= 99; ++i) {
                std::vector<std::pair<int, int>> tmp;
                tmp.push_back(std::make_pair(0, i));
                tmp.push_back(std::make_pair(1, 100-i));
                auto res = count(tmp, ing);
                if(m < res)
                    m = res;
            }
        } else if(ing.size() == 3) {
            for(auto i(1); i <= 98; ++i) {
                for(auto j(1); j < 99-i; ++j) {
                    std::vector<std::pair<int, int>> tmp;
                    tmp.push_back(std::make_pair(0, i));
                    tmp.push_back(std::make_pair(1, j));
                    tmp.push_back(std::make_pair(2, (100-i)-j));
                    auto res = count(tmp, ing);
                    if(m < res)
                        m = res;
                }
            }
        } else if(ing.size() == 4) {
            for(auto i(1); i <= 97; ++i) {
                for(auto j(1); j < 98-i; ++j) {
                    for(auto k(1); k < 98-i-j; ++k) {
                        std::vector<std::pair<int, int>> tmp;
                        tmp.push_back(std::make_pair(0, i));
                        tmp.push_back(std::make_pair(1, j));
                        tmp.push_back(std::make_pair(2, k));
                        tmp.push_back(std::make_pair(3, (100-i)-j-k));
                        auto res = count(tmp, ing);
                        if(m < res)
                            m = res;
                    }
                }
            }

        }
        return m;
    };
    unsigned long m(0);
    for(auto i(0); i < 3; ++i) {
        for(auto j(i+1); j < 4; ++j) {
            std::vector<Ingredient> tmp;
            tmp.push_back(ings.at(i));
            tmp.push_back(ings.at(j));
            auto res = biggest(tmp);
            if(res > m)
                m = res;
        }
    }
    for(auto i(0); i < 2; ++i) {
        for(auto j(i+1); j < 3; ++j) {
            for(auto k(j+1); k < 4; ++k) {
                std::vector<Ingredient> tmp;
                tmp.push_back(ings.at(i));
                tmp.push_back(ings.at(j));
                tmp.push_back(ings.at(k));
                auto res = biggest(tmp);
                if(res > m)
                    m = res;
            }
        }
    }
    auto res = biggest(ings);
    if(res > m)
        m = res;

    return m;
} 

int main() {
    auto ings = read_data("input.txt");
    std::cout << "Silver: " << solve(ings) << '\n';
    std::cout << "Gold: " << solve(ings, true) << '\n';
}