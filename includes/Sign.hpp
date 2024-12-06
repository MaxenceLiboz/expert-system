#include <iostream>
#include <string>
#include <exception>

class Sign {
public:
    enum Enum {
        AND,
        OR,
        NOT,
        XOR,
        IMPLIES,
        IF_ONLY_IF
    };

    static std::string  toString(Enum sign);
    static bool         isSign(std::string sign);
};