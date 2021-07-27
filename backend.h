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
	~Backend();
    CalcResult calc(std::string input);
    std::string calcNoExcp(std::string input);
private:
	int bc_in_pipe[2];
	int bc_out_pipe[2];
	int bc_in_fd;
	int bc_out_fd;
	FILE* bc_in;
	FILE* bc_out;
};

#endif // BACKEND_H
