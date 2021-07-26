#ifndef BACKEND_H
#define BACKEND_H
#include <string>

enum CalcError {
    Unknown = 0,
    Math = 1,
    Parenthesis = 2,
};

struct CalcResult {
    bool is_error;
    std::string str;
    CalcError ce;
    CalcResult(std::string str);
    CalcResult(const char* str);
    CalcResult(CalcError error);
};

class Backend
{
public:
    Backend();
    CalcResult calc(std::string input);
    std::string calcNoExcp(std::string input);
};

#endif // BACKEND_H
