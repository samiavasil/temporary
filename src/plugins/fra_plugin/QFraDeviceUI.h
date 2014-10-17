#ifndef QFRADEVICE_H
#define QFRADEVICE_H

#include <QWidget>
#include"QFraMeasurementContext.h"

namespace Ui {
class QFraDevice;
}
class QPortsIoView;
class QProtocolPackFactory;
class QCommandExecutor;
class QPacketCollector;

class QFraDeviceUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit QFraDeviceUI(QWidget *parent = 0);
    ~QFraDeviceUI();
protected:
    int getMeasurementParams( FraMeasurementConfig &params );
private slots:
    void onStartButtonclicked(bool clicked);
protected:
    QPortsIoView* m_PIOList;
    QProtocolPackFactory*  m_packetFactory;
    QCommandExecutor*      m_Executor;
    QPacketCollector*      m_packetCollector;
    QFraMeasurementContext mes_ctx;
private:
    Ui::QFraDevice *ui;
};

#endif // QFRADEVICE_H
