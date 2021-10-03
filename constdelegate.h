#ifndef CONSTDELEGATE_H
#define CONSTDELEGATE_H

#include "constitemdata.h"
#include "mydelegate.h"

class ConstDelegate : public MyDelegate
{
    Q_OBJECT
public:
    explicit ConstDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // CONSTDELEGATE_H
