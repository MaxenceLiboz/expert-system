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
    letters.insert(std::make_pair('C', Letter('C', FALSE, DEFAULT)));
    letters.insert(std::make_pair('D', Letter('D', FALSE, DEFAULT)));
    letters.insert(std::make_pair('E', Letter('E', FALSE, DEFAULT)));
    letters.insert(std::make_pair('F', Letter('F', FALSE, DEFAULT)));
    letters.insert(std::make_pair('V', Letter('V', FALSE, DEFAULT)));
    letters.insert(std::make_pair('X', Letter('X', FALSE, DEFAULT)));

    std::unordered_map<std::string, Rule> rules;
    Rule rule = Rule("E + F => !V"); // F = FALSE / V = TRUE
    Rule rule1 = Rule("C => E"); // E = TRUE
    Rule rule2 = Rule("A + B + C => D"); // D = TRUE
    Rule rule3 = Rule("A | B => C"); // C = TRUE
    Rule rule4 = Rule("C | D => X | V"); // V = TRUE 
    std::vector<char> querries = std::vector<char>{'V', 'X'};
    rules.insert(std::make_pair(rule.getValue(), rule));
    rules.insert(std::make_pair(rule1.getValue(), rule1));
    rules.insert(std::make_pair(rule2.getValue(), rule2));
    rules.insert(std::make_pair(rule3.getValue(), rule3));
    rules.insert(std::make_pair(rule4.getValue(), rule4));


    // Rule rule = Rule("A + B => C");  
    // Rule rule1 = Rule("A + !B => C");  
    // rules.insert(std::make_pair(rule.getValue(), rule));
    // rules.insert(std::make_pair(rule1.getValue(), rule1));
    // std::vector<char> querries = std::vector<char>{'C'};

    // Rule rule = Rule("A + B => C");  
    // Rule rule1 = Rule("A | C => D");  
    // Rule rule2 = Rule("C + D => E");
    // rules.insert(std::make_pair(rule.getValue(), rule));
    // rules.insert(std::make_pair(rule1.getValue(), rule1));
    // rules.insert(std::make_pair(rule2.getValue(), rule2));
    // std::vector<char> querries = std::vector<char>{'E'};


    ExpertSys expertSys(letters, rules, querries);

    return 0;

}