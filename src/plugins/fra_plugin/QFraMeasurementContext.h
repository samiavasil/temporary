#ifndef QFRAMEASUREMENTCONTEXT_H
#define QFRAMEASUREMENTCONTEXT_H

#include <QObject>
#include "FraMeasurementConfig.h"

class QCommandExecutor;
class QPortIO;
class QProtocolPackFactory;
class QPacketCollector;
class FraMeasurementConfig;

class QFraMeasurementContext : public QObject
{
    Q_OBJECT
public:
    typedef enum{ //TBD
      E_IDLE,
      E_WORK
    }FraMeasureStatus;
    explicit QFraMeasurementContext(QObject *parent = 0);
    QFraMeasurementContext::FraMeasureStatus getStatus();

    void setCommandExecutor( QCommandExecutor* Executor );
    void setPort( QPortIO* port );
    void setProtocolPackFactory( QProtocolPackFactory* factory );
    void setPacketCollector( QPacketCollector* packetCollector );
    void setMesConfig( FraMeasurementConfig& cfg ) ;

    QCommandExecutor*     getCommandExecutor();
    QPortIO*              getPort();
    QProtocolPackFactory* getProtocolPackFactory();
    QPacketCollector*     getPacketCollector();
    FraMeasurementConfig& getMesConfig();


    bool startMeasure();

protected:
    bool paramsAreGood();
    bool configIsGood();
signals:
    
public slots:

protected:
    QCommandExecutor*     m_Executor;
    QPortIO*              m_port;
    QProtocolPackFactory* m_packetFactory;
    QPacketCollector*     m_packetCollector;
    FraMeasurementConfig  m_Cfg;
    FraMeasureStatus      m_status;
};

#endif // QFRAMEASUREMENTCONTEXT_H
