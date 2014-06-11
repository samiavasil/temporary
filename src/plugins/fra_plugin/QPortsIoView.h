#ifndef QFRAIOPORTSVIEW_H
#define QFRAIOPORTSVIEW_H

#include <QWidget>
#include <QList>
#include "qt/QPluginFabrique.h"

namespace Ui {
class QPortsIoView;
}

class QPortIO;
class QPortsIoView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QPortsIoView(QWidget *parent = 0);
    ~QPortsIoView();
    QPortIO* getCurentIO(  );

protected:
    void addToList( PluginDescription& desc );
public slots:
    void reloadPIOlist();
private slots:
    void on_IoList_currentRowChanged(int currentRow);

private:
    Ui::QPortsIoView *ui;
    QList< PluginDescription > mIoPorts;
    QPortIO* mCurrentIo;
};

#endif // QFRAIOPORTSVIEW_H
