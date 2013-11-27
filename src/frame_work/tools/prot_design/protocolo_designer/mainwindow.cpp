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
    ui->treeWidget->clear();
    //TODO load db
    QTreeWidgetItem* item = new QTreeWidgetItem( QStringList("Networks"), (int)SqlDataManager::eNET );

    ui->treeWidget->insertTopLevelItem( 0, item );
    item = new QTreeWidgetItem( QStringList("Packets"), (int)SqlDataManager::ePACKET );

    ui->treeWidget->insertTopLevelItem( 1, item );
    item = new QTreeWidgetItem( QStringList("Messages"), (int)SqlDataManager::eMESSAGES );
    ui->treeWidget->insertTopLevelItem( 2, item );
}


void MainWindow::showTable( SqlDataManager::sqlTablesTypes_t type, const QString &q )
{

    data_manager.initializeModel( type,q, ui->tableView );
    connect( ui->tableView->model(), SIGNAL(rowsInserted ( const QModelIndex &, int, int)),this, SLOT(tableRowsInserted ( const QModelIndex &, int, int)) );
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

}


void MainWindow::insertRow()
{
    data_manager.insertRow( ui->tableView );
}

void MainWindow::deleteRow()
{
    data_manager.deleteRow( ui->tableView );
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QTreeWidgetItem* item =  ui->treeWidget->currentItem();
    /*
    eNET,
    eNODE,
    ePACKET,
    eMESSAGES,
    eENUM_NUMBER
    */

    if( item == NULL || item->type() >= SqlDataManager::eENUM_NUMBER )
    {
        qDebug() << "Invalid tree widged data";
        return;
    }
    QString str;
    if( item->parent() )
    {
        str = item->text(0);
    }
    showTable( (SqlDataManager::sqlTablesTypes_t)item->type() ,str );
    m_cur_view_type  = (SqlDataManager::sqlTablesTypes_t)item->type();
    m_cur_view_query = str;
    qDebug() << "m_cur_view_type: "<< m_cur_view_type<< " ....... " << "m_cur_view_query: " << m_cur_view_query;
}

void deleteItems( QTreeWidgetItem* item )
{
    if( item )
    {
        while( item->childCount() )
        {
            deleteItems( item->child(0) );
        }
        item->parent()->removeChild(item);
        delete item;
    }
}

void deleteChildItems( QTreeWidgetItem* item )
{
    if( item )
    {
        while( item->childCount() )
        {
            deleteItems( item->child(0) );
        }
    }
}

int findColumnIndex( QAbstractItemModel * model, const QModelIndex & parent, QString& name )
{
    int ret = -1;
    if( !model )
    {
        return ret;
    }
    int c_cnt = model->columnCount ( parent );

    for( int i = 0; i < c_cnt; i++ )
    {
        if( name == model->headerData( i , Qt::Horizontal ).toString() )
        {
            ret = i;
            break;
        }
    }

    return ret;
}

void MainWindow::tableRowsInserted ( const QModelIndex & parent, int start, int end )
{
    SqlDataManager::sqlTablesTypes_t sub_item_type = SqlDataManager::eMESSAGES;
    QStringList  sub_item_name;
    QString model_column_name;
    qDebug() << "Inserted rows: " << start << " - " << end;
    QTreeWidgetItem* cur_item =  ui->treeWidget->currentItem();
    QAbstractItemModel * model = ui->tableView->model();
    bool update_tree = false;
    deleteChildItems( cur_item );

    if( m_cur_view_type != cur_item->type() )
    {
        qDebug() << "Incorect: m_cur_view_type != row_type ";
        return;
    }
    switch( cur_item->type() )
    {
    case SqlDataManager::eNET     :
    {
        //sub_item_name << "Nets";
        update_tree   = true;
        model_column_name = "netName";
        sub_item_type = SqlDataManager::eNODE;
        break;
    }
    case SqlDataManager::eNODE    :
    {
        update_tree   = true;
        model_column_name = "nodeName";
        sub_item_type = SqlDataManager::eNODEPACKS;
        break;
    }
    case SqlDataManager::ePACKET  :
    {
        update_tree   = true;
        model_column_name = "packName";
        sub_item_type = SqlDataManager::ePACKETDESC;
        break;
    }
    case SqlDataManager::eMESSAGES:
    {
        model_column_name = "msgName";
        if( m_cur_view_query.isNull() )
        {
            update_tree   = true;
        }
        break;
    }
    case SqlDataManager::eNODEPACKS:
    {
        update_tree   = true;
        model_column_name = "packName";
        sub_item_type = SqlDataManager::ePACKETDESC;
        break;
    }
    case SqlDataManager::ePACKETDESC:
    {
        break;
    }
    default:
    {
        qDebug() << "File: " << __FILE__ "Line " << __LINE__ << "Wrong table type";
    }
    }

    if( update_tree )
    {
        int c_idx = findColumnIndex( model, parent, model_column_name );

        if( 0 <= c_idx )
        {
            QTreeWidgetItem* item;
            QModelIndex id;
            for( int i = start; i <= end; i++ )
            {
                sub_item_name.clear();

                id = model->index( i, c_idx, parent );
                sub_item_name << id.data().toString();
                item = new QTreeWidgetItem( sub_item_name, (int)sub_item_type );
                cur_item->addChild(item);
            }
        }
    }

}


