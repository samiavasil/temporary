#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "base/global.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionNew_triggered();

    void on_actionFullScreen_triggered(bool checked);

    void on_actionHideToolbar_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
