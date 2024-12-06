#include "utils.hpp"

void readNextLetter(const std::string &line, char &c, std::size_t &index) {
    if (line[index] == '(' || line[index] == '!') {
        index++;
    }
    if (!isalpha(line[index])){
        throw std::invalid_argument("Error occured in line: " + line + ". Char \'" + line[index] + "\' where given at index " + std::to_string(index) + " instead of letter");
    }
    c = line[index++];
    if (line[index] == ')') {
        index++;
    }
}

void readNextSign(const std::string &line, std::string &sign, std::size_t &index) {
    std::size_t start = index;
    while (index < line.size() && !isalpha(line[index])) {
        index++;
    }
    sign = line.substr(start, index - start);
    if (!Sign::isSign(sign) && sign != ""){
        throw std::invalid_argument("Error occured in line: " + line + ". Sign \'" + sign + "\' but it is not valid.");
    }
}
