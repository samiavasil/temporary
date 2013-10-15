#ifndef QLOGGERINTERFACE_H
#define QLOGGERINTERFACE_H
#include "frame_work_global.h"
#include<QMultiMap>
#include <QObject>

class QloggerInterface_private:public QObject
{
    Q_OBJECT
public:
    QloggerInterface_private( QObject* parent );
public slots:
    virtual void Log( const QString& data );
signals:
    void LogOutput( const QString& data );
};

class FRAME_WORKSHARED_EXPORT QloggerInterface
{
public:
    typedef int LogId_t;

    enum{
        ROOT_ID,
        INALID_ID = 0xffffffff
    };

    explicit QloggerInterface( QloggerInterface::LogId_t id = INALID_ID );
    virtual ~QloggerInterface();
    QloggerInterface::LogId_t getId();
    QloggerInterface::LogId_t getConnId();
    void setId( QloggerInterface::LogId_t id);//TODO- make protected and friend only axxess

    virtual void enableLog( bool enb);
    virtual void Log( const QString& data );

protected:
    QloggerInterface_private* getObject();
protected:
    QloggerInterface_private* m_Object;
    QloggerInterface::LogId_t m_Id;
    bool m_enLog;
    friend class LogerTree;
};

class LogerTree
{
public:
    static   LogerTree* instance();
    static   int addToLoggerList( QloggerInterface* log );// = 0;
    static   int removeFromLoggerList( QloggerInterface* log );// = 0;
    static   int connectLogger( QloggerInterface* logger, QloggerInterface::LogId_t dest_logger_id );
    int      disconnectLogger( QloggerInterface* logger );
    int      disconnectLogger( QloggerInterface* logger, QloggerInterface::LogId_t id_dest );
protected:
    explicit LogerTree();
    bool connect( QloggerInterface* Logg, QloggerInterface* destLogg );//= 0;
    virtual  bool disconnect( QloggerInterface* Logg, QloggerInterface* destLogg );
    bool isLoggerConected( QloggerInterface* Logg, QloggerInterface::LogId_t dest_logger )                   ;// = 0;
    virtual  QloggerInterface::LogId_t getNewLoggerId()                        ;// = 0;

protected:
    static   LogerTree*  m_Tree;
    static   int         m_NextId;
    static   QMap<QloggerInterface::LogId_t, QloggerInterface*>          m_id_obj_map;   /**/
    static   QMultiMap<QloggerInterface::LogId_t, QloggerInterface::LogId_t>  m_id_con_map;
};


class MainLogger:public virtual QObject,public QloggerInterface
{
public:
    explicit MainLogger();
};

#endif // QLOGGERINTERFACE_H
