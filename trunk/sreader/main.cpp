#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
#ifdef Q_WS_MAEMO_5
    w.setAttribute(Qt::WA_Maemo5AutoOrientation, true);
#endif

    w.show();
    return a.exec();
}
