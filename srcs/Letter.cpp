#include "Letter.hpp"

Letter::Letter(char letter) {
    this->letter = letter;
}

Letter::Letter(char letter, bool value, LetterValueFrom valueFrom) {
    this->letter = letter;
    this->value = value;
    this->valueFrom = valueFrom;
}

Letter::~Letter() {}


char Letter::getLetter() const {
    return this->letter;
}
bool Letter::getValue() const {
    return this->value;
}
LetterValueFrom Letter::getValueFrom() const {
    return this->valueFrom;
}

void Letter::setValue(bool value) {
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