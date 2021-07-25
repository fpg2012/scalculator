#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(centralWidget()->geometry());
    statusBar();
    initButtonData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initButtonData() {
    numberButtons << ui->pushButton_0 << ui->pushButton_1
                  << ui->pushButton_2 << ui->pushButton_3
                  << ui->pushButton_4 << ui->pushButton_5
                  << ui->pushButton_6 << ui->pushButton_7
                  << ui->pushButton_8 << ui->pushButton_9;
    char ch = '0';
    for (int i = 0;i <= 9;++i) {
        data[numberButtons[i]] = QString(QChar(ch + i));
    }
    data[ui->pushButton_dot] = ".";
    connect(ui->pushButton_dot, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_divide] = "/";
    connect(ui->pushButton_divide, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_add] = "+";
    connect(ui->pushButton_add, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_times] = "*";
    connect(ui->pushButton_times, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_minus] = "-";
    connect(ui->pushButton_minus, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_pow10] = "10^";
    connect(ui->pushButton_pow10, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_power] = "^";
    connect(ui->pushButton_power, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_root] = "√";
    connect(ui->pushButton_root, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_lf] = "(";
    connect(ui->pushButton_lf, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_rt] = ")";
    connect(ui->pushButton_rt, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);

    for (int i = 0;i <= 9;++i) {
        connect(numberButtons[i], &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    }
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::handleClearButtonClick);
    connect(ui->backspaceButton, &QPushButton::clicked, this, &MainWindow::handleBackspaceButtonClick);
    connect(ui->pushButton_eq, &QPushButton::clicked, this, &MainWindow::handleEqualButtonClick);
}

void MainWindow::handleNumberButtonClick() {
    QString str = ui->displayArea->toPlainText();
    str.append(data[qobject_cast<QPushButton*>(sender())]);
    ui->displayArea->setText(str);
}

void MainWindow::handleBackspaceButtonClick() {
    QString str = ui->displayArea->toPlainText();
    str.truncate(str.length() - 1);
    ui->displayArea->setText(str);
}

void MainWindow::handleClearButtonClick() {
    ui->displayArea->setText("");
    setStatusTip("Clear Button Clicked");
}

void MainWindow::handleEqualButtonClick() {
    ui->displayArea->setText("");
    setStatusTip("Equal Button Clicked");
}
