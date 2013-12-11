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
    {"ID",            " integer primary key"         },
    {"msgName",        " varchar NOT NULL UNIQUE"    },
    {"BitLen",         " integer NOT NULL" },
    {"Type",           " integer NOT NULL"       },
    {"DefaultValue",   " integer NOT NULL"       },
    {"msgDescription", " varchar"},
    {"CHECK( msgName !='')",""}
};

const items_t net_to_node_map_table[] =
{
    {"ID",        " integer primary key"},
    {"netName" ,  " integer NOT NULL" },
    {"nodeName",  " integer NOT NULL" },
    {"FOREIGN KEY(netName) REFERENCES Nets ( ID )",  "FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )" },
    {"CONSTRAINT c1 UNIQUE (netName,nodeName)",""},
};

const items_t packet_to_msg_map_table[] = {
    {"ID",         " integer primary key"},
    {"packName",   " integer NOT NULL" },
    {"msgPos",     " integer NOT NULL" },
    {"msgName",    " integer NOT NULL" },
    {"FOREIGN KEY(msgName) REFERENCES Messages ( ID )", "FOREIGN KEY(packName) REFERENCES Packets ( ID ) "},
    {"CONSTRAINT c1 UNIQUE (packName,msgPos)","CONSTRAINT c2 UNIQUE (packName,msgName)"},
    {"CHECK( packName!='')","CHECK(msgPos >= 0)"}
};




const items_t node_to_pack_map_table[] =
{
    {"ID",        " integer primary key"},
    {"nodeName",  " integer NOT NULL" },
    {"packName",  " integer NOT NULL" },
    {"FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )",  "FOREIGN KEY(packName) REFERENCES Packets ( ID )" },
    {"CHECK( nodeName!='' )","CONSTRAINT c1 UNIQUE (nodeName,packName)"}
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


SqlDataManager* SqlDataManager::m_this;

SqlDataManager::SqlDataManager(QObject *parent) :
    QObject(parent)
{
}

SqlDataManager* SqlDataManager::Instance()
{
    if( NULL == m_this )
    {
        m_this = new SqlDataManager( NULL );
    }
    return m_this;
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

//    EXEC_QUERY( q,"drop table PacketsDesc");
//    EXEC_QUERY( q,"drop table NodePacks");
//    EXEC_QUERY( q,"drop table NetNodes");
//    EXEC_QUERY( q,"drop table Packets");
//    EXEC_QUERY( q,"drop table Messages");

//    EXEC_QUERY( q,"drop table Nodes");
//    EXEC_QUERY( q,"drop table Nets");


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
    QList<int> col_hide;
    col_hide << 0;
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

    switch(type)
    {
    case eNET     :
    {

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
     //   model->setRelation( 1, QSqlRelation( "Nets" , "ID", "netName") );
        model->setRelation( 2, QSqlRelation( "Nodes", "ID", "nodeName") );
        col_hide << 1;//TODO ADD DEFAULT
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
      //  model->setRelation( 1, QSqlRelation( "Nodes", "ID", "nodeName") );
        model->setRelation( 2, QSqlRelation( "Packets", "ID", "packName") );
        col_hide << 1;//TODO ADD DEFAULT
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
      //  model->setRelation( 1, QSqlRelation( "Packets", "ID", "packName") );
        model->setRelation( 3, QSqlRelation( "Messages","ID", "msgName") );
        col_hide << 1;//TODO ADD DEFAULT
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

    for( int i=0; i < model->columnCount(); i++ )
    {
      table->setColumnHidden( i, false );
    }

    for( int i=0; i < col_hide.count(); i++ )
    {
      table->hideColumn(col_hide.value(i,-1));
    }
}

int SqlDataManager::insertRow( QTableView* table, QList<colum_cfg_t>& c_list )
{
    if( !table )
    {
        qDebug()<< "Wrong input params: Can't insert row";
        return -1;
    }
    QSqlRelationalTableModel *model = qobject_cast<QSqlRelationalTableModel *>(table->model());
    if (!model)
    {
        qDebug()<< "Error: Can't get QSqlRelationalTableModel for table";
        return -1;
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


    int insert_id = 1;
    if( c_list.count() )
    {
       colum_cfg_t val = c_list.value(0);
       qDebug() << newRecord.field(val.coll).value( ).toString();
       qDebug() << newRecord.field(val.coll).value( ).toInt();
       qDebug() << newRecord.field(val.coll).value( ).type();
       qDebug() << newRecord.field(val.coll).isReadOnly();
       newRecord.setValue(val.coll, val.default_value );
       qDebug() << newRecord.field(val.coll).value( ).toInt();
       insert_id = 2;
    }
    else
    {
        newRecord.setValue( 1, st_name );
    }
    /*!!!! First columns in tables are Autoincremented primary keys..
    To work corectly autoincrementing first column in record shoud be cleared.*/
    newRecord.remove(0);
    if( model->insertRow(row) )
    {
        insertIndex = model->index( row, insert_id );
        if( !model->setRecord( row, newRecord ) )
        {
            qDebug() << model->lastError();
        }
        table->setCurrentIndex(insertIndex);
        table->edit(insertIndex);

    }
    else
    {
        row = -1;
        qDebug() << model->lastError();
    }
    return row;
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


int SqlDataManager::get_data( QString& NodeName, QMap< int, pack_types_t >& p_list, QMap< int, msg_types_t  > & m_list )
{
    int i;
    QString str = tr("select packName from NodePacks where nodeName in (select ID from Nodes where nodeName == '%1')").arg(NodeName);
    QSqlQuery q("",m_db);
    QList<int> tempIDS;
    p_list.clear();
    m_list.clear();
    /*Find packets Id in node*/
    EXEC_QUERY(q,str );
    if( QSqlError::NoError == m_db.lastError().type() )
    {
        QSqlRecord record;
        while( q.next() )
        {
            record = q.record();
            tempIDS.append( record.field("packName").value().toInt() );
        }
        q.finish() ;
        while( q.isActive() );
    }

    str  = "";
    for( i = 0; i< tempIDS.count();i++)
    {
        str.append(QString("%1").arg(tempIDS.value(i)));
        if( i < tempIDS.count() -1 )
        {
            str.append(",");
        }
    }
    /*Get packets description from packet ID*/
    EXEC_QUERY(q,QString("select * from Packets where ID in (%1)").arg(str) );
    if( QSqlError::NoError == m_db.lastError().type() )
    {
        pack_types_t temp;
        QSqlRecord record;
        int id;
        while( q.next() )
        {
            record = q.record();
            id =  record.field("ID").value().toInt();
            temp.packName             =  record.field("packName").value().toString();
            temp.packetDescription    =  record.field("packetDescription").value().toString();
            p_list[id]                =  temp;
            //qDebug() << "ID= " <<  p_list[id].mIDs << "  " << p_list[id].packName <<"  "<<  p_list[id].packetDescription << "\n";
        }
        q.finish() ;
        while( q.isActive() );
    }
    /*Get packet messages*/
    tempIDS.clear();
    EXEC_QUERY(q,QString("select * from PacketsDesc where packName in (%1)").arg(str) );
    if( QSqlError::NoError == m_db.lastError().type() )
    {
        QSqlRecord record;
        int packId;
        msg_pos mIdpos;
        int mID;

        while( q.next() )
        {
            record    = q.record();
            packId    = record.field("packName").value().toInt();
            mID       = record.field("msgName").value().toInt();
            mIdpos.ID = mID;
            tempIDS.append( mID );
            mIdpos.pos = record.field("msgPos").value().toInt();
            p_list[packId].mIDs.append( mIdpos  );
        }
        q.finish() ;
        while( q.isActive() );
    }


    str  = "";
    for( i = 0; i< tempIDS.count();i++)
    {
        str.append(QString("%1").arg(tempIDS.value(i)));
        if( i < tempIDS.count() -1 )
        {
            str.append(",");
        }
    }
    /*Get messages descriptions*/
    EXEC_QUERY(q,QString("select * from Messages where ID in (%1)").arg(str) );
    if( QSqlError::NoError == m_db.lastError().type() )
    {

        QSqlRecord record;
        int mId;
        msg_types_t temp;
        while( q.next() )
        {
            record              = q.record();
            mId                 = record.field("ID").value().toInt();
            temp.BitLen         = record.field("BitLen").value().toInt();
            temp.msgName        = record.field("msgName").value().toString();
            temp.Type           = record.field("Type").value().toInt();
            temp.DefaultValue   = record.field("DefaultValue").value().toInt();
            temp.msgDescription = record.field("msgDescription").value().toString();
            m_list[mId]         = temp;
        }
        q.finish() ;
        while( q.isActive() );
    }

    return 0;
}
