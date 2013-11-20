/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "browser.h"
#include "qsqlconnectiondialog.h"

#include <QtGui>
#include <QtSql>

Browser::Browser(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    table->addAction(insertRowAction);
    table->addAction(deleteRowAction);

    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));
    connect( this, SIGNAL(statusMessage(QString)), logEdit, SLOT(append(QString)) );
    emit statusMessage(tr("Ready."));
}

Browser::~Browser()
{
    QSqlDatabase::database("in_mem_db", false).close();
    QSqlDatabase::database("in_mem_db1", false).close();

}

void Browser::exec()
{
    QSqlQueryModel *model = new QSqlQueryModel(table);
    model->setQuery(QSqlQuery(sqlEdit->toPlainText(), connectionWidget->currentDatabase()));
    table->setModel(model);

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    else if (model->query().isSelect())
        emit statusMessage(tr("Query OK."));
    else
        emit statusMessage(tr("Query OK, number of affected rows: %1").arg(
                           model->query().numRowsAffected()));

    updateActions();
}

QSqlError Browser::addConnection(const QString &driver, const QString &dbName, const QString &host,
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
    }
    QSqlQuery q("", db);
  //  q.exec("drop table Movies");
//     q.exec("drop table Names");
   if(!  q.exec("PRAGMA foreign_keys = ON") )
       qDebug("Can't enable foreign keys!!!! ");
    connectionWidget->refresh();

    return err;
}

void createRelationalTables( QSqlDatabase& db )
{
    QSqlQuery query( "",db );
    if(!  query.exec("PRAGMA foreign_keys = ON") )
        qDebug("Can't enable foreign keys!!!! ");
    query.exec("CREATE TABLE MsgValueTypes ( ID INTEGER PRIMARY KEY AUTOINCREMENT, typeName VARCHAR( 1, 20 )  NOT NULL UNIQUE );");

    /*query.exec("insert into MsgValueTypes values(1, 'Espen', 5000, 47)");
    query.exec("insert into employee values(2, 'Harald', 80000, 49)");
    query.exec("insert into employee values(3, 'Sam', 100, 1)");*/
    query.exec("CREATE TABLE Messages ( ID INTEGER( 1, 11111 )  PRIMARY KEY,bitLen INTEGER NOT NULL, type  INTEGER NOT NULL,  FOREIGN KEY(type) REFERENCES MsgValueTypes ( ID ) )");

    /*query.exec("insert into city values(100, 'San Jose')");
    query.exec("insert into city values(5000, 'Oslo')");
    query.exec("insert into city values(80000, 'Munich')");*/

    query.exec("CREATE TABLE EnumTable ( ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR  NOT NULL,value  INTEGER( 1, 10001 ),enumID INTEGER( 1, 20 ) NOT NULL )");
    /*query.exec("insert into country values(1, 'USA')");
    query.exec("insert into country values(47, 'Norway')");
    query.exec("insert into country values(49, 'Germany')");*/
}

void initializeModel( const QString &t, QSqlRelationalTableModel *model )
{
    if( NULL == model )
    {
        return;
    }
    model->setTable( t );
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    if(  !t.compare("MsgValueTypes") )
    {

    }
    else if( !t.compare("Messages") )
    {
        model->setRelation(2, QSqlRelation("MsgValueTypes", "ID", "typeName"));
        //model->setRelation(3, QSqlRelation("country", "id", "name"));
    }else if( !t.compare("EnumTable") )
    {

    }
    model->select();

#if 0
    model->setTable("employee");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setRelation(2, QSqlRelation("city", "id", "name"));
    model->setRelation(3, QSqlRelation("country", "id", "name"));

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));

    model->select();
#endif
}

void Browser::addConnection()
{
    QSqlConnectionDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    if (dialog.useInMemoryDatabase()) {
       // QSqlDatabase::database("in_mem_db", false).close();
       // QSqlDatabase::removeDatabase("in_mem_db");
        static int a;
        a=!a;
        QSqlDatabase db;

        if( a )
          db = QSqlDatabase::addDatabase("QSQLITE", "in_mem_db");
        else
          db = QSqlDatabase::addDatabase("QSQLITE", "in_mem_db1");

        //db.setDatabaseName(":bauuu:");
        db.setHostName("localhost");
        db.setDatabaseName("customdb");
        db.setUserName("mojito");
        db.setPassword("J0a1m8");
        if (!db.open())
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                         "opening the connection: ") + db.lastError().text());
       QSqlQuery q("", db);
       q.exec("drop table EnumTable");
        q.exec("drop table Messages");
        q.exec("drop table MsgValueTypes");

        createRelationalTables( db );
#if 0



        if(! q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)") )
                 qDebug() << q.lastError().databaseText();
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
                qDebug() << q.lastError().databaseText();
#endif
        connectionWidget->refresh();
        qDebug()<< db.record( db.tables()[0] );
    } else {
        QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                           dialog.userName(), dialog.password(), dialog.port());
        if (err.type() != QSqlError::NoError)
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                       "opening the connection: ") + err.text());
    }

}

void Browser::showTable(const QString &t)
{
    //QSqlTableModel *model = new QSqlTableModel(table, connectionWidget->currentDatabase());

    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(table, connectionWidget->currentDatabase());

#if 0
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable(connectionWidget->currentDatabase().driver()->escapeIdentifier(t, QSqlDriver::TableName));
    model->select();
#endif
    initializeModel( t, model );

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    QItemSelectionModel *m = table->selectionModel();
    table->setModel(model);
    delete m;
    table->setItemDelegate(new QSqlRelationalDelegate(table));
    table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentChanged()));
    updateActions();
}

void Browser::showMetaData(const QString &t)
{
    QSqlRecord rec = connectionWidget->currentDatabase().record(t);
    QStandardItemModel *model = new QStandardItemModel(table);

    model->insertRows(0, rec.count());
    model->insertColumns(0, 7);

    model->setHeaderData(0, Qt::Horizontal, "Fieldname");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Length");
    model->setHeaderData(3, Qt::Horizontal, "Precision");
    model->setHeaderData(4, Qt::Horizontal, "Required");
    model->setHeaderData(5, Qt::Horizontal, "AutoValue");
    model->setHeaderData(6, Qt::Horizontal, "DefaultValue");


    for (int i = 0; i < rec.count(); ++i) {
        QSqlField fld = rec.field(i);
        model->setData(model->index(i, 0), fld.name());
        model->setData(model->index(i, 1), fld.typeID() == -1
                ? QString(QVariant::typeToName(fld.type()))
                : QString("%1 (%2)").arg(QVariant::typeToName(fld.type())).arg(fld.typeID()));
        model->setData(model->index(i, 2), fld.length());
        model->setData(model->index(i, 3), fld.precision());
        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
                : QVariant(bool(fld.requiredStatus())));
        model->setData(model->index(i, 5), fld.isAutoValue());
        model->setData(model->index(i, 6), fld.defaultValue());
    }

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateActions();
}

void Browser::insertRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(table->model());
    if (!model)
        return;

    QModelIndex insertIndex = table->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    model->insertRow(row);
    insertIndex = model->index(row, 0);
    table->setCurrentIndex(insertIndex);
    table->edit(insertIndex);
}

void Browser::deleteRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(table->model());
    if (!model)
        return;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QModelIndexList currentSelection = table->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        if (currentSelection.at(i).column() != 0)
            continue;
        model->removeRow(currentSelection.at(i).row());
    }

    model->submitAll();
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    updateActions();
}

void Browser::updateActions()
{
    bool enableIns = qobject_cast<QSqlTableModel *>(table->model());
    bool enableDel = enableIns && table->currentIndex().isValid();

    insertRowAction->setEnabled(enableIns);
    deleteRowAction->setEnabled(enableDel);
}

void Browser::about()
{
    QMessageBox::about(this, tr("About"), tr("The SQL Browser demonstration "
        "shows how a data browser can be used to visualize the results of SQL"
        "statements on a live database"));
}

void Browser::on_pushButton_clicked()
{
    logEdit->clear();
}


