#ifndef QFRADEVICE_H
#define QFRADEVICE_H

#include <QWidget>

namespace Ui {
class QFraDevice;
}
class QPortsIoView;
class QProtocolPackFactory;
class QCommandExecutor;
class QPacketCollector;

class QFraDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit QFraDevice(QWidget *parent = 0);
    ~QFraDevice();

private slots:
    void onStartButtonclicked(bool clicked);
protected:
    QPortsIoView* m_PIOList;
    QProtocolPackFactory* m_packetFactory;
    QCommandExecutor*     m_Executor;
    QPacketCollector*     m_packetCollector;

private:
    Ui::QFraDevice *ui;
};

#endif // QFRADEVICE_H
