#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "backend.h"
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QSet>
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
    QVector<QPushButton *> advanceButtons;
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

    void initButtonData();

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
    void displayResult(std::string &str);
    void myAdjustSize();
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MAINWINDOW_H
