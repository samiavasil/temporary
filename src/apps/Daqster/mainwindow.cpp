#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaces.h"
#include"QFrameWork.h"
#include"PluginList.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    PluginList pList(this);
    //if( QDialog::Accepted == pList.exec() )
    {
        qDebug("%d", pList.exec());
    }
}
