#include <QtGui/QApplication>
#include "mainwindow.h"
#include"docwriter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    delete ( new DocWriter() );
    return a.exec();
}
