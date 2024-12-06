#include "Rule.hpp"

Rule::Rule(std::string rule) {
    this->value = rule;

    this->verifyRule();
}

Rule::~Rule() {}

void Rule::verifyRule() {
    std::size_t index = 0;
    char        letter;
    std::string sign;

    this->value.erase(std::remove_if(this->value.begin(), this->value.end(), isspace), this->value.end());

    while (index < this->value.size()) {
        readNextLetter(this->value, letter, index);
        this->letters.push_back(letter);
        readNextSign(this->value, sign, index);
    }
}

std::string Rule::getValue() const {
    return this->value;
}

void Rule::setValue(std::string value) {
    this->value = value;
}

std::vector<char>  Rule::getLettersNeeded() const {
    return this->letters;
}

bool Rule::operator==(const Rule &rule) const {
    return this->value == rule.getValue();
}

std::size_t HashRule::operator()(const Rule &rule) const {
    return std::hash<std::string>{}(rule.getValue());
}

void Rule::solveForLetter(std::unordered_map<char, Letter> &letters, char querry) {
    // Do the calculation

    if (querry == 'N') {
        letters.at(0);
    }
}
