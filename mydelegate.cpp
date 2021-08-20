#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void MyDelegate::paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }
    painter->save();
    QVariant var = index.data(Qt::UserRole + 1);
    HistoryItemData itemData = var.value<HistoryItemData>();

    qreal spacing = 4;
    qreal height = option.rect.height() / 2 - spacing;
    qreal width = option.rect.width() - spacing * 2;
    QRectF iArea(option.rect.left() + spacing, option.rect.top() + spacing, width, height);
    QRectF oArea(option.rect.left() + spacing, option.rect.top() + spacing + height, width, height);

    painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
    painter->setFont(QFont("JetBrains Mono NL", 9));

    QString input(itemData.input), output(itemData.output);
    if (input.length() > 20) {
        input = input.left(17);
        input.append("...");
    }
    if (output.length() > 13) {
        output = output.left(10);
        output.append("...");
    }

    painter->drawText(iArea, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere, input);
    painter->setFont(QFont("JetBrains Mono NL", 12));
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    painter->drawText(oArea, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere, "=");
    painter->drawText(oArea, Qt::AlignRight | Qt::AlignVCenter | Qt::TextWrapAnywhere, output);

    painter->setBrush(QBrush(QColor(0, 0, 0, 150)));
    painter->setPen(QPen(QBrush(QColor(0, 0, 0, 150)), 1));
    painter->drawLine(option.rect.left(),
                      option.rect.bottom(),
                      option.rect.right(),
                      option.rect.bottom());
    if (option.state.testFlag(QStyle::State_Selected)) {
        QRectF rect = option.rect;
        painter->setPen(QPen(QColor(150, 0, 150, 50)));
        painter->setBrush(QColor(150, 0, 150, 50));
        painter->drawRect(rect);
    }
    painter->restore();
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 50);
}
