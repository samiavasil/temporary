#include "sqldatamanager.h"
#include <QtSql>
#if 0
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
    {"netName",  " varchar"},
};

const items_t node_table_items_names[] =
{
    {"ID",        " integer primary key" },
    {"nodeName",  " varchar"             },
    {"netName",   " INTEGER NOT NULL,  FOREIGN KEY(netName) REFERENCES Nets ( ID )" }
};


const items_t packets_table_items_names[] = {
    {"ID",         " integer primary key"},
    {"packName",   " varchar"            },
    {"Messages",   " integer"            },
    {"nodeName",   " INTEGER NOT NULL,  FOREIGN KEY(nodeName) REFERENCES Nodes ( ID )" }
};

const items_t messages_table_items_names[] =
{
    {"ID",           " integer primary key"},
    {"msgName",      " varchar"            },
    {"BitLen",       " integer"            },
    {"Type",         " integer"            },
    {"DefaultValue", " integer"            },
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





SqlDataManager::SqlDataManager(QObject *parent) :
    QObject(parent)
{
}
#endif
