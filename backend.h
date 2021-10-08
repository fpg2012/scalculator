#ifndef BACKEND_H
#define BACKEND_H
#include "historyitemdata.h"
#include <map>
#include <sevaluator.h>
#include <string>
#include <QObject>
#include <QString>

class Backend : QObject
{
    Q_OBJECT
public:
    Backend(QObject *parent = nullptr);
    ~Backend();
    std::string calc(std::string input, bool sci_flt = false);
    int getHistoryListLength();
    HistoryItemData getKthHistory(int k);
    const Constant *getConstList() const;
    void setDigits(unsigned digits) { digits_ = digits; }
    void setSciFlt(bool sci_flt) { sci_flt_ = sci_flt; }
signals:
    void resultReady(std::string result);

private:
    std::map<ErrorType, const char *> error_map_;
    HistoryList *se_hist_list_;
    unsigned digits_ = 10;
    bool sci_flt_ = false;

    std::string temp_ret;

    void initErrorMap();
};

#endif // BACKEND_H
