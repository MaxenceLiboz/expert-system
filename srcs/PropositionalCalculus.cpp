#include "PropositionalCalculus.hpp"

PropositionalCalculus::PropositionalCalculus(Letter &letterA, Letter &letterB, Sign sign) : letterA(letterA), letterB(letterB), sign(sign)
{
}

PropositionalCalculus::~PropositionalCalculus()
{
}

Letter &PropositionalCalculus::getLetterA() {
    return this->letterA;
}

Letter &PropositionalCalculus::getLetterB() {
    return this->letterB;
}

Sign PropositionalCalculus::getSign() const {
    return this->sign;
}

int PropositionalCalculus::getPriority() const {
    return this->priority;
}

void PropositionalCalculus::setPriority(int prio) {
    this->priority = prio;
}