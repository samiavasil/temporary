#ifndef QLOGGERINTERFACE_H
#define QLOGGERINTERFACE_H
#include <QObject>


class QloggerInterface
{
public:
    typedef int LogId_t;

    enum{
        ROOT_ID,
        INALID_ID = 0xffffffff
    };

    explicit QloggerInterface( QObject * ,QloggerInterface::LogId_t id = INALID_ID );
    void enableLog( bool );
    void Log( );
    QloggerInterface::LogId_t getId();
    QloggerInterface::LogId_t getConnId();

    void setId( QloggerInterface::LogId_t id);//TODO- make protected and friend only axxess
protected:

protected:
    QloggerInterface::LogId_t m_Id;
    QloggerInterface::LogId_t m_ConnId;
    QObject *m_myObj;
};





class MainLogger:public QObject,public QloggerInterface
{
public:
    explicit MainLogger();
};

#endif // QLOGGERINTERFACE_H
