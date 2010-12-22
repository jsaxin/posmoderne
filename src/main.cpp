#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Unithorpe");
    QCoreApplication::setOrganizationDomain("unithorpe.org");
    QCoreApplication::setApplicationName("posmoderne");

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
