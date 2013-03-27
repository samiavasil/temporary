#ifndef QTESTCOMMAND_H
#define QTESTCOMMAND_H

#include <qt/QCommand.h>
#include "qt/QFrameWork.h"
class QFrameWork;
class QPacketCollector;
class QProtocolPackFactory;

class QtestCommand : public QCommand
{
    Q_OBJECT
public:
    explicit QtestCommand( QPacketCollector* colector, QProtocolPackFactory *factory, QObject *parent = NULL );
    virtual ~QtestCommand();
signals:
    
public slots:
protected:
    virtual int handler();
    QPacketCollector*     m_Col;
    QProtocolPackFactory* m_Factory;
    int a;
};

#endif // QTESTCOMMAND_H
