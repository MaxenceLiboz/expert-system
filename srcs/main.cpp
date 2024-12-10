#include "main.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello world" << std::endl;
    std::cout << "Number of args: " <<  (argc - 1) << std::endl;
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::unordered_map<char, Letter> letters;
    letters.insert(std::make_pair('A', Letter('A', TRUE, INIT_FACTS)));
    letters.insert(std::make_pair('B', Letter('B', TRUE, INIT_FACTS)));
    letters.insert(std::make_pair('C', Letter('C')));
    letters.insert(std::make_pair('D', Letter('D')));

    std::unordered_map<std::string, Rule> rules;
    rules.insert(std::make_pair("A | (B + C) => D + C", Rule("A | (B + C) => D")));

    std::vector<char> querries = std::vector<char>{'C'};

    ExpertSys expertSys(letters, rules, querries);

    return 0;

}