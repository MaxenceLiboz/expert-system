#include "ExpertSys.hpp"

ExpertSys::ExpertSys(std::unordered_map<char, Letter> letters, std::unordered_map<std::string, Rule> rules, std::vector<char> querries)
{
    this->letters = letters;
    this->rules = rules;
    this->querries = querries;

    initLetterAssociationWithRules();

    std::vector<std::string> rulesToSovle = getAssociateRulesName(querries[0]);
    for (std::string ruleName : rulesToSovle) {
        auto it = this->rules.find(ruleName);
        if (it != this->rules.end()) {
            it->second.solveForLetter(letters, querries[0]);
        } else {
            throw std::invalid_argument("Problem with the rule " + ruleName);
        }
    }
}

ExpertSys::~ExpertSys(){}

void ExpertSys::initLetterAssociationWithRules() {
    for (std::pair<std::string, Rule> rule : this->rules) {
        for (char letter : rule.second.getLettersNeeded()) {
            std::unordered_map<char, Letter>::iterator it = this->letters.find(letter);
            if (it != this->letters.end()) {
                it->second.addAssociateRuleValue(rule.first);
            } else {
                throw std::invalid_argument("Problem with the letter " + std::to_string(letter) + " in rule " + rule.first);
            }
        }
    }
}

std::vector<std::string> ExpertSys::getAssociateRulesName(char letter) {
    std::vector<std::string> rules;
    for (std::pair<std::string, Rule> rule : this->rules) {
        for (char c : rule.second.getLettersNeeded()) {
            if (c == letter) {
                rules.push_back(rule.first);
                break;
            }
        }
    }
    return rules;
}