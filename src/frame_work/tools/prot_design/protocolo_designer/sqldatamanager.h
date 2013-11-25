#ifndef SQLDATAMANAGER_H
#define SQLDATAMANAGER_H

#include <QObject>
#include <QSqlDatabase>
class QTableView;

typedef struct table_desc_ table_desc_t;
QT_FORWARD_DECLARE_CLASS(QSqlError)

//QT_FORWARD_DECLARE_CLASS(QModelIndex)


class SqlDataManager : public QObject
{
    Q_OBJECT
public:
    typedef enum{
        eNET,
        eNODE,
        ePACKET,
        eMESSAGES,
        eENUM_NUMBER
    }sqlTablesTypes_t;

    explicit SqlDataManager(QObject *parent = 0);
    void initializeModel( SqlDataManager::sqlTablesTypes_t type, QString &querry, QTableView *table );

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                                        const QString &user, const QString &passwd, int port);
    void deleteRow( QTableView* table );
    void insertRow( QTableView* table);
protected:

    int createTables( QSqlDatabase& db );
    int createTable( QSqlDatabase& db, const table_desc_t* desc );
    QSqlDatabase& database( const QString& connectionName = QString(),
                                   bool open = true );

protected:
    QSqlDatabase m_db;
signals:
    
public slots:
    
};

#endif // SQLDATAMANAGER_H
