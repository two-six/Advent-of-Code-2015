#include <iostream>
#include <vector>
#include <utility>

std::string const INITIAL_INPUT = "3113322113";

std::vector<std::pair<unsigned, unsigned>> look_and_say(std::vector<std::pair<unsigned, unsigned>> sequence) {
    std::vector<std::pair<unsigned, unsigned>> res;
    auto insert = [&](std::pair<unsigned, unsigned> p) {
        if(res.size() == 0) {
            res.push_back(p);
        } else if(res.at(res.size()-1).first == p.first) {
            res.at(res.size()-1).second += p.second;
        } else {
            res.push_back(p);
        }
    };
    for(auto const &el : sequence) {
        insert(std::make_pair(el.second, 1));
        insert(std::make_pair(el.first, 1));
    }
    return res;
}

unsigned real_size(std::vector<std::pair<unsigned, unsigned>> sequence) {
    unsigned sum(0);
    for(auto const &el : sequence) {
        sum += el.second;
    }
    return sum;
}

int main() {
    auto rep = [&](int const &pos) -> unsigned {
        for(auto i = 1;;++i) {
            if(pos + i >= INITIAL_INPUT.size() || INITIAL_INPUT.at(pos+i) != INITIAL_INPUT.at(pos)) 
                return i;
        }
    };

    std::vector<std::pair<unsigned, unsigned>> sequence;
    for(auto i(0); i < INITIAL_INPUT.size();) {
        sequence.push_back(std::make_pair(INITIAL_INPUT.at(i)-48, rep(i)));
        i += rep(i);
    }

    for(auto i = 0; i < 40; ++i) {
        sequence = look_and_say(sequence);
    }
    std::cout << "Silver: " << real_size(sequence) << '\n';

    for(auto i = 0; i < 10; ++i) {
        sequence = look_and_say(sequence);
    }
    std::cout << "Gold: " << real_size(sequence) << '\n';
}