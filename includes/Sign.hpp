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

    Sign(Enum sign);
    ~Sign();

    std::string toString() const;

private:
    Enum value;
};