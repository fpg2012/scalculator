#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <string>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(centralWidget()->geometry());
    statusBar();
    initButtonData();
    setWindowTitle("Scalculator");
    setFocusPolicy(Qt::StrongFocus);
    installEventFilter(this);
    ui->editArea->installEventFilter(this);
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
    QString str = ui->editArea->toPlainText();
    str.append(data[qobject_cast<QPushButton*>(sender())]);
    ui->editArea->setText(str);
}

void MainWindow::handleBackspaceButtonClick() {
    QString str = ui->editArea->toPlainText();
    str.truncate(str.length() - 1);
    ui->editArea->setText(str);
}

void MainWindow::handleClearButtonClick() {
    ui->editArea->setText("");
    setStatusTip("Clear Button Clicked");
}

void MainWindow::handleEqualButtonClick() {
    std::string input = ui->editArea->toPlainText().toStdString();
    std::string output = be.calcNoExcp(input);
    displayResult(output);
}

void MainWindow::displayResult(std::string &str) {
    QString toDisplay;
    int cnt = 0;
    for (const char ch : str) {
       if (cnt % 20 == 0 && cnt != 0) {
           toDisplay.append('\n');
       }
       toDisplay.append(ch);
       ++cnt;
    }
    ui->resultArea->setText(toDisplay);
    ui->resultArea->setMinimumHeight(10 * ceil((double) cnt / 20));
    QTimer::singleShot(1, this, &MainWindow::myAdjustSize);
}

void MainWindow::myAdjustSize() {
    int width = this->width();
    adjustSize();
    int height = this->height();
    resize(width, height);
}

//void MainWindow::keyPressEvent(QKeyEvent *event) {

//}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return) {
            handleEqualButtonClick();
            return true;
        }
        else if (ke->key() == Qt::Key_Delete) {
            handleClearButtonClick();
            return true;
        }
        else if (ke->key() == Qt::Key_Equal) {
            handleEqualButtonClick();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
