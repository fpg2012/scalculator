#ifndef UNIT_H
#define UNIT_H
#include <QString>
#include <QVariant>

struct Unit
{
    QString name;
    QString symbol;
    double coef, offset;
    Unit() = default;
    Unit(const QString &name, const QString &symbol, double coef = 1, double offset = 0)
        : name(name), symbol(symbol), coef(coef), offset(offset)
    {}

    bool operator==(const Unit &u)
    {
        return name == u.name && coef == u.coef && offset == u.offset;
    }
};

Q_DECLARE_METATYPE(Unit)

#endif // UNIT_H
