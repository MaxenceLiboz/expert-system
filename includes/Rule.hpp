#ifndef RULE_HPP
#define RULE_HPP

#include <string>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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

    static LetterValue  solveExpr(const std::string &expr, std::unordered_map<char, Letter> &letters);

public:
    Rule(std::string rule);
    ~Rule();

    std::string                 getValue() const;
    std::vector<char>           getLettersNeeded() const;
    std::unordered_set<char>   getLettersDefault(std::unordered_map<char, Letter> &expertSysletters) const;

    void                        setValue(std::string value);

    bool                        operator==(const Rule &rule) const;

    static void                 solve(const std::string &expr, std::unordered_map<char, Letter> &letters, char letterToFind);
};

struct HashRule
{
    std::size_t operator()(const Rule &rule) const;
};




#endif