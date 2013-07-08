#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "base/global.h"
#include <QMainWindow>
#include"qt/QPluginList.h"

namespace Ui {
class MainWindow;
}

namespace Ui {
class Designer;
}
namespace qdesigner_internal {
    class QDesignerIntegration;
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

    void on_actionHideMainMenu_triggered(bool checked);

    void on_actionSave_triggered();


    void onUndoAvailable();

    void onRedoAvailable();

    void onCopyAvailable();

    void onPasteAvailable();
signals:
    void copyAvailable(bool);
    void undoAvailable(bool);
    void redoAvailable(bool);
    void pasteAvailable(bool);
protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
protected:
    void createQTDesignerWidget();
    qdesigner_internal::QDesignerIntegration * _designer;
private:
    Ui::MainWindow *ui;
    Ui::Designer   *ui_des;
};

#endif // MAINWINDOW_H
