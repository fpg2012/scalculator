#ifndef CONSTITEMDATA_H
#define CONSTITEMDATA_H

#include <QString>
#include <QVariant>

struct ConstItemData
{
    QString name;
    QString value;
};

Q_DECLARE_METATYPE(ConstItemData)

#endif // CONSTITEMDATA_H
