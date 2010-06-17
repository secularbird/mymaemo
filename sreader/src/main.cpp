#include <QtGui/QApplication>
#include "mainwindow.h"
#include "system.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(system::applicationName);
    a.setOrganizationName(system::organizationName);

    MainWindow w;
    w.setAttribute(Qt::WA_Maemo5AutoOrientation, true);
    w.show();
    return a.exec();
}
