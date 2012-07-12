#include <QtGui/QApplication>
#include "mainwindow.h"
#include "qt/QCommandExecutor.h"
#include "qt/QCommand.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QCommandExecutor exec;
    QCommand* comm = new QCommand(NULL);
    exec.appendCommand(comm);
    exec.startExecution(true);
    return a.exec();
}
