#include <iostream>
#include <fstream>

unsigned n_of_chars_in_memory(std::string const &s) {
    unsigned sum(0);
    for(auto i = 1; i < s.size()-1; ++i) {
        sum++;
        if(s.at(i) == '\\') {
            if(s.at(i+1) == 'x') 
                i+=3;
            else 
                i++;
        }
    }
    return sum;
}

unsigned encoded_line(std::string const &s) {
    unsigned sum(6);
    for(auto i = 1; i < s.size()-1; ++i) {
        sum++;
        if(s.at(i) == '\\') 
            sum++;
        else if(s.at(i) == '\"')
            sum++;
    }
    return sum;
}

int main() {
    std::fstream input_file("input.txt", std::ios::in);
    std::string line;

    unsigned raw_sum(0);
    unsigned sum(0);
    unsigned encoded_sum(0);
    while(input_file >> line) {
        raw_sum += line.size();
        sum += n_of_chars_in_memory(line);
        encoded_sum += encoded_line(line);
    }
    std::cout << "Silver: " << raw_sum - sum << '\n';
    std::cout << "Gold: " << encoded_sum - raw_sum << '\n';
}