#include <cctype>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>
#include <sstream>

enum e_type {
    SIGNAL,
    SHIFT,
    AND_OR,
    NOT
};

class Board {
    struct Op {
        int type;
        std::vector<std::string> values;
    };

    std::map<std::string, u_int16_t> wires;
    std::map<int, std::vector<std::vector<std::string>>> operations;

public: 
    void insert(const std::smatch sm, const int type) {
        if(type < SIGNAL || type > NOT)
            throw "Invalid type";

        if(operations.count(type) == 0) {
            std::vector<std::vector<std::string>> tmp;
            operations.insert(std::make_pair(type, tmp));
        }
        
        std::vector<std::string> tmp;
        for(auto i = 1; i < sm.size(); ++i) 
            tmp.push_back(sm[i].str());

        operations.at(type).push_back(tmp);
    }

    std::vector<std::vector<std::string>> get_operations(const int &type) {
        if(operations.count(type) == 0) 
            throw "Invalid Element";
        return operations.at(type);
    }

    std::map<std::string, u_int16_t> silver() {
        auto valid = [&](std::vector<std::string> op) -> bool {
            auto exists = [&](std::string const &el) -> bool {
                return wires.count(el) != 0;
            };
            std::stringstream ss;
            switch (op.size()) {
                case 2:
                    if(std::isdigit(op.at(0).at(0))) 
                        return true;
                    return exists(op.at(0));
                    break;
                default:
                    if(op.at(1).substr(1) == "SHIFT") {
                        if(std::isdigit(op.at(0).at(0)))
                            return true;
                        return exists(op.at(0));
                    } else {
                        bool first = std::isdigit(op.at(0).at(0)), second = std::isdigit(op.at(2).at(0));
                        if(first && second)
                            return true;
                        else if(first)
                            return exists(op.at(2));
                        else if(second)
                            return exists(op.at(0));
                        else
                            return exists(op.at(0)) && exists(op.at(2));
                    }
                    break;
            }
            return false;
        };

        auto get_value = [&](std::string v) -> u_int16_t {
            std::stringstream ss;
            if(std::isdigit(v.at(0))) 
                ss << v;
            else 
                ss << wires.at(v);
            u_int16_t val;
            ss >> val;
            return val;
        };

        unsigned total_size = operations.at(SHIFT).size() +
            operations.at(NOT).size() +
            operations.at(SIGNAL).size() +
            operations.at(AND_OR).size();

        while(total_size > 0) {
            total_size = 0;
            for(auto &el : operations) {
                total_size += el.second.size();
                auto content = &el.second;
                unsigned tmp_size = content->size();
                for(auto i = 0; i < tmp_size; ++i) {
                    if(valid(content->at(i))) {
                        u_int16_t v1, v2, v;
                        std::string dest;
                        if(content->at(i).size() == 2) {
                            v = el.first == NOT ? ~get_value(content->at(i).at(0)) : get_value(content->at(i).at(0));
                            dest = content->at(i).at(1);
                        } else {
                            v1 = get_value(content->at(i).at(0));
                            v2 = get_value(content->at(i).at(2));
                            std::string op = content->at(i).at(1);
                            if(op.substr(1) == "SHIFT") 
                                v = op.at(0) == 'R' ? v1 >> v2 : v1 << v2;  
                            else 
                                v = op == "AND" ? v1 & v2 : v1 | v2;
                            dest = content->at(i).at(3);
                        }
                        wires.insert(std::make_pair(dest, v));
                        content->erase(content->begin()+i);
                        i--;
                        tmp_size--;
                    }
                }
            }
        }

        return wires;
    }

    std::map<std::string, u_int16_t> gold(u_int16_t first) {
        wires.insert(std::make_pair("b", first));
        return silver();
    }
};

int main() {
    Board board;
    auto read_from_file = [&] {
        std::fstream input_file("input.txt", std::ios::in);
        std::string line;

        std::regex signal("(\\w+) -> (\\w+)");
        std::regex gate("(\\w+) (\\w+) (\\w+) -> (\\w+)");
        std::regex not_gate("NOT (\\w+) -> (\\w+)");

        auto insert = [&](std::smatch const &sm, int const &type) {
            board.insert(sm, type);
        };
        while(std::getline(input_file, line)) {
            std::smatch sm;
            if(std::regex_match(line, sm, signal)) 
                insert(sm, SIGNAL);
            else if(std::regex_match(line, sm, gate)) 
                insert(sm, (sm[2].str().substr(1) == "SHIFT") ? SHIFT : AND_OR);
            else if(std::regex_match(line, sm, not_gate)) 
                insert(sm, NOT);
        } 
    };

    read_from_file();
    u_int16_t first = board.silver().at("a");
    std::cout << "Silver: " << first << '\n';
    board = Board();
    read_from_file();
    std::cout << "Gold: " << board.gold(first).at("a") << '\n';
}