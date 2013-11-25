#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsqlconnectiondialog.h"
#include<QString>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),data_manager(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->addAction(ui->insertRowAction);
    ui->tableView->addAction(ui->deleteRowAction);
    ui->insertRowAction->setEnabled(1);
    ui->deleteRowAction->setEnabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNewProject_triggered()
{
    QSqlConnectionDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QSqlError err = data_manager.addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                                  dialog.userName(), dialog.password(), dialog.port());
    if (err.type() != QSqlError::NoError)
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                     "opening the connection: ") + err.text());

}


void MainWindow::showTable( SqlDataManager::sqlTablesTypes_t type, QString &q )
{
    data_manager.initializeModel( type,q, ui->tableView );
}


//TODO: DELL ME FIX ME
const char* table1[ SqlDataManager::eENUM_NUMBER ]={
    "Net",
    "Node",
    "Packet",
    "Message"
};

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    QTreeWidgetItem* item =  ui->treeWidget->currentItem();
    /*
    eNET,
    eNODE,
    ePACKET,
    eMESSAGES,
    eENUM_NUMBER
    */

    QString type( item->data(1,0).toString());
    for(int i=SqlDataManager::eNET; i<SqlDataManager::eENUM_NUMBER; i++ )
    {
        if( !qstrcmp( type.toAscii().constData(), table1[ i ]) )
        {
            QString q = item->data(0,0).toString();
            showTable( (SqlDataManager::sqlTablesTypes_t)i , q);
            break;
        }
    }

}


void MainWindow::insertRow()
{
    data_manager.insertRow( ui->tableView );
}

void MainWindow::deleteRow()
{
    data_manager.deleteRow( ui->tableView );
}
