#include <iostream>
#include <string>
#include <exception>

#include "Letter.hpp"

class Operator {
public:
    enum Enum {
        AND,
        OR,
        NOT,
        XOR,
        IMPLIES,
        IF_ONLY_IF
    };

    Operator();
    ~Operator();

    static std::string  toString(Enum value);
    static bool         isOperator(std::string value);
    static bool         findIsOperator(const std::string &expr, std::size_t &index, Operator &op);

    static LetterValue  andOp(LetterValue valueA, LetterValue valueB);
    static LetterValue  orOp(LetterValue valueA, LetterValue valueB);
    static LetterValue  xorOp(LetterValue valueA, LetterValue valueB);
    static LetterValue  impliesOp(LetterValue valueA, LetterValue valueB, bool isLookingForB);
    static LetterValue  ifOnlyIfOp(LetterValue valueA, LetterValue valueB);
    static LetterValue  eval(LetterValue valueA, LetterValue valueB, Operator op);

    Enum                getValue() const;
    void                setValue(Enum value);

private:
    Enum value;
};