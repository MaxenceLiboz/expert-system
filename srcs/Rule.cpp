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
        // if (isRightSide) {
        //     this->letters.push_back(letter);
        // }
        this->letters.push_back(letter);
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

void Rule::solve(const std::string &expr, std::unordered_map<char, Letter> &letters, char letterToFind) {
    std::size_t index = 0;
    Operator op;
    bool    isLeftSide = false;

    // Get the iterator of the letter
    std::unordered_map<char, Letter>::iterator itLetterToFind = letters.find(letterToFind);
    if (itLetterToFind == letters.end()) {
        throw std::runtime_error("The letter to find " + std::to_string(letterToFind) + " is not found in our letters map.");
    }

    // Decompose the expr in two to get the left side and the right side.
    while (index < expr.size() && op.getValue() != Operator::IMPLIES && op.getValue() != Operator::IF_ONLY_IF) {
        index++;
        Operator::findIsOperator(expr, index, op);
    }
    std::string leftSideExpr = expr.substr(0, index - 1);
    while (index < expr.size() && expr[index] != '>') {
        index++;
    }
    std::string rightSideExpr = expr.substr(index + 1, expr.size() - index + 1);

    // Save the old value of the letter
    LetterValue tmpValue  = itLetterToFind->second.getValue();

    // Check if the letter to find is in the right side of the left side
    if (leftSideExpr.find(letterToFind) != std::string::npos) {
        isLeftSide = true;
    }
    // Value for the side without the letter to find
    LetterValue valueWithoutLetter = Rule::solveExpr(isLeftSide ? rightSideExpr : leftSideExpr, letters);
    // Try the solution with letterToFind = TRUE
    itLetterToFind->second.setValue(TRUE);
    LetterValue valueWithLetterTrue = Rule::solveExpr(isLeftSide ? leftSideExpr : rightSideExpr, letters);
    // Try the solution with letterToFind = FALSE
    itLetterToFind->second.setValue(FALSE);
    LetterValue valueWithLetterFalse = Rule::solveExpr(isLeftSide ? leftSideExpr : rightSideExpr, letters);
    // Value that the right side need to have
    LetterValue valueNeededWithLetter = Operator::eval(valueWithoutLetter, isLeftSide ? FALSE : TRUE, op);

    if (valueNeededWithLetter == UNDEFINED || (valueNeededWithLetter == valueWithLetterTrue && valueNeededWithLetter == valueWithLetterFalse)) {
        itLetterToFind->second.setValue(UNDEFINED);
    } else if (valueNeededWithLetter == valueWithLetterTrue && valueNeededWithLetter != valueWithLetterFalse) {
        itLetterToFind->second.setValue(TRUE);
    } else if (valueNeededWithLetter != valueWithLetterTrue && valueNeededWithLetter == valueWithLetterFalse) {
        itLetterToFind->second.setValue(FALSE);
    } else {
        throw std::runtime_error("The value of the right side is not the same as the needed one with FALSE or TRUE value.");
    }
    if ((itLetterToFind->second.getValueFrom() == RULES || itLetterToFind->second.getValueFrom() == INIT_FACTS) && itLetterToFind->second.getValue() != tmpValue) {
        throw std::invalid_argument("Rule(s) does not give the same results given by other or initial fact.");
    }
    itLetterToFind->second.setValueFrom(RULES);
}

LetterValue Rule::solveExpr(const std::string &expr, std::unordered_map<char, Letter> &letters) {
    // Do the calculation
    LetterValue value = UNDEFINED;
    std::stack<LetterValue> values;

    Operator op;
    std::stack<Operator> operators;

    LetterValue valueA = UNDEFINED;
    LetterValue valueB = UNDEFINED;

    for (std::size_t index = 0; index < expr.size(); index++) {
        if (Letter::findIsLetter(expr, index, value, letters)) {
            values.push(value);
        } else if (expr[index] == '(') {
            std::size_t start = index + 1;
            while (index < expr.size() && expr[index] != ')') {
                index++;
            }
            std::string subExpretion = expr.substr(start, index - start);
            values.push(Rule::solveExpr(subExpretion, letters));
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
