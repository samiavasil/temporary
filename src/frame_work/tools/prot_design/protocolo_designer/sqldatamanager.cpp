#include "sqldatamanager.h"
#include <QTableView>
#include <QtSql>



typedef struct
{
    const char* name;
    const char* type;
}items_t;

const items_t net_table_items_names[] =
{
    {"ID", " integer primary key"},
    {"netName",  " varchar  NOT NULL UNIQUE"},
    {"netDescription",  " varchar"},
    {"CHECK(netName!='')",""}
};

const items_t node_table_items_names[] =
{
    {"ID",        " integer primary key" },
    {"nodeName",  " varchar NOT NULL UNIQUE"  },
    {"nodeDescription",  " varchar"},
    //{"netName",   " integer NOT NULL,  FOREIGN KEY(netName) REFERENCES Nets ( ID )" },
    //{"CHECK( nodeName!='' )","CONSTRAINT c1 UNIQUE (nodeName,netName)"},
};

const items_t packets_table_items_names[] = {
    {"ID",         " integer primary key"},
    {"packName",    " varchar NOT NULL UNIQUE" },
    {"packetDescription",  " varchar"},
    {"CHECK( packName!='')",""}
};

const items_t messages_table_items_names[] =
{
    {"ID",           " integer primary key"},
    {"msgName",      " varchar NOT NULL UNIQUE" },
    {"BitLen",       " integer"            },
    {"Type",         " integer"            },
    {"DefaultValue", " integer"            },
    {"msgDescription",  " varchar"},
    {"CHECK( msgName !='')",""}
};

const items_t net_to_node_map_table[] =
{
    {"ID",        " integer primary key"},
    {"netName" ,  " integer NOT NULL" },
    {"nodeName",  " integer NOT NULL" },
    {"FOREIGN KEY(netName) REFERENCES Nets ( ID )",  "FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )" },
};

const items_t packet_to_msg_map_table[] = {
    {"ID",         " integer primary key"},
    {"packName",   " integer NOT NULL" },
    {"msgPos",     " integer NOT NULL" },
    {"msgName",    " integer NOT NULL" },
    {"FOREIGN KEY(msgName) REFERENCES Messages ( ID )", "FOREIGN KEY(packName) REFERENCES Packets ( ID ) "},
    {"CONSTRAINT c1 UNIQUE (packName,msgPos)","CONSTRAINT c2 UNIQUE (packName,msgName)"},
   // {"CONSTRAINT c3 UNIQUE (msgName,msgPos)" ,""}
    {"CHECK( packName!='')","CHECK(msgPos >= 0)"}
};



const items_t node_to_pack_map_table[] =
{
    {"ID",        " integer primary key"},
    {"nodeName",  " integer NOT NULL" },
    {"packName",  " integer NOT NULL" },
    {"FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )",  "FOREIGN KEY(packName) REFERENCES Packets ( ID )" },

    {"CHECK( nodeName!='' )",""}
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
    },
    {
        "NetNodes",
        net_to_node_map_table,
        GET_ARREA_NUMS(net_to_node_map_table)
    },
    {
        "PacketsDesc",
        packet_to_msg_map_table,
        GET_ARREA_NUMS( packet_to_msg_map_table )
    },
    {
        "NodePacks",
        node_to_pack_map_table,
        GET_ARREA_NUMS( node_to_pack_map_table )
    }
};

#define EXEC_QUERY( x,y ) qDebug() << "Execute query " << y;\
    if( !(x).exec((y)) ){\
    qDebug() << (x).lastError().databaseText();\
    }



SqlDataManager::SqlDataManager(QObject *parent) :
    QObject(parent)
{
}

QSqlError SqlDataManager::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                        const QString &user, const QString &passwd, int port)
{

    QSqlError err;
    m_db = QSqlDatabase::addDatabase(driver);
    m_db.setDatabaseName(dbName);
    m_db.setHostName(host);
    m_db.setPort(port);
    if (!m_db.open(user, passwd)) {
        err = m_db.lastError();
        m_db = QSqlDatabase();
        qDebug() << err.databaseText();
    }
    else
    {
        qDebug() << "New conection to m_db: " << m_db;
    }
    createTables(m_db);
   // m_db.close();
    return err;
}


int SqlDataManager::createTable( QSqlDatabase& db, const table_desc_t* desc )
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

int SqlDataManager::createTables( QSqlDatabase& db )
{
    //db = QSqlDatabase::database();/*TODO: Add connection name*/

    QSqlQuery q("", db);
    //  q.exec("drop table Movies");
    // q.exec("drop table Packets");

    EXEC_QUERY(q,"PRAGMA foreign_keys = ON");

    //TODO DELL ME

    EXEC_QUERY( q,"drop table PacketsDesc");
    EXEC_QUERY( q,"drop table NodePacks");
    EXEC_QUERY( q,"drop table NetNodes");
    EXEC_QUERY( q,"drop table Packets");
    EXEC_QUERY( q,"drop table Messages");

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




//TODO fix these to be created automaticaly from structures
void SqlDataManager::initializeModel( SqlDataManager::sqlTablesTypes_t type, const QString& querry, QTableView *table )
{
    if( NULL == table )
    {
        qDebug() << "Incorrect input parameters";
        return;
    }
    if( 0 >= QSqlDatabase::connectionNames().count() )
    {
        qDebug() << "Not connected db";
        return;
    }

    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(table);
    if( NULL == model && eENUM_NUMBER <= type )
    {
        return;
    }

    model->setTable( tables_descriptors[ type ].name );
    model->setEditStrategy(QSqlRelationalTableModel::OnRowChange);
    //table->setColumnHidden(0,false);
    switch(type)
    {
    case eNET     :
    {
        //            if( !querry.isNull() )
        //            {
        //                    model->setFilter ( tr("Nets.netName = '%1'").arg(querry) );
        //            }
        break;
    }
    case eNODE    :
    {
        if( !querry.isNull() )
        {
            QString str = tr("NetNodes.netName == ( select ID from Nets where netName == '%1' ) ").arg(querry);
            qDebug() << str;
            model->setFilter ( str );
        }
        break;
    }
    case ePACKET  :
    {
        if( !querry.isNull() )
        {
            model->setFilter ( QString("Packets.packName = '%1'").arg(querry) );
        }
        break;
    }
    case eNETNODES:
    {
        if( !querry.isNull() )
        {
            QString str = tr("NetNodes.netName == ( select ID from Nets where netName == '%1' ) ").arg(querry);
            qDebug() << str;
            model->setFilter ( str );
        }
        model->setRelation( 1, QSqlRelation( "Nets" , "ID", "netName") );
        model->setRelation( 2, QSqlRelation( "Nodes", "ID", "nodeName") );
        break;
    }
    case eNODEPACKS:
    {
        if( !querry.isNull() )
        {
            QString str = tr("NodePacks.nodeName == ( select ID from Nodes where nodeName == '%1' ) ").arg(querry);
            qDebug() << str;
            model->setFilter ( str );
        }
        model->setRelation( 1, QSqlRelation( "Nodes", "ID", "nodeName") );
        model->setRelation( 2, QSqlRelation( "Packets", "ID", "packName") );
        break;
    }
    case ePACKETDESC:
    {
        if( !querry.isNull() )
        {
            QString str = tr("PacketsDesc.packName == ( select ID from Packets where packName == '%1' ) ").arg(querry);
            qDebug() << str;
            model->setFilter ( str );
            //model->setQuery("select packName from PacketsDesc");
        }
        model->setRelation( 1, QSqlRelation( "Packets", "ID", "packName") );
        model->setRelation( 3, QSqlRelation( "Messages","ID", "msgName") );
        break;
    }
    case eMESSAGES:
    {
        if( !querry.isNull() )
        {
            model->setFilter ( QString("Messages.msgName = '%1'").arg(querry) );
        }
        break;
    }
    default:
    {
    }
    }
    model->select();

    if (model->lastError().type() != QSqlError::NoError)
        qDebug() << model->lastError().text();
    QItemSelectionModel *m = table->selectionModel();
    table->setModel(model);
    if (model->lastError().type() != QSqlError::NoError)
        qDebug() << model->lastError();
    else if (model->query().isSelect())
        qDebug() << "Query OK.";
    else
        qDebug() << tr("Query OK, number of affected rows: %1").arg(
                        model->query().numRowsAffected());
    delete m;
    table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
}

void SqlDataManager::insertRow( QTableView* table)
{
#if 1
    if( !table )
    {
        qDebug()<< "Wrong input params: Can't insert row";
        return;
    }
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(table->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return;
    }
    QModelIndex insertIndex = table->currentIndex();
    QSqlRecord newRecord = model->record();
    int row = insertIndex.row();
    QString st_name = newRecord.fieldName( 1 );
    if( row == -1 )
    {
       row = 0;
    }
    else
    {
       row = insertIndex.row();
    }

    if( 0 < model->rowCount() )
    {
      QSqlRecord last_record;
      last_record = model->record( model->rowCount()-1 );
      st_name.append( last_record.field(0).value().toString() );
    }


    newRecord.setValue( 1, st_name );
    newRecord.remove(0);
    if( model->insertRow(row) )
    {
        insertIndex = model->index(row, 1);
        if( !model->setRecord( row, newRecord ) )
        {
            qDebug() << model->lastError();
        }
        table->setCurrentIndex(insertIndex);
        table->edit(insertIndex);

    }
    else
    {
        qDebug() << model->lastError();
    }
#else
   table->setSortingEnabled(false);
     /*table->blockSignals( true );*/
    if( !table )
    {
        qDebug()<< "Wrong input params: Can't insert row";
        return;
    }
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(table->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return;
    }
    QModelIndex insertIndex = table->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    //if( model->insertRow(row) )
    QSqlRecord newRecord = model->record();
    newRecord.setValue( 1, tr("Name%1").arg(model->rowCount()) );
    newRecord.remove(0);

    //if( model->insertRecord(row, newRecord) )
     if( model->insertRow(row) )
    {

        insertIndex = model->index(row, 1);

        if( !model->setRecord( row, newRecord ) )
        {
            qDebug() << model->lastError();
        }
      //  model->setData( insertIndex, tr("Name%1").arg(model->rowCount()));
        table->setCurrentIndex(insertIndex);
       table->edit(insertIndex);
    }
    else
    {
        qDebug() << model->lastError();
    }
//  table->blockSignals( false );
  //table->setSortingEnabled(true);
#endif
}

void SqlDataManager::deleteRow( QTableView* table )
{
    if( !table )
    {
        qDebug()<< "Wrong input params: Can't delete row";
        return;
    }
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(table->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return;
    }

    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    QModelIndexList currentSelection = table->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        model->removeRow(currentSelection.at(i).row());
    }
    if( ! model->submitAll() )
    {
        qDebug() << model->lastError();
    }

    model->setEditStrategy(QSqlRelationalTableModel::OnRowChange);

}
