#include <iostream>
#include "md5.h"
#include <sstream>
#include <utility>
 
std::pair<unsigned, unsigned> solution(std::string const &base) {
    unsigned sil(0);
    unsigned gold(0);
    auto connect = [&](unsigned const &n) -> std::string {
        std::stringstream ss;
        ss << n;
        return base+ss.str();
    };
    while(md5(connect(sil)).substr(0, 5) != "00000") 
        sil++;
    while(md5(connect(gold)).substr(0, 6) != "000000")
        gold++;
    return std::make_pair(sil, gold);
}
 
int main() {
    auto sol = solution("ckczppom");
    std::cout << "Silver: " << sol.first << '\n';
    std::cout << "Gold: " << sol.second << '\n';
}