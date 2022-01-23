#include <iostream>

std::string const PASS = "vzbxkghb";

bool valid_pass(std::string const &pass) {
    auto first_req = [&]() -> bool {
        for(auto i = 0; i < pass.size()-2; ++i) {
            if(pass.at(i)+1 == pass.at(i+1) && pass.at(i)+2 == pass.at(i+2))
                return true;
        }
        return false;
    };

    auto second_req = [&]() -> bool {
        for(auto const &c : pass) {
            if(c == 'i' || c == 'o' || c == 'l')
                return false;
        }
        return true;
    };

    auto third_req = [&]() -> bool {
        unsigned pairs(0);
        for(auto i = 0; i < pass.size()-1; ++i) {
            if(pass.at(i) == pass.at(i+1)) {
                pairs++;
                i++;
            }
        }
        return pairs >= 2;
    };

    return first_req() && second_req() && third_req();
} 

void increment(std::string &pass, unsigned pos=PASS.size()-1) {
    for(auto &c : pass) {
        if(c == 'i' || c == 'o' || c == 'l') 
            c++;
    }
    if(pass.at(pos) == 'z') {
        pass.at(pos) = 'a';
        increment(pass, pos-1);
    } else {
        pass.at(pos)++;
    }
}

int main() {
    std::string pass = PASS;
    while(!valid_pass(pass)) {
        increment(pass);
    }
    std::cout << "Silver: " << pass << '\n';
    do {
        increment(pass);
    } while(!valid_pass(pass));
    std::cout << "Gold: " << pass << '\n';
}