
#include "Sign.hpp"

Sign::Sign(Enum sign) : value(sign) {}
Sign::~Sign(){}

std::string Sign::toString() const
{
    switch (this->value) {
        case AND: return "+";
        case OR: return "|";
        case NOT: return "!";
        case XOR: return "^";
        case IMPLIES: return "=>";
        case IF_ONLY_IF: return "<=>";
        default: throw std::invalid_argument("The sign is not supported"); 
    }
}