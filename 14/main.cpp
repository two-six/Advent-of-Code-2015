#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <utility>

const unsigned TIME_LIMIT(2503);

typedef struct Data {
    std::pair<unsigned, unsigned> speed;
    unsigned rest;
} Data;

std::map<std::string, Data> read_from_file(std::string const &file_name) {
    std::map<std::string, Data> res;
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    std::regex reg("(\\w+) can fly (\\d+) km/s for (\\d+)"
                    " seconds, but then must rest for (\\d+) seconds.");
    while(std::getline(input_file, line)) {
        std::smatch sm;
        std::regex_match(line, sm, reg); 
        Data tmp;
        tmp.speed = std::make_pair(
            std::stoi(sm[2].str()), std::stoi(sm[3].str()));
        tmp.rest = std::stoi(sm[4].str());
        res.insert(std::make_pair(sm[1].str(), tmp));
    }
    input_file.close();
    return res;
}

unsigned silver(std::map<std::string, Data> const &reindeers, unsigned tl) {
    unsigned m(0);
    for(auto const &el : reindeers) {
        unsigned sum = (tl/(el.second.speed.second+el.second.rest))
            *(el.second.speed.first*el.second.speed.second);
        unsigned left_time = tl%(el.second.speed.second+el.second.rest);
        if(left_time >= el.second.speed.second) 
            sum += el.second.speed.first * el.second.speed.second;
        else 
            sum += el.second.speed.first * left_time;

        if(m < sum)
            m = sum;
    }
    return m;
}

unsigned gold(std::map<std::string, Data> const &reindeers, unsigned tl) {
    auto count = [&](unsigned t) -> std::pair<std::vector<std::string>, unsigned> {
        unsigned m(0);
        std::string reindeer;
        auto reindeer_speed = [&](std::string s) -> unsigned {
            unsigned sum = (t/(reindeers.at(s).speed.second+reindeers.at(s).rest))
                *(reindeers.at(s).speed.first*reindeers.at(s).speed.second);
            unsigned left_time = t%(reindeers.at(s).speed.second+reindeers.at(s).rest);
            if(left_time >= reindeers.at(s).speed.second) 
                sum += reindeers.at(s).speed.first * reindeers.at(s).speed.second;
            else
                sum += reindeers.at(s).speed.first * left_time;
            return sum;
        };
        for(auto const &el : reindeers) {
            auto tmp = reindeer_speed(el.first);
            if(m < tmp)
                m = tmp;
        }
        std::vector<std::string> res;

        for(auto const &el : reindeers) {
            auto tmp = reindeer_speed(el.first);
            if(m == tmp) {
                res.push_back(el.first);
            }
        }
        return std::make_pair(res, m);
    };
    std::map<std::string, unsigned> points;
    for(auto const &el : reindeers) {
        points.insert(std::make_pair(el.first, 0));
    }
    std::string reindeer;
    for(auto i(1); i <= tl; i++) {
        unsigned m(0);
        auto res = count(i);
        for(auto const &el : res.first) {
            points.at(el)++;
        }
    }
    unsigned m(0);
    for(auto const &el : points) {
        if(m < el.second)
            m = el.second;
    }
    return m;
}

int main() {
    auto reindeers = read_from_file("input.txt");
    std::cout << "Silver: " << silver(reindeers, TIME_LIMIT) << '\n';
    std::cout << "Gold: " << gold(reindeers, TIME_LIMIT) << '\n';
}