#include <functional>
#include <iostream>
#include <array>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>

class Board {
    std::array<std::array<int, 1000>, 1000> board;
    typedef struct Data {
        std::string instruction;
        int x1, y1;
        int x2, y2;
    } Data;

    Data extract(std::string line) {
        Data data;
        std::stringstream ss;
        ss << line;
        ss >> line;
        if(line == "toggle") {
            data.instruction = line;
        } else {
            ss >> line;
            if(line == "on")
                data.instruction = "turn on";
            else
                data.instruction = "turn off";
        }
        ss >> data.x1;
        ss.ignore();
        ss >> data.y1;
        ss.ignore(9);
        ss >> data.x2;
        ss.ignore();
        ss >> data.y2;

        return data;
    }

    void silver_action(Data data) {
        std::map<std::string, std::function<void(int, int)>> act;

        act.insert(std::make_pair("toggle", [&](int i, int j) {
            board.at(i).at(j) = board.at(i).at(j) > 0 ? 0 : 1;
        }));
        act.insert(std::make_pair("turn on", [&](int i, int j) {
            board.at(i).at(j) = 1;
        }));
        act.insert(std::make_pair("turn off", [&](int i, int j) {
            board.at(i).at(j) = 0;
        }));

        for(int i = data.x1; i <= data.x2; ++i) {
            for(int j = data.y1; j <= data.y2; ++j) {
                act.at(data.instruction)(i, j);
            }
        }
    }

    void gold_action(Data data) {
        std::map<std::string, std::function<void(int, int)>> act;

        act.insert(std::make_pair("toggle", [&](int i, int j) {
            board.at(i).at(j) += 2;
        }));
        act.insert(std::make_pair("turn on", [&](int i, int j) {
            board.at(i).at(j) += 1;
        }));
        act.insert(std::make_pair("turn off", [&](int i, int j) {
            board.at(i).at(j) -= board.at(i).at(j) == 0 ? 0 : 1;
        }));

        for(int i = data.x1; i <= data.x2; ++i) {
            for(int j = data.y1; j <= data.y2; ++j) {
                act.at(data.instruction)(i, j);
            }
        }
    }

    unsigned count() {
        unsigned sum(0);
        for(auto const &el : board) {
            for(auto const &el_in : el) {
                if(el_in > 0)
                    sum++;
            }
        }
        return sum;
    }

public:

    Board() {
        for(int i = 0; i < 1000; ++i) {
            for(int j = 0; j < 1000; ++j) {
                board.at(i).at(j) = 0;
            }
        }
    }

    unsigned silver() {
        std::fstream input_file("input.txt", std::ios::in);
        std::string line;
        while(std::getline(input_file, line)) {
            silver_action(extract(line));
        }
        input_file.close();
        return count();
    }

    unsigned gold() {
        std::fstream input_file("input.txt", std::ios::in);
        std::string line;
        while(std::getline(input_file, line)) {
            gold_action(extract(line));
        }
        input_file.close();

        auto sum_up = [&]() -> unsigned {
            unsigned sum(0);
            for(auto const &el : board) {
                for(auto const &el_in : el) {
                    sum += el_in;
                }
            }
            return sum;
        };

        return sum_up();
    }
};

int main() {
    Board board;
    std::cout << "Silver: " << board.silver() << '\n';
    board = Board();
    std::cout << "Gold: " << board.gold() << '\n';
}