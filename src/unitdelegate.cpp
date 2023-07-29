#include "unitdelegate.h"

UnitDelegate::UnitDelegate(QObject *parent) : MyDelegate(parent) {}

void UnitDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }
    painter->save();
    QVariant var = index.data(Qt::UserRole + 1);
    Unit itemData = var.value<Unit>();

    qreal spacing = 4;
    qreal height = option.rect.height() / 2 - spacing;
    qreal width = option.rect.width() - spacing * 2;
    QRectF iArea(option.rect.left() + spacing, option.rect.top() + spacing, width, height);
    QRectF oArea(option.rect.left() + spacing, option.rect.top() + spacing + height, width, height);

    painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
    painter->setFont(QFont("JetBrains Mono NL", 9));

    QString input(itemData.name), output(itemData.symbol);

    painter->drawText(iArea, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere, input);
    painter->setFont(QFont("JetBrains Mono NL", 12));
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    //    painter->drawText(oArea, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere, "=");
    painter->drawText(oArea, Qt::AlignRight | Qt::AlignVCenter | Qt::TextWrapAnywhere, output);

    painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
    painter->setPen(QPen(QBrush(QColor(0, 0, 0, 150)), 1));
    painter->drawLine(option.rect.left(),
                      option.rect.bottom(),
                      option.rect.right(),
                      option.rect.bottom());
    if (option.state.testFlag(QStyle::State_Selected)) {
        QRectF rect = option.rect;
        painter->setPen(QPen(QColor(150, 150, 0, 50)));
        painter->setBrush(QColor(150, 150, 0, 50));
        painter->drawRect(rect);
    }
    painter->restore();
}
