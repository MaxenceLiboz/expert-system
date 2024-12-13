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

    std::unordered_map<std::string, Rule> rules;
    Rule rule = Rule("E + F => !V"); // Pour F FALSE = V = UNDEFINED;  
    Rule rule = Rule("C => E"); // E = TRUE
    Rule rule = Rule("A + B + C => D"); // D = TRUE
    Rule rule = Rule("A | B => C"); // C = TRUE
    Rule rule = Rule("C | D => X | V"); // Pour X = FALSE = V = TRUE ; X = UNDEFINED
    rules.insert(std::make_pair(rule.getValue(), rule));

    std::vector<char> querries = std::vector<char>{'V', 'X'};

    ExpertSys expertSys(letters, rules, querries);

    return 0;

}