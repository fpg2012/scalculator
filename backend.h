#ifndef BACKEND_H
#define BACKEND_H
#include "historyitemdata.h"
#include <map>
#include <sevaluator.h>
#include <string>
#include <QString>

class Backend
{
public:
    Backend();
	~Backend();
    std::string calc(std::string input);
    int getHistoryListLength();
    HistoryItemData getKthHistory(int k);

private:
    std::map<ErrorType, const char *> error_map_;
    HistoryList *se_hist_list_;
    void initErrorMap();
};

#endif // BACKEND_H
