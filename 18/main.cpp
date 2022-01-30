#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <iterator>

const size_t ARR_SIZE(100);

std::array<std::string, ARR_SIZE> read_from_file
(std::string file_name) {
    std::array<std::string, ARR_SIZE> res;
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    int i(0);
    while(std::getline(input_file, line)) {
        res.at(i) = line;
        i++;
    }
    return res;
}

unsigned silver(std::array<std::string, ARR_SIZE> arr, bool gold=false) {
    auto check_neighbours = [&](int x, int y) -> unsigned {
        unsigned sum(0);
        sum += x!=ARR_SIZE-1 ? arr.at(y).at(x+1) == '#' : 0;
        sum += y!=ARR_SIZE-1 ? arr.at(y+1).at(x) == '#' : 0;
        sum += y!=0 ? arr.at(y-1).at(x) == '#' : 0;
        sum += x!=0 ? arr.at(y).at(x-1) == '#' : 0;
        sum += y!=ARR_SIZE-1 && x!=ARR_SIZE-1 ? arr.at(y+1).at(x+1) == '#' : 0;
        sum += y!=0 && x!=ARR_SIZE-1 ? arr.at(y-1).at(x+1) == '#' : 0;
        sum += y!=0 && x!=0 ? arr.at(y-1).at(x-1) == '#' : 0;
        sum += y!=ARR_SIZE-1 && x!=0 ? arr.at(y+1).at(x-1) == '#' : 0;
        return sum;
    };
    auto animate = [&]() -> std::array<std::string, ARR_SIZE> {
        auto tmp(arr);
        for(auto i(0); i < ARR_SIZE; ++i) {
            for(auto j(0); j < ARR_SIZE; ++j) {
                if(gold) {
                    if((i==0&&j==0)||(i==0&&j==ARR_SIZE-1)||
                    (i==ARR_SIZE-1&&j==0)||(i==ARR_SIZE-1&&j==ARR_SIZE-1))
                            continue;
                }
                auto sum = check_neighbours(j, i);
                if(arr.at(i).at(j) == '#') {
                    if(!(sum == 2 || sum == 3)) 
                        tmp.at(i).at(j) = '.';
                } else if(sum == 3)
                    tmp.at(i).at(j) = '#';
            }
        }
        return tmp;
    };
    for(auto i(0); i < ARR_SIZE; ++i) {
        arr = animate();
    }
    unsigned sum(0);
    for(auto const &el : arr) {
        for(auto const &ch : el) 
            sum += ch == '#';
    }

    return sum;
}

unsigned gold(std::array<std::string, ARR_SIZE> arr) {
    arr.at(0).at(0) = '#';
    arr.at(0).at(ARR_SIZE-1) = '#';
    arr.at(ARR_SIZE-1).at(0) = '#';
    arr.at(ARR_SIZE-1).at(ARR_SIZE-1) = '#';
    return silver(arr, true);
}

int main() {
    auto board = read_from_file("input.txt");
    std::cout << "Silver: " << silver(board) << '\n';
    std::cout << "Gold: " << gold(board) << '\n';
}