#include "ExpertSys.hpp"

ExpertSys::ExpertSys(std::unordered_set<Letter, HashLetter> letters, std::unordered_set<Rule, HashRule> rules)
{
    this->letters = letters;
    this->rules = rules;
}

ExpertSys::~ExpertSys(){}