#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QFontDatabase>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/font/jbmono.ttf");

    QTranslator trans;
    trans.load(":/lang/zh_CN.qm");
    QLocale locale;
    qDebug() << locale;
    if (locale.language() == QLocale::Chinese) {
        QCoreApplication::installTranslator(&trans);
        qDebug() << "language changed";
    }

    MainWindow w;
    w.show();
    QDesktopWidget *temp = QApplication::desktop();
    w.move(temp->width() / 5, temp->height() / 5);
    return a.exec();
}
