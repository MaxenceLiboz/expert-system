#include "Rule.hpp"

Rule::Rule(std::string rule) {
    this->name = rule;

    this->initCalculus();
}

Rule::~Rule() {}

std::string Rule::getName() const {
    return this->name;
}

void Rule::setName(std::string name) {
    this->name = name;
}

Rule::calculusType Rule::getCalculus() const {
    return this->calculus;
}

bool Rule::operator==(const Rule &rule) const {
    return this->name == rule.getName();
}

void Rule::initCalculus() {
    for (char c : this->name) {
        (void)c;
        break;
    }
}

std::size_t HashRule::operator()(const Rule &rule) const {
    return std::hash<std::string>{}(rule.getName());
}
