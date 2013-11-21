#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsqlconnectiondialog.h"
#include<QString>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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

    QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                                  dialog.userName(), dialog.password(), dialog.port());
    if (err.type() != QSqlError::NoError)
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                     "opening the connection: ") + err.text());

}

QSqlError MainWindow::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                    const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("Browser%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("Browser%1").arg(cCount));
        qDebug() << err.databaseText();
    }
    else
    {
        qDebug() << "New conection to db: " << db;
    }
    createTables(db);
    showTable( ePACKET );
    //  db.close();
    return err;
}



const char* tables[ eENUM_NUMBER ]={
    "Nets",
    "Nodes",
    "Packets",
    "Messages"
};

typedef struct
{
    const char* name;
    const char* type;
}items_t;

const items_t net_table_items_names[] =
{
    {"ID", " integer primary key"},
    {"netName",  " varchar  NOT NULL UNIQUE"},
    {"CHECK(netName!='')",""}
};

const items_t node_table_items_names[] =
{
    {"ID",        " integer primary key" },
    {"nodeName",  " varchar NOT NULL UNIQUE"  },
    {"netName",   " INTEGER NOT NULL,  FOREIGN KEY(netName) REFERENCES Nets ( ID )" },
    {"CHECK( nodeName!='' )",""}
};


const items_t packets_table_items_names[] = {
    {"ID",         " integer primary key"},
    {"packName",   " varchar NOT NULL UNIQUE" },
    {"Messages",   " integer"            },
    {"nodeName",   " INTEGER NOT NULL,  FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )" },
    {"CHECK( packName!='')",""}
};

const items_t messages_table_items_names[] =
{
    {"ID",           " integer primary key"},
    {"msgName",      " varchar NOT NULL UNIQUE" },
    {"BitLen",       " integer"            },
    {"Type",         " integer"            },
    {"DefaultValue", " integer"            },
    {"CHECK( msgName !='')",""}
  /*{"packName",     " INTEGER,  FOREIGN KEY(packName) REFERENCES Packets ( ID )" }*/
};



struct table_desc_
{
public:
    const char* name;
    const items_t * const table_items_names;
    int items_count;
} ;

#define GET_ARREA_NUMS( x )  ((int)(sizeof(x)/sizeof(x[0])))

const table_desc_t tables_descriptors[] =
{
    {
        "Nets",
        net_table_items_names,
        GET_ARREA_NUMS( net_table_items_names )
    },
    {
        "Nodes",
        node_table_items_names,
        GET_ARREA_NUMS( node_table_items_names )
    },
    {
        "Packets",
        packets_table_items_names,
        GET_ARREA_NUMS( packets_table_items_names )
    },
    {
        "Messages",
        messages_table_items_names,
        GET_ARREA_NUMS( messages_table_items_names )
    }
};

#define EXEC_QUERY( x,y ) qDebug() << "Execute query " << y;\
    if( !(x).exec((y)) ){\
    qDebug() << (x).lastError().databaseText();\
    }


//TODO fix these to be created automaticaly from structures
void initializeModel( column_t type, QSqlRelationalTableModel *model )
{
    if( NULL == model && eENUM_NUMBER <= type)
    {
        return;
    }

    model->setTable( tables[ type ] );
    model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);

    switch(type)
    {
        case eNET     :
        {
            break;
        }
        case eNODE    :
        {
            model->setRelation( 2, QSqlRelation( tables[eNET], "ID", "netName") );
            break;
        }
        case ePACKET  :
        {
            model->setRelation( 3, QSqlRelation( tables[eNODE], "ID", "nodeName") );
            break;
        }
        case eMESSAGES:
        {
          //  model->setRelation( 5, QSqlRelation( tables[ePACKET], "ID", "packName") );
            break;
        }
        default:
        {
        }
    }
    model->select();

#if 0
    model->setTable("employee");

    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    model->setRelation(2, QSqlRelation("city", "id", "name"));
    model->setRelation(3, QSqlRelation("country", "id", "name"));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));

    model->select();
#endif

}






void MainWindow::showTable( column_t type )
{
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::connectionNames()[QSqlDatabase::connectionNames().count()-1]);
    QSqlQuery q("", db);
  //  EXEC_QUERY(q,"PRAGMA foreign_keys = ON");

    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(ui->tableView, db);

    initializeModel( type, model );

    if (model->lastError().type() != QSqlError::NoError)
        qDebug() << model->lastError().text();
    QItemSelectionModel *m = ui->tableView->selectionModel();
    ui->tableView->setModel(model);
    if (model->lastError().type() != QSqlError::NoError)
        qDebug() << model->lastError();
    else if (model->query().isSelect())
        qDebug() << "Query OK.";
    else
        qDebug() << tr("Query OK, number of affected rows: %1").arg(
                           model->query().numRowsAffected());

    delete m;
    QAbstractItemDelegate* itemDel = ui->tableView->itemDelegate();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    delete itemDel;
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
}


int MainWindow::createTable( QSqlDatabase& db, const table_desc_t* desc )
{
    qDebug()<<"Connection names:"<<QSqlDatabase::connectionNames();
    QSqlQuery q("", db);
    qDebug()<<"Used connection"<<db.connectionName();
    QString str(tr("create table %1 (").arg( desc->name ));
    for(int i=0; i< desc->items_count; i++)
    {
        str.append(tr("%1 %2").arg(desc->table_items_names[i].name).arg(desc->table_items_names[i].type));
        if( i < desc->items_count - 1 )
            str.append(",");
    }
    str.append(")");
    EXEC_QUERY(q, str);
    return 0;
}

int MainWindow::createTables( QSqlDatabase& db )
{
    //db = QSqlDatabase::database();/*TODO: Add connection name*/

    QSqlQuery q("", db);
    //  q.exec("drop table Movies");
    // q.exec("drop table Packets");

    EXEC_QUERY(q,"PRAGMA foreign_keys = ON");

   //TODO DELL ME



    EXEC_QUERY( q,"drop table Messages");
    EXEC_QUERY( q,"drop table Packets");
    EXEC_QUERY( q,"drop table Nodes");
    EXEC_QUERY( q,"drop table Nets");

    for( int i=0; i < GET_ARREA_NUMS(tables_descriptors); i++ )
    {
        if( db.tables().contains( tables_descriptors[i].name ) )
        {
            qDebug() << "DB contains table: " << tables_descriptors[i].name << "\n        check for valid items";
            QSqlRecord rec = db.record( tables_descriptors[i].name );
            if( rec.count() !=  tables_descriptors[i].items_count )
            {
                EXEC_QUERY( q,tr("drop table %1").arg(tables_descriptors[i].name) );/*TODO: here can try merge if have a need*/
                if( q.lastError().type() == QSqlError::NoError )
                {
                    if( createTable( db, &tables_descriptors[i] ) )
                    {
                        qDebug() << "Can't restore table: " << tables_descriptors[i].name;
                        return 1;
                    }
                    continue;
                }
                else
                {
                    qDebug() << "Can't restore table: " << tables_descriptors[i].name;
                    return 1;
                }
            }
            else
            {
                QSqlRecord rec = db.record( tables_descriptors[i].name );
                bool Ok = true;
                for( int j = 0;j < tables_descriptors[i].items_count; j++ )
                {
                    if( !rec.contains( tables_descriptors[i].table_items_names[j].name ) )
                    {
                        Ok = false;
                        break;
                    }
                }
                if( !Ok )
                {
                    if( createTable( db, &tables_descriptors[i] ) )
                    {
                        qDebug() << "Can't restore table: " << tables_descriptors[i].name;
                        return 1;
                    }
                    continue;
                }
            }

        }
        else
        {
            qDebug() << "DB create new table: " << tables_descriptors[i].name;
            if( createTable( db, &tables_descriptors[i] ) )
            {
                qDebug() << "Can't restore table: " << tables_descriptors[i].name;
                return 1;
            }
            continue;
        }
    }
    return 0;

}

const char* table1[ eENUM_NUMBER ]={
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
    eENUM_NUMBER*/

    QString type( item->data(1,0).toString());
    for(int i=eNET; i<eENUM_NUMBER; i++ )
    {
        if( !qstrcmp( type.toAscii().constData(), table1[ i ]) )
        {
            showTable( (column_t)i );
            break;
        }
    }

}

void MainWindow::insertRow()
{
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(ui->tableView->model());
    if (!model)
        return;

    QModelIndex insertIndex = ui->tableView->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    if( model->insertRow(row) )
    {
        insertIndex = model->index(row, 0);
        ui->tableView->setCurrentIndex(insertIndex);
        ui->tableView->edit(insertIndex);
    }
    else
    {
        qDebug() << model->lastError();
    }
}

void MainWindow::deleteRow()
{
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(ui->tableView->model());
    if (!model)
        return;

    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    QModelIndexList currentSelection = ui->tableView->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        model->removeRow(currentSelection.at(i).row());
    }
    if( ! model->submitAll() )
    {
       qDebug() << model->lastError();
    }

    model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);

}
