#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsqlconnectiondialog.h"
#include<QString>
#include <QtSql>
#define ID_TREE_INVALID  (-1)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),data_manager(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->addAction(ui->insertRowAction);
    ui->tableView->addAction(ui->deleteRowAction);
    ui->insertRowAction->setEnabled(1);
    ui->deleteRowAction->setEnabled(1);
    QAbstractItemDelegate* itemDel = ui->tableView->itemDelegate();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->horizontalHeader()->setStretchLastSection( true );

    delete itemDel;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem* createTreeWidgetItem( const QStringList& name, SqlDataManager::sqlTablesTypes_t type, int sub_item_id = ID_TREE_INVALID )
{
    QTreeWidgetItem* item = new QTreeWidgetItem( name, (int)type );
    if( item )
    {
        item->setData( 0, Qt::UserRole, sub_item_id );
        switch( type )
        {
        case SqlDataManager::eNET     :
        {
            item->setIcon(0,QIcon( "icons/net.png" ));
            break;
        }
        case SqlDataManager::eNODE    :
        {
            item->setIcon(0,QIcon( "icons/node.png" ));
            break;
        }
        case SqlDataManager::ePACKET  :
        {
            item->setIcon(0,QIcon( "icons/packet.png" ));
            break;
        }
        case SqlDataManager::eMESSAGES:
        {
            item->setIcon(0,QIcon( "icons/message.png" ));
            break;
        }
        case SqlDataManager::eNETNODES:
        {
            item->setIcon(0,QIcon( "icons/net.png" ));
            break;
        }

        case SqlDataManager::eNODEPACKS:
        {
            item->setIcon(0,QIcon( "icons/node.png" ));
            break;
        }
        case SqlDataManager::ePACKETDESC:
        {
            item->setIcon(0,QIcon( "icons/packet.png" ));
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return item;
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
    ui->treeWidget->blockSignals(true);
    ui->treeWidget->clear();//FIX ME
    //TODO load db
    QTreeWidgetItem* item = createTreeWidgetItem( QStringList("Networks"), SqlDataManager::eNET );
    ui->treeWidget->insertTopLevelItem( 0, item );

    item = createTreeWidgetItem( QStringList("Nodes"),    SqlDataManager::eNODE );
    ui->treeWidget->insertTopLevelItem( 1, item );

    item = createTreeWidgetItem( QStringList("Packets"),  SqlDataManager::ePACKET );
    ui->treeWidget->insertTopLevelItem( 2, item );

    item = createTreeWidgetItem( QStringList("Messages"), SqlDataManager::eMESSAGES );
    ui->treeWidget->insertTopLevelItem( 3, item );
    ui->treeWidget->blockSignals(false);
}


void MainWindow::showTable( SqlDataManager::sqlTablesTypes_t type, const QString &q )
{
    switch( type )
    {
    case SqlDataManager::eNET     :
    {
        ui->labelView->setText("Nets");
        break;
    }
    case SqlDataManager::eNODE    :
    {
        ui->labelView->setText("Nodes");
        break;
    }
    case SqlDataManager::ePACKET  :
    {
        ui->labelView->setText("Packets");
        break;
    }
    case SqlDataManager::eMESSAGES:
    {
        ui->labelView->setText("Messages description");
        break;
    }
    case SqlDataManager::eNETNODES:
    {
        ui->labelView->setText("Nodes on Net description");
        break;
    }

    case SqlDataManager::eNODEPACKS:
    {
        ui->labelView->setText("Packets in Node description");
        break;
    }
    case SqlDataManager::ePACKETDESC:
    {
        ui->labelView->setText("Packets description");
        break;
    }
    default:
    {
        ui->labelView->setText("Slect from tree");
        break;
    }
    }
    data_manager.initializeModel( type,q, ui->tableView );
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(ui->tableView->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return;
    }
    m_filter = model->filter();
    on_actionToggleFilter_toggled( ui->actionToggleFilter->isChecked() );
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
    QTreeWidgetItem* cur_item =  ui->treeWidget->currentItem();
    colum_cfg_t cm;
    QList< colum_cfg_t > list;
    /*Fill columns with default values.. set visibilities */
    switch( cur_item->type() )
    {
    case SqlDataManager::ePACKETDESC:
    case SqlDataManager::eNODEPACKS:
    case SqlDataManager::eNETNODES:
    {
        cm.coll = 1;
        cm.default_value = cur_item->data( 0, Qt::UserRole).toInt();//cur_item->text(0);
        cm.hide = 1;
        list.append(cm);
        break;
    }
    default:{
        break;
    }

    }
    data_manager.insertRow( ui->tableView, list );
}

void MainWindow::deleteRow()
{
    data_manager.deleteRow( ui->tableView );
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QTreeWidgetItem* item =  ui->treeWidget->currentItem();

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
    if( ui->tableView->model() )
    {
        for( int i = 0; i < ui->tableView->model()->columnCount(); i++ )
        {
            ui->tableView->resizeColumnToContents(i);
        }
    }
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
    QTreeWidgetItem* cur_item =  ui->treeWidget->currentItem();
    if( cur_item )
    {
        updateTreeSubitems( cur_item );

        for( int i=0; i < cur_item->childCount();i++ )
        {
            updateTreeSubitems(cur_item->child(i));
        }
    }
}


void MainWindow::updateTreeSubitems( QTreeWidgetItem* item )
{
#if 1
    SqlDataManager::sqlTablesTypes_t sub_item_type = SqlDataManager::eENUM_NUMBER;
    QString querry;
    QString field_name;
    int sub_item_id = ID_TREE_INVALID;
    if( NULL == item )
    {
        return;
    }
    switch( item->type() )
    {
    case SqlDataManager::eNET     :
    {
        field_name = "netName";
        querry = QString("select ID,%1 from Nets").arg(field_name);
        sub_item_type = SqlDataManager::eNETNODES;
        break;
    }
    case SqlDataManager::eNODE    :
    {
        field_name = "nodeName";
        querry = QString("select ID,%1 from Nodes ").arg(field_name);
        sub_item_type = SqlDataManager::eNODEPACKS;
        break;
    }
    case SqlDataManager::ePACKET  :
    {
        field_name = "packName";
        querry = QString("select ID,%1 from Packets").arg(field_name);
        sub_item_type = SqlDataManager::ePACKETDESC;
        break;
    }
    case SqlDataManager::eMESSAGES:
    {
        if( NULL == item->parent() )
        {
            field_name = "msgName";
            querry =  QString("select ID,%1 from Messages").arg(field_name);
            sub_item_type = SqlDataManager::eMESSAGES;
        }
        break;
    }
    case SqlDataManager::eNETNODES:
    {
        field_name = "nodeName";
        querry = QString("select ID,%1 from Nodes where ID in (select %1 from NetNodes where netName in (select ID from Nets where netName == '%2'))").arg(field_name).arg( item->text(0) );
        sub_item_type = SqlDataManager::eNODEPACKS;
        break;
    }

    case SqlDataManager::eNODEPACKS:
    {
        field_name    = "packName";
        querry        = QString("select ID,%1 from Packets where ID in (select %1 from NodePacks where nodeName in (select ID from Nodes where nodeName == '%2'))").arg(field_name).arg( item->text(0) );
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

    if( sub_item_type != SqlDataManager::eENUM_NUMBER )
    {
        QTreeWidgetItem* sub_item;
        QStringList  sub_item_name;
        QSqlQuery q( querry );
        qDebug() << "QUERRY: "<< querry;
        if( q.exec()  )
        {

            QSqlRecord record;
            deleteChildItems( item );
            while( q.next() )
            {
                record = q.record();
                sub_item_name.clear();
                sub_item_name << record.field(field_name).value().toString();
                sub_item_id = record.field("ID").value().toInt();
                sub_item = createTreeWidgetItem( sub_item_name, sub_item_type, sub_item_id );
                item->addChild(sub_item);
            }
            q.finish() ;
            while( q.isActive() );
        }
    }
#endif
}


void MainWindow::on_actionToggleFilter_toggled( bool arg1 )
{
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(ui->tableView->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return;
    }
    if( arg1 )
    {
        model->setFilter("");
    }
    else
    {
        model->setFilter( m_filter );
    }
}
