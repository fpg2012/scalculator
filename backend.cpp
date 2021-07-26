#include "backend.h"
#include <sstream>

Backend::Backend()
{

}

CalcResult::CalcResult(std::string str) : is_error(false), str(str) {

}

CalcResult::CalcResult(const char *str) : is_error(false), str(str) {

}

CalcResult::CalcResult(CalcError ce) : is_error(false), ce(ce) {

}

CalcResult Backend::calc(std::string input) {
    return "Not Implemented";
}

std::string Backend::calcNoExcp(std::string input) {
    int temp = rand() / 1000;
    std::stringstream ss;
    ss << temp;
    return ss.str();
}

