#ifndef RULE_HPP
#define RULE_HPP

#include <string>
#include <map>
#include <queue>
#include <unordered_map>


class Rule
{
private:
    typedef std::vector<std::pair<std::string, bool>> calculusType;

    std::string name;
    calculusType calculus;

    void            initCalculus();

public:
    Rule(std::string rule);
    ~Rule();

    std::string     getName() const;
    calculusType    getCalculus() const;

    void            setName(std::string name);

    bool            operator==(const Rule &rule) const;
};

struct HashRule
{
    std::size_t operator()(const Rule &rule) const;
};




#endif