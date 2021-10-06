#ifndef UNITMANAGER_H
#define UNITMANAGER_H
#include "unit.h"
#include "unitcategory.h"
#include <QMap>
#include <QString>
#include <QVector>

class UnitManager : QObject
{
    Q_OBJECT
public:
    UnitManager(QObject *parent = nullptr);

    const UnitCategory *getCategory(const QString &name);
    QList<QString> getCategoryList() const;

private:
    QMap<QString, UnitCategory *> cm;
};

#endif // UNITMANAGER_H
