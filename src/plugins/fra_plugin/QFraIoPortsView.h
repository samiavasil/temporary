#ifndef QFRAIOPORTSVIEW_H
#define QFRAIOPORTSVIEW_H

#include <QWidget>
#include <QList>
#include "qt/QPluginFabrique.h"

namespace Ui {
class QfraIoPortsView;
}

class QPortIO;
class QFraIoPortsView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QFraIoPortsView(QWidget *parent = 0);
    ~QFraIoPortsView();
    QPortIO* getCurentIO(  );
    void addToList( PluginDescription desc );
private slots:
    void on_IoList_currentRowChanged(int currentRow);

private:
    Ui::QfraIoPortsView *ui;
    QList< PluginDescription* > mIoPorts;
    QPortIO* mCurrentIo;
};

#endif // QFRAIOPORTSVIEW_H
