#ifndef UNITCONVERTDIALOG_H
#define UNITCONVERTDIALOG_H

#include "unitdelegate.h"
#include "unitmanager.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class UnitConvertDialog;
}

class UnitConvertDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UnitConvertDialog(QWidget *parent = nullptr);
    ~UnitConvertDialog();

    void handleCategoryChange(int);
    void handleFromSelected();
    void handleToSelected();

    void handleOk();

signals:
    void formulaGenerated(const QString &formula);

private:
    Ui::UnitConvertDialog *ui;
    QStandardItemModel *itemModel_;
    UnitDelegate *unitDelegate_;
    UnitManager *manager_;
    QString from, to;

    const UnitCategory *getCat() const;
};

#endif // UNITCONVERTDIALOG_H
