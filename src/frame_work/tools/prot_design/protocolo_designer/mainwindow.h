#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

typedef enum{
    eNET,
    eNODE,
    ePACKET,
    eMESSAGES,
    eENUM_NUMBER
}column_t;

QT_FORWARD_DECLARE_CLASS(QSqlError)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QModelIndex)
typedef struct table_desc_ table_desc_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                                const QString &user, const QString &passwd, int port);
    int  createTables(QSqlDatabase &db);
    int  createTable( QSqlDatabase &db, const table_desc_t *desc );
    void showTable(column_t type);
    void deleteRow();
    void insertRow();
public slots:
    void on_insertRowAction_triggered()
    { insertRow(); }
    void on_deleteRowAction_triggered()
    { deleteRow(); }

private slots:
    void on_actionNewProject_triggered();
    void on_treeWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
