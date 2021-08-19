#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <string>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), shift_state_(ShiftSin), mode_state_(ModeSimple),
      itemModel(new QStandardItemModel(this)), myDelegate(new MyDelegate(this))
{
    ui->setupUi(this);
    setGeometry(centralWidget()->geometry());
    //    statusBar();
    initButtonData();
    setWindowTitle("Scalculator");
    setFocusPolicy(Qt::StrongFocus);
    installEventFilter(this);
    ui->editArea->installEventFilter(this);
    ui->historyList->setItemDelegate(myDelegate);
    ui->historyList->setModel(itemModel);
    ui->historyList->setVisible(false);
    //    ui->historyList->setStyleSheet("background-color: rgba(250, 250, 250, 0);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initButtonData() {
    connect(ui->modeButton, &QPushButton::clicked, this, &MainWindow::handleModeButtonClick);
    connect(ui->rfButton, &QPushButton::clicked, this, &MainWindow::handleRFButton);
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::handleHistoryButton);
    connect(ui->historyList, &QListView::clicked, this, &MainWindow::handleHistorySelect);

    numberButtons << ui->pushButton_0 << ui->pushButton_1 << ui->pushButton_2 << ui->pushButton_3
                  << ui->pushButton_4 << ui->pushButton_5 << ui->pushButton_6 << ui->pushButton_7
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
    data[ui->pushButton_root_2] = "√";
    connect(ui->pushButton_root_2,
            &QPushButton::clicked,
            this,
            &MainWindow::handleNumberButtonClick);
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

    advanceButtons << ui->pushButton_sin << ui->pushButton_cos << ui->pushButton_tan
                   << ui->pushButton_ln << ui->pushButton_lg << ui->pushButton_log2
                   << ui->pushButton_exp << ui->pushButton_root << ui->pushButton_e
                   << ui->shiftButton << ui->pushButton_ans << ui->pushButton_pi;

    data[ui->pushButton_sin] = "sin";
    connect(ui->pushButton_sin, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_cos] = "cos";
    connect(ui->pushButton_cos, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_tan] = "tan";
    connect(ui->pushButton_tan, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_ln] = "ln";
    connect(ui->pushButton_ln, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_lg] = "log10";
    connect(ui->pushButton_lg, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_log2] = "log2";
    connect(ui->pushButton_log2, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_exp] = "exp";
    connect(ui->pushButton_exp, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_root] = "root";
    connect(ui->pushButton_root, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_e] = "e";
    connect(ui->pushButton_e, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_ans] = "ans";
    connect(ui->pushButton_ans, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_pi] = "π";
    connect(ui->pushButton_pi, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);

    connect(ui->shiftButton, &QPushButton::clicked, this, &MainWindow::handleShiftButtonClick);

    for (auto i = advanceButtons.begin(); i != advanceButtons.end(); ++i) {
        (*i)->setVisible(false);
    }

    oneParamFunc << ui->pushButton_sin << ui->pushButton_cos << ui->pushButton_tan
                 << ui->pushButton_ln << ui->pushButton_lg << ui->pushButton_log2
                 << ui->pushButton_exp;
    twoParamFunc << ui->pushButton_root;
}

void MainWindow::handleNumberButtonClick()
{
    QTextCursor temp = ui->editArea->textCursor();
    QString selected = temp.selectedText();
    auto *btn = qobject_cast<QPushButton *>(sender());
    temp.insertText(data[btn]);
    if (oneParamFunc.find(btn) != oneParamFunc.end()) {
        temp.insertText("[" + selected + "]");
        temp.movePosition(QTextCursor::PreviousCharacter);
        ui->editArea->setTextCursor(temp);
    } else if (twoParamFunc.find(btn) != twoParamFunc.end()) {
        temp.insertText("[" + selected + ", ]");
        temp.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor, 2);
    } else if (data[btn] == "(") {
        temp.insertText(selected + ")");
        ui->editArea->setTextCursor(temp);
    } else if (data[btn] == "[") {
        temp.insertText(selected + "]");
        ui->editArea->setTextCursor(temp);
    }
}

void MainWindow::handleBackspaceButtonClick() {
    QTextCursor temp = ui->editArea->textCursor();
    if (temp.hasSelection()) {
        temp.removeSelectedText();
    } else {
        temp.deletePreviousChar();
    }
}

void MainWindow::handleClearButtonClick() {
    ui->editArea->setText("");
}

void MainWindow::handleEqualButtonClick() {
    std::string input = ui->editArea->toPlainText().toStdString();
    std::string output = be.calc(input);
    displayResult(output);
    updateHistoryList(input, output);
}

void MainWindow::handleShiftButtonClick()
{
    if (shift_state_ == ShiftSin) {
        shift_state_ = ShiftAsin;
        data[ui->pushButton_sin] = "asin";
        ui->pushButton_sin->setText("asin");
        data[ui->pushButton_cos] = "acos";
        ui->pushButton_cos->setText("acos");
        data[ui->pushButton_tan] = "atan";
        ui->pushButton_tan->setText("atan");

        data[ui->pushButton_lf] = "[";
        ui->pushButton_lf->setText("[");
        data[ui->pushButton_rt] = "]";
        ui->pushButton_rt->setText("]");
    } else if (shift_state_ == ShiftAsin) {
        shift_state_ = ShiftSec;
        data[ui->pushButton_sin] = "sec";
        ui->pushButton_sin->setText("sec");
        data[ui->pushButton_cos] = "csc";
        ui->pushButton_cos->setText("csc");
        data[ui->pushButton_tan] = "cot";
        ui->pushButton_tan->setText("cot");
        data[ui->pushButton_lf] = "[";
        ui->pushButton_lf->setText("[");
        data[ui->pushButton_rt] = "]";
        ui->pushButton_rt->setText("]");
        data[ui->pushButton_dot] = ",";
        ui->pushButton_dot->setText(",");
    } else {
        shift_state_ = ShiftSin;
        data[ui->pushButton_sin] = "sin";
        ui->pushButton_sin->setText("sin");
        data[ui->pushButton_cos] = "cos";
        ui->pushButton_cos->setText("cos");
        data[ui->pushButton_tan] = "tan";
        ui->pushButton_tan->setText("tan");
        data[ui->pushButton_lf] = "(";
        ui->pushButton_lf->setText("(");
        data[ui->pushButton_rt] = ")";
        ui->pushButton_rt->setText(")");
        data[ui->pushButton_dot] = ".";
        ui->pushButton_dot->setText(".");
    }
}

void MainWindow::handleModeButtonClick()
{
    bool flag = false;
    if (mode_state_ == ModeSimple) {
        mode_state_ = ModeAdvance;
        flag = true;
    } else {
        mode_state_ = ModeSimple;
        flag = false;
    }
    for (auto i = advanceButtons.begin(); i != advanceButtons.end(); ++i) {
        (*i)->setVisible(flag);
    }
}

void MainWindow::handleRFButton()
{
    ui->editArea->setText("flt[ans]");
    handleEqualButtonClick();
}

void MainWindow::handleHistoryButton()
{
    ui->historyList->setVisible(!ui->historyList->isVisible());
}

void MainWindow::handleHistorySelect()
{
    QTextCursor temp = ui->editArea->textCursor();
    QModelIndex index = ui->historyList->currentIndex();
    temp.insertText("hist[" + QString::number(index.row()) + "]");
}

void MainWindow::displayResult(const std::string &str)
{
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

void MainWindow::updateHistoryList(const std::string &input, const std::string &output)
{
    QString result = QString::fromStdString(output);
    if (result.startsWith("Error")) {
        return;
    }
    QString in = QString::fromStdString(input);
    HistoryItemData hid;
    hid.input = in;
    hid.output = result;
    QStandardItem *item = new QStandardItem();
    item->setData(QVariant::fromValue(hid), Qt::UserRole + 1);
    itemModel->appendRow(item);
    handleClearButtonClick();
}

void MainWindow::myAdjustSize() {
    int width = this->width();
    adjustSize();
    int height = this->height();
    resize(width, height);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        bool flag = false;
        auto *ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return) {
            handleEqualButtonClick();
            flag = true;
        }
        else if (ke->key() == Qt::Key_Delete) {
            handleClearButtonClick();
            flag = true;
        }
        else if (ke->key() == Qt::Key_Equal) {
            handleEqualButtonClick();
            flag = true;
        } else if (ke->key() == Qt::Key_Tab) {
            handleRFButton();
            flag = true;
        }
        if (!ui->editArea->hasFocus()) {
            ui->editArea->setFocus();
            ui->editArea->moveCursor(QTextCursor::End);
            int k = ke->key();
            if (k >= 32 && k <= 126) {
                ui->editArea->append(QString(static_cast<QChar>(k)));
            }
        }
        return flag;
    }
    return QMainWindow::eventFilter(obj, event);
}
