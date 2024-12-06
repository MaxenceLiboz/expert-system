#ifndef RULE_HPP
#define RULE_HPP

#include <string>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

#include "Letter.hpp"
#include "Sign.hpp"


class Rule
{
private:
    std::string         value;
    std::vector<char>   letters;

    void verifyRule();
    void verifyNextLetter(char &c, std::size_t &index);
    void verifyNextSign(std::string &sign, std::size_t &index);
    
public:
    Rule(std::string rule);
    ~Rule();

    std::string         getValue() const;
    std::vector<char>   getLettersNeeded() const;

    void                setValue(std::string value);

    bool                operator==(const Rule &rule) const;

    void                solveForLetter(std::unordered_map<char, Letter> &letters, char querry);
};

struct HashRule
{
    std::size_t operator()(const Rule &rule) const;
};




#endif