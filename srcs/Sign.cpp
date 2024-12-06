
#include "Sign.hpp"


std::string Sign::toString(Enum sign)
{
    switch (sign) {
        case AND: return "+";
        case OR: return "|";
        case NOT: return "!";
        case XOR: return "^";
        case IMPLIES: return "=>";
        case IF_ONLY_IF: return "<=>";
        default: throw std::invalid_argument("The sign is not supported"); 
    }
}

bool Sign::isSign(std::string sign) {

    if (Sign::toString(Sign::AND) == sign || Sign::toString(Sign::OR) == sign
        || Sign::toString(Sign::NOT) == sign || Sign::toString(Sign::XOR) == sign
        || Sign::toString(Sign::IMPLIES) == sign || Sign::toString(Sign::IF_ONLY_IF) == sign) {
        return true;
    }
    return false;
}