#ifndef QPORTSIOVIEW_H
#define QPORTSIOVIEW_H

#include <QWidget>
#include <QList>
#include "qt/PluginDescription.h"

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

private slots:
    void selectedPluginChanged( const PluginDescription &desc );

private:
    Ui::QPortsIoView *ui;
    QList< PluginDescription > mIoPorts;
    QPortIO* mCurrentIo;
};

#endif // QFRAIOPORTSVIEW_H
