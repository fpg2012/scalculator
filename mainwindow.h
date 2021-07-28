#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QPushButton>
#include "backend.h"

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
    Backend be;

    void initButtonData();

    // slot functions
    void handleNumberButtonClick();
    void handleClearButtonClick();
    void handleEqualButtonClick();
    void handleBackspaceButtonClick();
    void displayResult(std::string &str);
    void myAdjustSize();
};
#endif // MAINWINDOW_H
