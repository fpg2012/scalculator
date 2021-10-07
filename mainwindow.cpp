#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "constantdialog.h"
#include <cmath>
#include <string>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QTranslator>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), shift_state_(ShiftSin), mode_state_(ModeSimple),
      itemModel(new QStandardItemModel(this)), myDelegate(new MyDelegate(this)),
      constDialog_(new ConstantDialog(&be, this)), unitDialog_(new UnitConvertDialog(this))
{
    ui->setupUi(this);
    setGeometry(centralWidget()->geometry());
    //    statusBar();
    initButtonData();
    initMenu();
    setWindowTitle("Scalculator");
    setWindowIcon(QIcon(":/pic/icon"));
    setFocusPolicy(Qt::StrongFocus);
    installEventFilter(this);
    ui->editArea->installEventFilter(this);
    ui->historyList->setItemDelegate(myDelegate);
    ui->historyList->setModel(itemModel);
    ui->historyList->setVisible(false);
    ui->resultScrollArea->setStyleSheet("background-color: rgba(250, 250, 250, 0);");
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

    advanceWidgets << ui->pushButton_sin << ui->pushButton_cos << ui->pushButton_tan
                   << ui->pushButton_ln << ui->pushButton_lg << ui->pushButton_log2
                   << ui->pushButton_exp << ui->pushButton_root << ui->pushButton_e
                   << ui->shiftButton << ui->pushButton_ans << ui->pushButton_pi
                   << ui->pushButton_rand << ui->pushButton_fact << ui->pushButton_rnd
                   << ui->pushButton_const << ui->checkBox_sci;

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

    data[ui->pushButton_rand] = "rand";
    connect(ui->pushButton_rand, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_fact] = "!";
    connect(ui->pushButton_fact, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);
    data[ui->pushButton_rnd] = "round";
    connect(ui->pushButton_rnd, &QPushButton::clicked, this, &MainWindow::handleNumberButtonClick);

    connect(ui->pushButton_const, &QPushButton::clicked, this, &MainWindow::handleConstButtonClick);
    connect(ui->shiftButton, &QPushButton::clicked, this, &MainWindow::handleShiftButtonClick);

    for (auto i = advanceWidgets.begin(); i != advanceWidgets.end(); ++i) {
        (*i)->setVisible(false);
    }

    noParamFunc << ui->pushButton_rand;
    oneParamFunc << ui->pushButton_sin << ui->pushButton_cos << ui->pushButton_tan
                 << ui->pushButton_ln << ui->pushButton_lg << ui->pushButton_log2
                 << ui->pushButton_exp << ui->pushButton_rnd;
    twoParamFunc << ui->pushButton_root;

    connect(constDialog_, &ConstantDialog::constSelected, this, &MainWindow::handleConstSelect);
    connect(unitDialog_,
            &UnitConvertDialog::formulaGenerated,
            this,
            &MainWindow::handleUnitConvertSelect);

    connect(ui->checkBox_sci,
            &QCheckBox::stateChanged,
            this,
            &MainWindow::handleSciButtonStateChange);
    connect(ui->unitButton, &QPushButton::clicked, this, &MainWindow::handleUnitButton);
}

void MainWindow::initMenu()
{
    auto *aboutAction = new QAction(tr("&about"), this);
    auto *usageAction = new QAction(tr("&usage"), this);
    //    auto *settingAction = new QAction(tr("Setting"), this);

    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(usageAction, &QAction::triggered, this, &MainWindow::showUsageDialog);

    menuBar()->addAction(usageAction);
    menuBar()->addAction(aboutAction);
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
    } else if (noParamFunc.find(btn) != noParamFunc.end()) {
        temp.insertText("[]");
        ui->editArea->setTextCursor(temp);
    } else if (twoParamFunc.find(btn) != twoParamFunc.end()) {
        temp.insertText("[" + selected + ", ]");
        temp.movePosition(QTextCursor::PreviousCharacter);
        ui->editArea->setTextCursor(temp);
    } else if (data[btn] == "(") {
        temp.insertText(selected + ")");
        if (selected == "") {
            temp.movePosition(QTextCursor::PreviousCharacter);
        }
        ui->editArea->setTextCursor(temp);
    } else if (data[btn] == "[") {
        temp.insertText(selected + "]");
        if (selected == "") {
            temp.movePosition(QTextCursor::PreviousCharacter);
        }
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

void MainWindow::handleEqualButtonClick()
{
    calc(false);
}

void MainWindow::calc(bool sci_flt)
{
    std::string input = ui->editArea->toPlainText().toStdString();
    std::string output = be.calc(input, sci_flt);
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
        data[ui->pushButton_rnd] = "floor";
        ui->pushButton_rnd->setText("flr");

        data[ui->pushButton_lf] = "[";
        ui->pushButton_lf->setText("[");
        data[ui->pushButton_rt] = "]";
        ui->pushButton_rt->setText("]");

        data[ui->pushButton_root_2] = "%";
        ui->pushButton_root_2->setText("%");
    } else if (shift_state_ == ShiftAsin) {
        shift_state_ = ShiftSec;
        data[ui->pushButton_sin] = "sec";
        ui->pushButton_sin->setText("sec");
        data[ui->pushButton_cos] = "csc";
        ui->pushButton_cos->setText("csc");
        data[ui->pushButton_tan] = "cot";
        ui->pushButton_tan->setText("cot");
        data[ui->pushButton_rnd] = "ceil";
        ui->pushButton_rnd->setText("ceil");

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
        data[ui->pushButton_rnd] = "round";
        ui->pushButton_rnd->setText("rnd");

        data[ui->pushButton_lf] = "(";
        ui->pushButton_lf->setText("(");
        data[ui->pushButton_rt] = ")";
        ui->pushButton_rt->setText(")");
        data[ui->pushButton_dot] = ".";
        ui->pushButton_dot->setText(".");

        data[ui->pushButton_root_2] = "√";
        ui->pushButton_root_2->setText("√");
    }
}

void MainWindow::handleConstButtonClick()
{
    constDialog_->show();
}

void MainWindow::handleModeButtonClick()
{
    bool flag = false;
    if (mode_state_ == ModeSimple) {
        mode_state_ = ModeAdvance;
        flag = true;
        ui->checkBox_sci->setChecked(true);
    } else {
        mode_state_ = ModeSimple;
        flag = false;
        ui->checkBox_sci->setChecked(false);
    }
    for (auto i = advanceWidgets.begin(); i != advanceWidgets.end(); ++i) {
        (*i)->setVisible(flag);
    }
}

void MainWindow::handleRFButton()
{
    ui->editArea->setText("flt[ans]");
    calc(true);
}

void MainWindow::handleHistoryButton()
{
    ui->historyList->setVisible(!ui->historyList->isVisible());
}

void MainWindow::handleUnitButton()
{
    unitDialog_->show();
}

void MainWindow::handleHistorySelect()
{
    QTextCursor temp = ui->editArea->textCursor();
    QModelIndex index = ui->historyList->currentIndex();
    temp.insertText("hist[" + QString::number(index.row()) + "]");
}

void MainWindow::handleConstSelect(const QString &name)
{
    QTextCursor temp = ui->editArea->textCursor();
    temp.insertText(name);
    ui->editArea->setTextCursor(temp);
}

void MainWindow::handleUnitConvertSelect(const QString &formula)
{
    calc();
    ui->editArea->setText(formula);
    calc();
}

void MainWindow::handleSciButtonStateChange()
{
    be.setSciFlt(ui->checkBox_sci->isChecked());
}

void MainWindow::displayResult(const std::string &str)
{
    QString toDisplay;
    int lw = 20;
    //    lw = ui->resultScrollArea->width() / 11 - 5;
    int cnt = 0;
    for (const char ch : str) {
        if (cnt % lw == 0 && cnt != 0) {
            toDisplay.append('\n');
        }
        toDisplay.append(ch);
        ++cnt;
    }
    ui->resultArea->setText(toDisplay);
    ui->resultArea->setMinimumHeight(15 * ceil((double) cnt / 20));
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
        } else if (ke->key() == Qt::Key_Shift) {
            handleShiftButtonClick();
            flag = true;
        }
        if (!ui->editArea->hasFocus()) {
            ui->editArea->setFocus();
            int k = ke->key();
            if (k >= 32 && k <= 126) {
                QTextCursor temp = ui->editArea->textCursor();
                temp.insertText(QString(static_cast<QChar>(k)).toLower());
            }
        }
        return flag;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(
        this,
        tr("about"),
        tr("<p><b>Scalculator</b>, simple but full-fledged calculator<br>"
           "with <b>Sevaluator</b> as backend to evaluate expressions.</p>"
           "<ul><li><a href='https://github.com/fpg2012/scalculator'> "
           "https://github.com/fpg2012/scalculator</a></li>"
           "<li><a "
           "href='https://github.com/fpg2012/sevaluator'>https://github.com/fpg2012/sevaluator</"
           "a></"
           "li></ul>"
           "Copyright nth233&lt;fpg2012@yeah.net&gt;, chikangxi&lt;chikangxi@hotmail.com&gt;, Meng "
           "Yuan 2021 "));
}

void MainWindow::showUsageDialog()
{
    QMessageBox::about(
        this,
        tr("Usage notes"),
        tr("Usage Notes:"
           "<ol>"
           "<li>shortcuts: enter '=', delete 'C', tab 'R->F', Shift '⇧'</li>"
           "<li>functions, such a <code>sin</code>, its parameters should be encapsulated in a "
           "pair of '[]'</li>"
           "<li>press 'History' button to show history list, history result would be inserted if "
           "you click any item in the list</li>"
           "<li>press 'Mode' button to show more advance buttons</li>"
           "<li>press '⇧' button to switch between <code>sin</code>, <code>asin</code> and "
           "<code>sec</code> </li>"
           "<li>big number is supported</li>"
           "<li>special functions, 'hist[n]' refers to (n-1)th historical result, 'ans' refers to "
           "the last result</li>"
           "<li>root[a, k] means the kth root of a</li>"
           "<li>press R->F to convert the result to float number instead of fractions</li>"
           "<li>rand[] or random[] function generates an float uniformly at random between 0 and "
           "1</li>"
           "<li>rnd[], ceil[] and floor[] round float to integer</li>"
           "<li>press 'ℂ' button to show constant table</li>"
           "</ol>"));
}
