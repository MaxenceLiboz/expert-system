
#include "Operator.hpp"

Operator::Operator() {}
Operator::~Operator() {}

void Operator::setValue(Enum value) {
    this->value = value;
}

Operator::Enum Operator::getValue() const {
    return this->value;
}

std::string Operator::toString(Enum sign)
{
    switch (sign) {
        case AND: return "+";
        case OR: return "|";
        case XOR: return "^";
        case IMPLIES: return "=>";
        case IF_ONLY_IF: return "<=>";
        default: throw std::invalid_argument("The sign is not supported"); 
    }
}

bool Operator::isOperator(std::string op) {

    if (Operator::toString(Operator::AND) == op || Operator::toString(Operator::OR) == op
        || Operator::toString(Operator::XOR) == op ||Operator::toString(Operator::IMPLIES) == op 
        || Operator::toString(Operator::IF_ONLY_IF) == op) {
        return true;
    }
    return false;
}

bool Operator::findIsOperator(const std::string &expr, std::size_t &index, Operator &op) {
    std::size_t start = index;
    if (expr[index] == '=') {
        index++;
    } else if (expr[index] == '<') {
        index += 2;
    }

    std::string opString = expr.substr(start, index + 1 - start);
    if (Operator::toString(Operator::AND) == opString) {
        op.setValue(AND); 
    } else if (Operator::toString(Operator::OR) == opString) {
        op.setValue(OR);
    } else if (Operator::toString(Operator::XOR) == opString) {
        op.setValue(XOR);
    } else if (Operator::toString(Operator::IMPLIES) == opString) {
        op.setValue(IMPLIES);
    } else if (Operator::toString(Operator::IF_ONLY_IF) == opString) {
        op.setValue(IF_ONLY_IF);
    } else {
        return false;
    }
    return true;
}

LetterValue Operator::andOp(LetterValue valueA, LetterValue valueB) {
    if (valueA == UNDEFINED || valueB == UNDEFINED) {
        return UNDEFINED;
    } else if (valueA == TRUE && valueB == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

LetterValue Operator::orOp(LetterValue valueA, LetterValue valueB) {
    if (valueA == TRUE || valueB == TRUE) {
        return TRUE;
    } else if (valueA == UNDEFINED || valueB == UNDEFINED) {
        return UNDEFINED;
    } else {
        return FALSE;
    }
}

LetterValue Operator::xorOp(LetterValue valueA, LetterValue valueB) {
    if (valueA == UNDEFINED || valueB == UNDEFINED) {
        return UNDEFINED;
    } else if ((valueA == TRUE && valueB == TRUE) || (valueA == FALSE && valueB == FALSE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// The result of the implies is always true
LetterValue Operator::ifOnlyIfOp(LetterValue value) {
    if (value == TRUE) {
        return TRUE;
    } else if (value == FALSE) {
        return FALSE;
    } else {
        return UNDEFINED;
    }    
}

// The result of the implies is always true
LetterValue Operator::impliesOp(LetterValue value, bool isLookingForB) {
    if (isLookingForB) {
        if (value == TRUE) {
            return TRUE;
        } else {
            return UNDEFINED;
        }
    } else {
        if (value == FALSE) {
            return FALSE;
        } else {
            return UNDEFINED;
        }
    }
}

LetterValue Operator::eval(LetterValue valueA, LetterValue valueB, Operator op) {
    switch (op.getValue())
    {
        case Operator::AND:
            return Operator::andOp(valueA, valueB);
        case Operator::OR:
            return Operator::orOp(valueA, valueB);
        case Operator::XOR:
            return Operator::xorOp(valueA, valueB);
        case Operator::IF_ONLY_IF:
            return Operator::ifOnlyIfOp(valueA);
        case Operator::IMPLIES:
            return Operator::impliesOp(valueA, valueB);
        default:
            return UNDEFINED;
    }   
}

