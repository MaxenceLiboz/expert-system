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
        verifyNextLetter(letter, index);
        this->letters.push_back(letter);
        verifyNextSign(sign, index);
    }
}

void Rule::verifyNextLetter(char &c, std::size_t &index) {
    if (this->value[index] == '(' || this->value[index] == '!') {
        index++;
    }
    if (!isalpha(this->value[index])){
        throw std::invalid_argument("Error occured in this->value: " + this->value + ". Char \'" + this->value[index] + "\' where given at index " + std::to_string(index) + " instead of letter");
    }
    c = this->value[index++];
    if (this->value[index] == ')') {
        index++;
    }
}

void Rule::verifyNextSign(std::string &sign, std::size_t &index) {
    std::size_t start = index;
    while (index < this->value.size() && !isalpha(this->value[index])) {
        index++;
    }
    sign = this->value.substr(start, index - start);
    if (!Sign::isSign(sign) && sign != ""){
        throw std::invalid_argument("Error occured in this->value: " + this->value + ". Sign \'" + sign + "\' but it is not valid.");
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
