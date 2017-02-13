#ifndef QLOGGERINTERFACE_H
#define QLOGGERINTERFACE_H
#include "base/global.h"
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

class FRAME_WORKSHARED_EXPORT QLoggerInterface
{
public:
    typedef int LogId_t;

    enum{
        ROOT_ID,
        INALID_ID = -1
    };

    explicit QLoggerInterface( QLoggerInterface::LogId_t id = INALID_ID );
    virtual ~QLoggerInterface();
    QLoggerInterface::LogId_t getId();
    QLoggerInterface::LogId_t getConnId();
    void setId( QLoggerInterface::LogId_t id);//TODO- make protected and friend only axxess

    virtual void enableLog( bool enb);
    virtual void Log( const QString& data );

protected:
    QloggerInterface_private* getObject();
protected:
    QloggerInterface_private* m_Object;
    QLoggerInterface::LogId_t m_Id;
    bool m_enLog;
    friend class LogerTree;
};

class Q_DECL_EXPORT LogerTree
{
public:
    static   LogerTree* instance();
    static   int addToLoggerList( QLoggerInterface* log );// = 0;
    static   int removeFromLoggerList( QLoggerInterface* log );// = 0;
    static   int connectLogger( QLoggerInterface* logger, QLoggerInterface::LogId_t dest_logger_id );
    int      disconnectLogger( QLoggerInterface* logger );
    int      disconnectLogger( QLoggerInterface* logger, QLoggerInterface::LogId_t id_dest );
protected:
    explicit LogerTree();
    bool connect( QLoggerInterface* Logg, QLoggerInterface* destLogg );//= 0;
    virtual  bool disconnect( QLoggerInterface* Logg, QLoggerInterface* destLogg );
    bool isLoggerConected( QLoggerInterface* Logg, QLoggerInterface::LogId_t dest_logger )                   ;// = 0;
    virtual  QLoggerInterface::LogId_t getNewLoggerId()                        ;// = 0;

protected:
    static   LogerTree*  m_Tree;
    static   int         m_NextId;
    static   QMap<QLoggerInterface::LogId_t, QLoggerInterface*>          m_id_obj_map;   /**/
    static   QMultiMap<QLoggerInterface::LogId_t, QLoggerInterface::LogId_t>  m_id_con_map;
};


class MainLogger:public virtual QObject,public QLoggerInterface
{
public:
    explicit MainLogger();
};

#endif // QLOGGERINTERFACE_H
