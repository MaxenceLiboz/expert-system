#ifndef RULE_HPP
#define RULE_HPP

#include <string>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <stack>

#include "Letter.hpp"
#include "Operator.hpp"


class Rule
{
private:
    std::string         value;
    std::vector<char>   letters;

    void        verifyRule();
    void        verifyNextLetter(std::size_t &index, char &c);
    void        verifyNextOperator(std::size_t &index, bool &isRightSide);

    static bool isLetter(const std::string &expr, std::size_t &index, LetterValue &letterValue, std::unordered_map<char, Letter> &letters);
    static bool isOperator(const std::string &expr, std::size_t &index, Operator &op);

public:
    Rule(std::string rule);
    ~Rule();

    std::string         getValue() const;
    std::vector<char>   getLettersNeeded() const;

    void                setValue(std::string value);

    bool                operator==(const Rule &rule) const;

    static LetterValue  solveForLetter(const std::string &expr, std::unordered_map<char, Letter> &letters);
};

struct HashRule
{
    std::size_t operator()(const Rule &rule) const;
};




#endif