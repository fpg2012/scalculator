#ifndef MYDELEGATE_H
#define MYDELEGATE_H
#include "historyitemdata.h"
#include <QFont>
#include <QPainter>
#include <QString>
#include <QStyledItemDelegate>
#include <QVariant>

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MYDELEGATE_H
