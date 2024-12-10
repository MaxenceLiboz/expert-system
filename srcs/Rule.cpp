#include "Rule.hpp"

Rule::Rule(std::string rule) {
    this->value = rule;

    this->verifyRule();
}

Rule::~Rule() {}

void Rule::verifyRule() {
    std::size_t index = 0;
    char        letter;
    std::string op;
    bool        isRightSide = false;

    this->value.erase(std::remove_if(this->value.begin(), this->value.end(), isspace), this->value.end());

    while (index < this->value.size()) {
        verifyNextLetter(index, letter);
        if (isRightSide) {
            this->letters.push_back(letter);
        }
        verifyNextOperator(index, isRightSide);
    }
}

void Rule::verifyNextLetter(std::size_t &index, char &c) {
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

void Rule::verifyNextOperator(std::size_t &index, bool &isRightSide) {
    std::size_t start = index;
    while (index < this->value.size() && !isalpha(this->value[index]) && this->value[index] != '(' && this->value[index] != ')') {
        index++;
    }
    std::string op = this->value.substr(start, index - start);
    if (!Operator::isOperator(op) && op != ""){
        throw std::invalid_argument("Error occured in this->value: " + this->value + ". Operator \'" + op + "\' but it is not valid.");
    }
    if (Operator::toString(Operator::IMPLIES) == op || Operator::toString(Operator::IF_ONLY_IF) == op) {
        if (isRightSide == true) {
            throw std::invalid_argument("Cannot implies or if and only if twice in a rule.");
        }
        isRightSide = true;
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

bool Rule::isLetter(const std::string &expr, std::size_t &index, LetterValue &letterValue, std::unordered_map<char, Letter> &letters) {
    bool isNegative = false;
    if (expr[index] == '!') {
        isNegative = true;
        index++;
    }

    if (isalpha(expr[index])) {
        std::unordered_map<char, Letter>::iterator it = letters.find(expr[index]);
        if (it != letters.end()) {
            letterValue = isNegative ? it->second.getInverseValue() : it->second.getValue();
            return true;
        } else {
            throw std::invalid_argument("Error occured, letter " + std::to_string(expr[index]) + " is undefined");
        }
    }
    return false;
}

LetterValue Rule::solveForLetter(const std::string &expr, std::unordered_map<char, Letter> &letters) {
    // Do the calculation
    LetterValue value = UNDEFINED;
    std::stack<LetterValue> values;

    Operator op;
    std::stack<Operator> operators;

    LetterValue valueA = UNDEFINED;
    LetterValue valueB = UNDEFINED;

    for (std::size_t index = 0; index < expr.size(); index++) {
        if (Rule::isLetter(expr, index, value, letters)) {
            values.push(value);
        } else if (expr[index] == '(') {
            std::size_t start = index + 1;
            while (index < expr.size() && expr[index] != ')') {
                index++;
            }
            std::string subExpretion = expr.substr(start, index - start);
            values.push(Rule::solveForLetter(subExpretion, letters));
        } else if (Operator::findIsOperator(expr, index, op)) {
            operators.push(op);
        }

        if (!operators.empty() && values.size() == 2) {
            valueB = values.top();
            values.pop();
            valueA = values.top();
            values.pop();
            values.push(Operator::eval(valueA, valueB, op));
        }
    }
    return values.top();
}
