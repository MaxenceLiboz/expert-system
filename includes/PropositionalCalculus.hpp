#ifndef PROPOSITIONAL_CALCULUS
#define PROPOSITIONAL_CALCULUS

#include "Letter.hpp"
#include "Sign.hpp"

class PropositionalCalculus
{
private:
    Letter          &letterA;
    Letter          &letterB;
    Sign            sign;
    int             priority;

public:
    PropositionalCalculus(Letter &letterA, Letter &letterB, Sign sign);
    ~PropositionalCalculus();

    Letter &getLetterA();
    Letter &getLetterB();
    Sign    getSign() const;
    int     getPriority() const;

    void    setPriority(int prio);
};



#endif