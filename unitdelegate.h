#ifndef UNITDELEGATE_H
#define UNITDELEGATE_H

#include "mydelegate.h"
#include "unit.h"

class UnitDelegate : public MyDelegate
{
    Q_OBJECT
public:
    explicit UnitDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // UNITDELEGATE_H
