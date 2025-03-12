#ifndef EXPERTSYS_HPP
#define EXPERTSYS_HPP

#include <unordered_map>
#include <unordered_set>

#include "Letter.hpp"
#include "Rule.hpp"

class ExpertSys
{
private:
    std::unordered_map<char, Letter> letters;
    std::unordered_map<std::string, Rule> rules;

    std::vector<char> querries;

    void initLetterAssociationWithRules();

    std::vector<std::string> getAssociateRulesName(char letter);

public:
    ExpertSys(std::unordered_map<char, Letter> letters, std::unordered_map<std::string, Rule> rules, std::vector<char> querries);
    ~ExpertSys();

    void solveForLetter(char &letter, std::unordered_set<std::string> &rulesCommingFrom);
};


#endif