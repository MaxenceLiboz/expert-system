#include "main.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello world" << std::endl;
    std::cout << "Number of args: " <<  (argc - 1) << std::endl;
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::unordered_set<Letter, HashLetter> letters;
    letters.insert(Letter('A', true, INIT_FACTS));
    letters.insert(Letter('B', true, INIT_FACTS));

    std::unordered_set<Rule, HashRule> rules;
    rules.insert(Rule("A | B => C"));

    ExpertSys expertSys(letters, rules);

    return 0;
}