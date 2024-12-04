#ifndef LETTER_HPP
#define LETTER_HPP

#include <string>
#include <unordered_set>

enum LetterValueFrom {
    DEFAULT,
    INIT_FACTS,
    RULES
};

class Letter
{
private:
    typedef std::unordered_set<std::string> associateRulesNameType;

    char            letter;
    bool            value = false;

    LetterValueFrom valueFrom = DEFAULT;
    associateRulesNameType associateRulesName;

public:

    Letter(char letter);
    Letter(char letter, bool value, LetterValueFrom valueFrom);
    ~Letter();


    char                getLetter() const;
    bool                getValue() const;
    LetterValueFrom     getValueFrom() const;


    void                setValue(bool value);
    void                setValueFrom(LetterValueFrom valueFrom);

    bool                operator==(const Letter &letter) const;

};

struct HashLetter
{
    std::size_t operator()(const Letter &letter) const;
};






#endif