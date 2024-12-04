#ifndef EXPERTSYS_HPP
#define EXPERTSYS_HPP

#include <unordered_set>

#include "Letter.hpp"
#include "Rule.hpp"

class ExpertSys
{
private:
    std::unordered_set<Letter, HashLetter> letters;
    std::unordered_set<Rule, HashRule> rules;

public:
    ExpertSys(std::unordered_set<Letter, HashLetter> letters, std::unordered_set<Rule, HashRule> rules);
    ~ExpertSys();
};


#endif