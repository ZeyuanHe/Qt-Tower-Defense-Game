#include "mainwindow.h"
#include <QApplication>
#include "globals.h"

int globalMoney = 1000;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
