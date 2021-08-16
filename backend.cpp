#include "backend.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>

Backend::Backend() : se_hist_list_(sevaluator_history_create())
{
    initErrorMap();
}

Backend::~Backend()
{
    sevaluator_history_destory(se_hist_list_);
}

void Backend::initErrorMap()
{
    error_map_[E_DIV_ZERO] = "Error::DivideZero";
    error_map_[E_SYNTAX] = "Error::Syntax";
    error_map_[E_NEGATIVE_ROOT] = "Error::NegativeRoot";
    error_map_[E_NO_HISTORY] = "Error::HistoryDisabled";
    error_map_[E_TYPE] = "Error::ImproperType";
    error_map_[E_INVALID_PARAMETER] = "Error::InvalidParameter";
}

std::string Backend::calc(std::string input)
{
    char *output;
    std::string temp;
    ErrorType error = sevaluator_calc(input.c_str(), &output, se_hist_list_, 10);
    if (error != E_OK) {
        temp = error_map_[error];
    } else {
        temp = output;
        free(output);
    }
    return temp;
}
