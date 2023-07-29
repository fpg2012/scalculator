#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "backend.h"
#include "constantdialog.h"
#include "mydelegate.h"
#include "unitconvertdialog.h"
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QSet>
#include <QStandardItemModel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap<QPushButton*, QString> data;
    QVector<QPushButton*> numberButtons;
    QVector<QWidget *> advanceWidgets;
    QSet<QPushButton *> noParamFunc;
    QSet<QPushButton *> oneParamFunc;
    QSet<QPushButton *> twoParamFunc;
    Backend be;
    enum ShiftState {
        ShiftSin,
        ShiftSec,
        ShiftAsin,
    } shift_state_;
    enum ModeState {
        ModeSimple,
        ModeAdvance,
    } mode_state_;
    QStandardItemModel *itemModel;
    MyDelegate *myDelegate;
    ConstantDialog *constDialog_;
    UnitConvertDialog *unitDialog_;

    void initButtonData();
    void initMenu();

    // events
//    void keyPressEvent(QKeyEvent *event) override;

    // slot functions
    void handleNumberButtonClick();
    void handleClearButtonClick();
    void handleEqualButtonClick();
    void handleBackspaceButtonClick();
    void handleShiftButtonClick();
    void handleModeButtonClick();
    void handleRFButton();
    void handleConstButtonClick();
    void handleHistoryButton();
    void handleUnitButton();

    void handleSciButtonStateChange();

    void handleHistorySelect();
    void handleConstSelect(const QString &name);
    void handleUnitConvertSelect(const QString &name);

    void displayResult(const std::string &str);
    void updateHistoryList(const std::string &input, const std::string &output);
    void myAdjustSize();
    bool eventFilter(QObject *obj, QEvent *event) override;

    void showAboutDialog();
    void showUsageDialog();

    void calc(bool sci_flt = false);
};
#endif // MAINWINDOW_H
