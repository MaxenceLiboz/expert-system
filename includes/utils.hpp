#ifndef UTLIS_HPP
#define UTLIS_HPP

#include <ctype.h>
#include "Sign.hpp"

void readNextLetter(const std::string &line, char &c, std::size_t &index);
void readNextSign(const std::string &line, std::string &sign, std::size_t &index);

#endif