#include <iostream>
#include <fstream>
#include <set>
#include <utility>

unsigned silver() {
    std::set<std::pair<int, int>> res = {std::make_pair(0, 0)};
    std::fstream input_file("input.txt", std::ios::in);
    std::string dir;
    input_file >> dir;
    input_file.close();
    int x(0), y(0);
    for(auto const &c : dir) {
        switch(c) {
            case '>':
                x += 1;
                break;
            case '<':
                x -= 1;
                break;
            case '^':
                y -= 1;
                break;
            case 'v':
                y += 1;
                break;
        }
        res.insert(std::make_pair(x, y));
    }

    return res.size();
}

unsigned gold() {
    std::set<std::pair<int, int>> santa = {std::make_pair(0, 0)};
    std::set<std::pair<int, int>> robosanta = {std::make_pair(0, 0)};
    std::fstream input_file("input.txt", std::ios::in);
    std::string dir;
    input_file >> dir;
    input_file.close();
    int x(0), y(0);
    int rx(0), ry(0);
    bool isSanta = true;
    for(auto const &c : dir) {
        switch(c) {
            case '>':
                if(isSanta)
                    x += 1;
                else
                    rx += 1;
                break;
            case '<':
                if(isSanta)
                    x -= 1;
                else
                    rx -= 1;
                break;
            case '^':
                if(isSanta)
                    y -= 1;
                else
                    ry -= 1;
                break;
            case 'v':
                if(isSanta)
                    y += 1;
                else
                    ry += 1;
                break;
        }
        santa.insert(std::make_pair(x, y));
        robosanta.insert(std::make_pair(rx, ry));
        isSanta = !isSanta;
    }
    santa.insert(robosanta.begin(), robosanta.end());
    return santa.size();
}

int main() {
    std::cout << "Silver: " << silver() << '\n';
    std::cout << "Gold: " << gold() << '\n';
}