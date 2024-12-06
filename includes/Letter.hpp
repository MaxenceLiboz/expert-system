#ifndef LETTER_HPP
#define LETTER_HPP

#include <string>
#include <vector>

enum LetterValueFrom {
    DEFAULT,
    INIT_FACTS,
    RULES
};

class Letter
{
private:
    char            letter;
    bool            value = false;

    LetterValueFrom valueFrom = DEFAULT;
    std::vector<std::string> associateRulesValue;

public:

    Letter(char letter);
    Letter(char letter, bool value, LetterValueFrom valueFrom);
    ~Letter();


    char                getLetter() const;
    bool                getValue() const;
    LetterValueFrom     getValueFrom() const;


    void                setValue(bool value);
    void                setValueFrom(LetterValueFrom valueFrom);

    void                addAssociateRuleValue(const std::string ruleName);

    bool                operator==(const Letter &letter) const;

};

struct HashLetter
{
    std::size_t operator()(const Letter &letter) const;
};






#endif