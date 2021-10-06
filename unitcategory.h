#ifndef UNITCATEGORY_H
#define UNITCATEGORY_H
#include "unit.h"
#include <QObject>
#include <QString>

struct UnitCategory : QObject
{
    Q_OBJECT
public:
    QString cat_name;
    const Unit base_unit;
    QMap<QString, Unit> um;

    UnitCategory(QString cat_name,
                 const Unit &base_unit,
                 const QVector<Unit> &units,
                 QObject *parent = nullptr)
        : QObject(parent), cat_name(cat_name), base_unit(base_unit)
    {
        for (auto unit : units) {
            um.insert(unit.name, unit);
        }
    }

    // this function does not check whether the unit name is valid
    // convert value from _unit1_ to _unit2_
    // unit1 -> base unit -> unit2
    QString getConversionFormula(const QString &unit1, const QString &unit2) const
    {
        auto str = QString("flt[(ans - %1) / %2 * %3 + %4]")
                       .arg(um[unit1].offset)
                       .arg(um[unit1].coef)
                       .arg(um[unit2].coef)
                       .arg(um[unit2].offset);
        return str;
    }
};

#endif // UNITCATEGORY_H
