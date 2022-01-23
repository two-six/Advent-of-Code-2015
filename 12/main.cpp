#include <iostream>
#include <fstream>
#include <vector>

unsigned count(std::string const &con, bool gold=false) {
    auto num_len = [&](unsigned const &pos) -> unsigned {
        unsigned i(1);
        for(; i+pos < con.size(); ++i) {
            if(!std::isdigit(con.at(pos+i)))
                return i;
        } 
        return i;
    };

    int sum(0);
    if(gold) {
        auto num_to_close = [&](unsigned const &pos, bool curly=true) -> unsigned {
            int tmp(0);
            unsigned i(1);
            for(; con.at(pos+i) != (curly ? '}' : ']') || tmp > 0; ++i) {
                if(con.at(pos+i) == (curly ? '{' : '[')) {
                    tmp++;
                } else if(con.at(pos+i) == (curly ? '}' : ']')) {
                    tmp--;
                    if(tmp < 0)
                        return i;
                }
            }
            return i;
        };

        auto actually_contains_red = [&](unsigned const &pos) -> bool {
            std::string tmp="";
            unsigned limit = num_to_close(pos);
            for(auto i = 1; i < limit; ++i) {
                if(con.at(pos+i) == '{' || con.at(pos+i) == '[') {
                    i += num_to_close(pos+i, con.at(pos+i) == '{');
                } else {
                    tmp += con.at(pos+i);
                }
            }
            return (tmp.find("\"red\"") != std::string::npos);
        };

        std::string res = "";
        for(auto i = 0; i < con.size(); ++i) {
            if(con.at(i) == '{') {
                if(actually_contains_red(i)) {
                    i += num_to_close(i);
                    res += " ";
                }  else {
                    res += con.at(i);
                }
            } else {
                res += con.at(i);
            }
        }
        return count(res);
    }
    for(auto i = 0; i < con.size(); ++i) {
        if(con.at(i) == '-') {
            sum -= std::stoi(con.substr(i+1, num_len(i+1))); 
            i += num_len(i+1);
        } else if(std::isdigit(con.at(i))) {
            sum += std::stoi(con.substr(i, num_len(i)));
            i += num_len(i);
        }
    }
    return sum;
}


int main() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string content;
    input_file >> content;
    input_file.close();
    std::cout << "Silver: " << count(content) << '\n';
    std::cout << "Gold: " << count(content, true) << '\n';
}