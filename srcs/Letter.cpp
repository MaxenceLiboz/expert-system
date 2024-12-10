#include "Letter.hpp"

Letter::Letter(char letter) {
    this->letter = letter;
    this->value = FALSE;
    this->valueFrom = DEFAULT;
}

Letter::Letter(char letter, LetterValue value, LetterValueFrom valueFrom) {
    this->letter = letter;
    this->value = value;
    this->valueFrom = valueFrom;
}

Letter::~Letter() {}


char Letter::getLetter() const {
    return this->letter;
}

LetterValue Letter::getValue() const {
    return this->value;
}

LetterValue Letter::getInverseValue() const {
    switch (this->value)
    {
        case TRUE:
            return FALSE;
        case FALSE:
            return TRUE;
        default:
            return UNDEFINED;
    }
}

LetterValueFrom Letter::getValueFrom() const {
    return this->valueFrom;
}

void Letter::setValue(LetterValue value) {
    this->value = value;
}

void Letter::setValueFrom(LetterValueFrom valueFrom) {
    this->valueFrom = valueFrom;
}

void Letter::addAssociateRuleValue(std::string ruleName) {
    this->associateRulesValue.push_back(ruleName);
}

bool Letter::operator==(const Letter &letter) const {
    return this->letter == letter.getLetter();
}

std::size_t HashLetter::operator()(const Letter &letter) const {
    return letter.getLetter();
}