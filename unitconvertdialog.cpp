#include "unitconvertdialog.h"
#include "ui_unitconvertdialog.h"
#include <QComboBox>

UnitConvertDialog::UnitConvertDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::UnitConvertDialog), itemModel_(new QStandardItemModel(this)),
      unitDelegate_(new UnitDelegate(this)), manager_(new UnitManager(this))
{
    ui->setupUi(this);
    ui->fromList->setModel(itemModel_);
    ui->toList->setModel(itemModel_);
    ui->fromList->setItemDelegate(unitDelegate_);
    ui->toList->setItemDelegate(unitDelegate_);
    setWindowTitle(tr("Unit Convert"));

    auto cats = manager_->getCategoryList();
    for (auto i = cats.begin(); i != cats.end(); ++i) {
        ui->comboBox->addItem(*i);
    }

    handleCategoryChange(0);
    connect(ui->comboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &UnitConvertDialog::handleCategoryChange);
    connect(ui->fromList, &QListView::clicked, this, &UnitConvertDialog::handleFromSelected);
    connect(ui->toList, &QListView::clicked, this, &UnitConvertDialog::handleToSelected);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UnitConvertDialog::handleOk);
}

UnitConvertDialog::~UnitConvertDialog()
{
    delete ui;
}

void UnitConvertDialog::handleCategoryChange(int)
{
    auto cat = getCat();
    itemModel_->clear();
    for (auto i = cat->um.begin(); i != cat->um.end(); ++i) {
        QStandardItem *item = new QStandardItem();
        item->setData(QVariant::fromValue(*i), Qt::UserRole + 1);
        itemModel_->appendRow(item);
    }
}

void UnitConvertDialog::handleFromSelected()
{
    QVariant temp = ui->fromList->currentIndex().data(Qt::UserRole + 1);
    Unit fr_ = temp.value<Unit>();
    from = fr_.name;
}

void UnitConvertDialog::handleToSelected()
{
    QVariant temp = ui->toList->currentIndex().data(Qt::UserRole + 1);
    Unit to_ = temp.value<Unit>();
    to = to_.name;
}

const UnitCategory *UnitConvertDialog::getCat() const
{
    QString temp = ui->comboBox->currentText();
    return manager_->getCategory(temp);
}

void UnitConvertDialog::handleOk()
{
    emit formulaGenerated(getCat()->getConversionFormula(from, to));
}
