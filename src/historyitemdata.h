#ifndef HISTORYITEMDATA_H
#define HISTORYITEMDATA_H

#include <QString>
#include <QVariant>

struct HistoryItemData
{
    QString input;
    QString output;
};

Q_DECLARE_METATYPE(HistoryItemData)

#endif // HISTORYITEMDATA_H
