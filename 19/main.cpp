#include <iostream>
#include <fstream>
#include <set>
#include <regex>
#include <utility>
#include <vector>
#include <map>

std::pair<std::map<std::string, std::vector<std::string>>, std::string>
read_from_file(std::string const &file_name) {
    std::map<std::string, std::vector<std::string>> res1;
    std::string res2;
    std::fstream input_file(file_name, std::ios::in);
    std::string line;
    std::regex reg("(\\w+) => (\\w+)");
    while(std::getline(input_file, line)) {
        std::smatch sm;
        if(!std::regex_match(line, sm, reg)) {
            if(line.size() != 0)
                res2 = line;
        } else {
            if(res1.count(sm[1].str()) == 0) {
                std::vector<std::string> tmp;
                res1.insert(std::make_pair(sm[1].str(), tmp));
            }
            res1.at(sm[1].str()).push_back(sm[2].str());
        }
    }
    return std::make_pair(res1, res2);
}

unsigned silver
(std::map<std::string, std::vector<std::string>> rep, std::string const &line) {
    std::set<std::string> res;
    for(auto const &el : rep) {
        for(auto const &sel : el.second) {
            std::vector<std::string> tmp;
            auto last(-1);
            while(line.find(el.first, last+1) != std::string::npos) {
                std::string tmps(line);
                last = line.find(el.first, last+1);
                tmps.replace(last, el.first.size(), sel);
                tmp.push_back(tmps);
            }
            for(auto const &el : tmp) 
                res.insert(el);
        }
    }
    return res.size();
}

int main() {
    auto data = read_from_file("input.txt");
    std::cout << "Silver: " << silver(data.first, data.second) << '\n';
    
}