#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <regex>
#include <sstream>

std::pair<unsigned, unsigned> distance(std::map<std::string, std::set<std::pair<unsigned, std::string>>> const connections, 
    bool longest, unsigned const &sum=0, std::vector<std::string> visited={}, std::string const &current = "", unsigned vis=0) {
    
    unsigned shortest(0);
    if(sum == 0) {
        for(auto const &el : connections) {
            for(auto const &sel : el.second) {
                std::vector<std::string> tmpv = {el.first};
                auto tmp = distance(connections, longest, sel.first, tmpv, sel.second, 1);
                if((longest ? shortest < tmp.first : shortest > tmp.first || shortest == 0) && tmp.second == connections.size()) {
                    shortest = tmp.first;
                }
            }
        }
    } else {
        visited.push_back(current);
        for(auto const &sel : connections.at(current)) {
            if(std::count(visited.begin(), visited.end(), sel.second) == 0) {
                auto tmp = distance(connections, longest, sum+sel.first, visited, sel.second, visited.size());
                if((longest ? shortest < tmp.first : shortest > tmp.first || shortest == 0) && connections.size() == tmp.second) {
                    shortest = tmp.first;
                    vis = connections.size();
                }
            }
        }
    }
    return std::make_pair(shortest == 0 ? sum : shortest, visited.size() == connections.size() ? visited.size() : vis);
};

int main() {
    std::map<std::string, std::set<std::pair<unsigned, std::string>>> connections;


    auto insert = [&](std::smatch sm) {
        std::stringstream ss;
        ss << sm[3].str();
        unsigned dist;
        ss >> dist;
        if(connections.count(sm[1].str()) == 0) {
            std::set<std::pair<unsigned, std::string>> tmp;
            connections.insert(std::make_pair(sm[1].str(), tmp));
        }
        if(connections.count(sm[2].str()) == 0) {
            std::set<std::pair<unsigned, std::string>> tmp;
            connections.insert(std::make_pair(sm[2].str(), tmp));
        }
        connections.at(sm[1].str()).insert(std::make_pair(dist, sm[2].str()));
        connections.at(sm[2].str()).insert(std::make_pair(dist, sm[1].str()));
    };

    std::fstream input_file("input.txt", std::ios::in);
    std::string line;

    std::regex reg("(\\w+) to (\\w+) = (\\d+)");

    while(std::getline(input_file, line)) {
        std::smatch sm;
        std::regex_match(line, sm, reg);
        insert(sm);
    }
    input_file.close();

    std::cout << "Silver: " << distance(connections, false).first << '\n';
    std::cout << "Gold: " << distance(connections, true).first << '\n';
}