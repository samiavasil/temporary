#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QDialog>

namespace Ui {
class PluginList;
}

class PluginList : public QDialog
{
    Q_OBJECT
    
public:
    explicit PluginList(QWidget *parent = 0);
    ~PluginList();
    
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

protected:
    void populatePluginList();
private:

    Ui::PluginList *ui;
};

#endif // PLUGINLIST_H
