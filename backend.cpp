#include "backend.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <future>
#include <sstream>
#include <thread>
#include <utility>

Backend::Backend(QObject *parent) : QObject(parent), se_hist_list_(sevaluator_history_create())
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
    error_map_[E_NO_HISTORY] = "Error::NoHistory";
    error_map_[E_TYPE] = "Error::ImproperType";
    error_map_[E_INVALID_PARAMETER] = "Error::InvalidParam";
    error_map_[E_UNKNOWN_TOKEN] = "Error::UnknownToken";
}

std::string Backend::calc(std::string input, bool sci_flt)
{
    //    std::packaged_task<std::string()> task([&] {
    //        char *output;
    //        std::string temp;
    //        ErrorType error = sevaluator_calc(input.c_str(),
    //                                          &output,
    //                                          se_hist_list_,
    //                                          10,
    //                                          sci_flt || sci_flt_);
    //        if (error != E_OK) {
    //            if (error_map_.find(error) == error_map_.end()) {
    //                temp = "Error";
    //            } else {
    //                temp = error_map_[error];
    //            }
    //        } else {
    //            temp = output;
    //            free(output);
    //        }
    //        return temp;
    //    });

    //    std::future<std::string> f1 = task.get_future();
    //    std::thread t(std::move(task));

    std::promise<std::string> p;
    std::future<std::string> f3 = p.get_future();
    std::thread([=, &p] {
        char *output;
        std::string temp;
        ErrorType error = sevaluator_calc(input.c_str(),
                                          &output,
                                          se_hist_list_,
                                          10,
                                          sci_flt || sci_flt_);
        if (error != E_OK) {
            if (error_map_.find(error) == error_map_.end()) {
                temp = "Error";
            } else {
                temp = error_map_[error];
            }
        } else {
            temp = output;
            free(output);
        };
        p.set_value_at_thread_exit(temp);
    }).detach();

    auto res = f3.wait_for(std::chrono::seconds(2));
    std::string ret;
    if (res == std::future_status::timeout) {
        ret = "Error::Timeout";
    } else {
        ret = f3.get();
    }
    //    t.join();
    return ret;
}

int Backend::getHistoryListLength()
{
    return se_hist_list_->len;
}

HistoryItemData Backend::getKthHistory(int k)
{
    FullResult *result = sevaluator_history_get(se_hist_list_, k);
    char *o_str = sevaluator_result_get_str(result, 10, false);
    const char *i_str = sevaluator_history_get_input(se_hist_list_, k);
    QString output(o_str);
    QString input(i_str);
    free(o_str);
    HistoryItemData hid;
    hid.input = input;
    hid.output = output;
    return hid;
}

const Constant *Backend::getConstList() const
{
    return sevaluator_result_get_const_table();
}
