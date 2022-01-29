#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> read_from_file(std::string file_name) {
    std::vector<int> res;
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    while(std::getline(input_file, line)) 
        res.push_back(std::stoi(line));
    input_file.close();
    return res;
}


unsigned silver(std::vector<int> vec, bool min=false, int n=0) {
    int c(0);
    for(int i(0); i < (1 << vec.size()); ++i) {
        int t(i);
        int s(0);
        int count(0);
        for(auto const &el : vec) {
            if(t%2 == 1) {
                s += el;
                count++;
            }
            t = std::floor(t/2);
            if(t == 0)
                break;
        }
        if(s == 150) {
            if(!min || (min && count == n)) {
                c++;
            }
        }
    }
    return c;
}

unsigned gold(std::vector<int> vec) {
    std::sort(vec.begin(), vec.end());
    int c(0);
    int sum(0);
    for(auto i(vec.size()-1); i >= 0; --i) {
        c++;
        sum += vec.at(i);
        if(sum >= 150)
            break;
    }
    return silver(vec, true, c);
}

int main() {
    auto vec = read_from_file("input.txt");
    std::cout << "Silver: " << silver(vec) << '\n';
    std::cout << "Gold: " << gold(vec) << '\n';
}