#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/font/jbmono.ttf");
    MainWindow w;
    w.show();
    QDesktopWidget *temp = QApplication::desktop();
    w.move(temp->width() / 5, temp->height() / 5);
    return a.exec();
}
