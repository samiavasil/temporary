#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsqlconnectiondialog.h"
#include <QtSql>

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
    db.close();
    return err;
}

typedef struct
{
    const char* name;
    const char* type;
}items_t;

const items_t messages_table_items_names[] =
{
    {"MsgId", " integer primary key"},
    {"Name",  " varchar"},
    {"BitLen"," integer"},
    {"Type",  " integer"},
    {"DefaultValue", " integer"},
};

const items_t packets_table_items_names[] = {
    {"PackId", " integer primary key"},
    {"Messages", " integer"},
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
         "Messages",
         messages_table_items_names,
         GET_ARREA_NUMS( messages_table_items_names )
      },
      {
        "Packets",
         packets_table_items_names,
         GET_ARREA_NUMS( packets_table_items_names )
      }
};

#define EXEC_QUERY( x,y ) qDebug() << "Execute query " << y;\
                          if( !(x).exec((y)) ){\
                              qDebug() << (x).lastError().databaseText();\
                          }
#include<QString>

int MainWindow::createTable( QSqlDatabase& db1, const table_desc_t* desc )
{
    qDebug()<<"Connection names:"<<QSqlDatabase::connectionNames();
    QSqlDatabase db = QSqlDatabase::database(QSqlDatabase::connectionNames()[QSqlDatabase::connectionNames().count()-1]);
    qDebug()<<"Used connection"<<db.connectionName();
    QSqlQuery q("", db);
    QString str(tr("create table %1 (").arg( desc->name ));
    for(int i=0; i< desc->items_count; i++)
    {
        str.append(tr("%1 %2").arg(desc->table_items_names[i].name).arg(desc->table_items_names[i].type));
        if( i < desc->items_count - 1 )
            str.append(",");
    }
    str.append(")");
    EXEC_QUERY(q, str);

    #if 0
    q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
    q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
    q.exec("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
    q.exec("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
    q.exec("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
    q.exec("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
    q.exec("create table Names (id number primary key, Firstname varchar, Lastname varchar, City varchar)");
 //   q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
 //   q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
 //   q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
 //   q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
 //   q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");
     if(! q.exec("insert into Names values (5, 'Wlock', 'Holmes', 'London')") )
#endif
         return 0;
}

int MainWindow::createTables( QSqlDatabase& db )
{
    //db = QSqlDatabase::database();/*TODO: Add connection name*/

    QSqlQuery q("", db);
  //  q.exec("drop table Movies");
   q.exec("drop table Packets");
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

