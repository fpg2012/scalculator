#ifndef CONSTANTDIALOG_H
#define CONSTANTDIALOG_H

#include "backend.h"
#include "constdelegate.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class ConstantDialog;
}

class ConstantDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConstantDialog(Backend *be, QWidget *parent = nullptr);
    ~ConstantDialog();

signals:
    void constSelected(QString name);

private:
    Ui::ConstantDialog *ui;
    ConstDelegate *constDelegate_;
    QStandardItemModel *itemModel_;

    void handleConstListSelected();
};

#endif // CONSTANTDIALOG_H
