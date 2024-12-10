#ifndef LETTER_HPP
#define LETTER_HPP

#include <string>
#include <vector>

enum LetterValueFrom {
    DEFAULT,
    INIT_FACTS,
    RULES
};

enum LetterValue {
    FALSE,
    TRUE,
    UNDEFINED
};

class Letter
{
private:
    char            letter;
    LetterValue     value = FALSE;

    LetterValueFrom valueFrom = DEFAULT;
    std::vector<std::string> associateRulesValue;

public:

    Letter(char letter);
    Letter(char letter, LetterValue value, LetterValueFrom valueFrom);
    ~Letter();


    char                getLetter() const;
    LetterValue         getValue() const;
    LetterValue         getInverseValue() const;
    LetterValueFrom     getValueFrom() const;


    void                setValue(LetterValue value);
    void                setValueFrom(LetterValueFrom valueFrom);

    void                addAssociateRuleValue(const std::string ruleName);

    bool                operator==(const Letter &letter) const;

};

struct HashLetter
{
    std::size_t operator()(const Letter &letter) const;
};






#endif