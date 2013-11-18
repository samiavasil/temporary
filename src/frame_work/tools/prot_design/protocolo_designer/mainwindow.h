#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

QT_FORWARD_DECLARE_CLASS(QSqlError)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)

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
private slots:
    void on_actionNewProject_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
