#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setAttribute(Qt::WA_Maemo5AutoOrientation, true);
    w.show();
    return a.exec();
}
