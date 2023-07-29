#include "constantdialog.h"
#include "../ui/ui_constantdialog.h"
#include <QDebug>

ConstantDialog::ConstantDialog(Backend *be, QWidget *parent)
    : QDialog(parent), itemModel_(new QStandardItemModel(this)),
      constDelegate_(new ConstDelegate(this)), ui(new Ui::ConstantDialog)
{
    ui->setupUi(this);
    ui->constList->setItemDelegate(constDelegate_);
    ui->constList->setModel(itemModel_);

    setWindowTitle(tr("Constants Table - Click to insert"));

    auto constList = be->getConstList();
    // QDesktopWidget *temp = QApplication::desktop();
    // move(temp->width() / 2, temp->height() / 5);

    for (int i = 0; i < SE_M_CONST; ++i) {
        QString name(constList[i].const_name), value(constList[i].value);
        ConstItemData cid;
        cid.name = name;
        cid.value = value;
        QStandardItem *item = new QStandardItem();
        item->setData(QVariant::fromValue(cid), Qt::UserRole + 1);
        itemModel_->appendRow(item);
    }

    connect(ui->constList, &QListView::clicked, this, &ConstantDialog::handleConstListSelected);    
}

ConstantDialog::~ConstantDialog()
{
    delete ui;
}

void ConstantDialog::handleConstListSelected()
{
    QModelIndex index = ui->constList->currentIndex();
    QVariant var = index.data(Qt::UserRole + 1);
    ConstItemData itemData = var.value<ConstItemData>();
    QString temp = itemData.name;
    emit constSelected(temp);
}
