#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqldatamanager.h"

namespace Ui {
class MainWindow;
}



QT_FORWARD_DECLARE_CLASS(QSqlError)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QModelIndex)


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                                const QString &user, const QString &passwd, int port);
    void showTable( SqlDataManager::sqlTablesTypes_t type, QString &q);
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
protected:
    SqlDataManager data_manager;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
