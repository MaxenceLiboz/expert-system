#include "ExpertSys.hpp"

ExpertSys::ExpertSys(std::unordered_map<char, Letter> letters, std::unordered_map<std::string, Rule> rules, std::vector<char> querries)
{
    this->letters = letters;
    this->rules = rules;
    this->querries = querries;

    initLetterAssociationWithRules();

    for (char querry : this->querries) {
        std::unordered_set<std::string> rulesCommingFrom;
        solveForLetter(querry, rulesCommingFrom);
        std::unordered_map<char, Letter>::iterator it = this->letters.find(querry);
        std::cout << it->second.printValue() << std::endl;

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
                throw std::invalid_argument("Problem in rule " + rule.first +" with the letter " + std::string(1, letter));
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

void ExpertSys::solveForLetter(char &letter, std::unordered_set<std::string> &rulesCommingFrom) {
    std::unordered_map<char, Letter>::iterator letterIt = this->letters.find(letter);
    if (letterIt == this->letters.end()) {
        throw std::invalid_argument("Letter to solve is not found in our map.");
    }

    for (std::string associateRule : letterIt->second.getAssociateRulesValue()) {
        if (rulesCommingFrom.find(associateRule) != rulesCommingFrom.end()) {
            continue;
        }
        std::unordered_map<std::string, Rule>::iterator ruleIt = this->rules.find(associateRule);
        std::unordered_set<char> lettersDefault = ruleIt->second.getLettersDefault(this->letters);
        lettersDefault.erase(letter);
        if (!lettersDefault.empty()) {
            rulesCommingFrom.insert(associateRule);
            for (char letter : lettersDefault) {
                solveForLetter(letter, rulesCommingFrom);
            }
        } 
        lettersDefault = ruleIt->second.getLettersDefault(this->letters);
        ruleIt->second.solve(ruleIt->first, this->letters, lettersDefault.size() == 1 ? *lettersDefault.begin() : letterIt->first);
        rulesCommingFrom.erase(associateRule);
    }
}