#include "backtestwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BacktestWidget w;
    w.show();
    return a.exec();
}
