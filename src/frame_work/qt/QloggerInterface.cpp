#include "base/debug.h"
#include "QLoggerInterface.h"

QloggerInterface_private::QloggerInterface_private( QObject* parent ):QObject( parent )
{

}

void QloggerInterface_private::Log( const QString& data )
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    WARNING << "        LogHop: " <<  data.toAscii().constData();
#else
    WARNING << "        LogHop: " <<  data.toLatin1().constData();
#endif
    emit LogOutput( data );
}

QLoggerInterface::QLoggerInterface( QLoggerInterface::LogId_t id  ):m_Id( id ),m_enLog(true)
{
    m_Object = new QloggerInterface_private( NULL );
    LogerTree::instance()->addToLoggerList( this );
    enableLog( m_enLog );
}

QLoggerInterface::~QLoggerInterface()
{
    LogerTree::instance()->removeFromLoggerList( this );
    if( m_Object )
    {
        m_Object->deleteLater();
    }
}

QLoggerInterface::LogId_t QLoggerInterface::getId()
{
    return m_Id;
}

void QLoggerInterface::setId( QLoggerInterface::LogId_t id)
{
    m_Id = id;
}

void QLoggerInterface::Log( const QString &data )
{
    if( m_enLog )
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    WARNING << "LogFrom[" << m_Id << "]: " << data.toAscii().constData();
#else
    WARNING << "LogFrom[" << m_Id << "]: " << data.constData();
#endif
        getObject()->Log( data );
    }
    else
    {
        WARNING << "LogFrom[" << m_Id << "] disabled";
    }
}

void QLoggerInterface::enableLog( bool enb )
{
   m_enLog = enb;
   getObject()->blockSignals( (!m_enLog) );
}

QloggerInterface_private *QLoggerInterface::getObject()
{
    return m_Object;//TODO - fix me
}

bool LogerTree::connect( QLoggerInterface* Logg, QLoggerInterface* destLogg ){
    QObject::connect( Logg->getObject(),SIGNAL(LogOutput(const QString&)), destLogg->getObject(), SLOT(Log( const QString&)) );
    return true;//TODO - fix me
}

bool LogerTree::disconnect( QLoggerInterface* Logg, QLoggerInterface* destLogg ){
    QObject::disconnect( Logg->getObject(),SIGNAL(LogOutput(const QString&)), destLogg->getObject(), SLOT(Log(const QString&)) );
    return true;
}

bool LogerTree::isLoggerConected( QLoggerInterface* Logg, QLoggerInterface::LogId_t dest_logger ){

    bool ret = false;
    if( Logg )
    {
       QLoggerInterface::LogId_t src_id = Logg->getId();
       if( Logg == m_id_obj_map.value( src_id, NULL ) )
       {
           if( m_id_con_map.values( src_id ).contains( dest_logger ) )
           {
               /*Already connected. Here can add checks is the Qobject connection is OK*/
               ret = true;
           }
       }
       else
       {
           /*Someting incorrect with object map*/
           WARNING << "QloggerInterface[" << (void*)Logg << "] isn't founded on id/object map";
       }
    }
    return ret;//TODO - fix me
}

QLoggerInterface::LogId_t LogerTree::getNewLoggerId(){
    int i;
    m_NextId++;
    //return m_NextId;
    QList< QLoggerInterface::LogId_t > keys = m_id_obj_map.keys();
    for( i = QLoggerInterface::ROOT_ID + 1; i < keys.count() ; i++  )
    {
        if( i < keys.value( i, -1 ) )
        {
           break;
        }
    }
    return i;
}

int LogerTree::removeFromLoggerList( QLoggerInterface* log )
{
    int ret = -1;
    if( log )
    {
        ret = instance()->disconnectLogger( log );
        if( 0 != ret )
        {
            //TODO: DBG some error
        }
        m_id_obj_map.remove( log->getId() );
        ret = 0;
    }
    return ret;
}

int LogerTree::addToLoggerList( QLoggerInterface* log  ){
    int ret = -1;
    if( log )
    {
        if( QLoggerInterface::INALID_ID == log->getId() )
        {
            log->setId( instance()->getNewLoggerId() );
        }
        QLoggerInterface* tempLog = m_id_obj_map.value( log->getId(), NULL );
        if( tempLog == NULL )
        {
            m_id_obj_map.insert( log->getId(), log );
            ret = 0;
        }
        else if( tempLog != log )
        {
            //DBG: ID not correspond to object - replace old logger with new one
            //TODO: Disconnect old, and connect to new one.
            ret = 2;
        }
        else
        {
            ret = 1;//Already added
        }
    }
    return ret;
}

int LogerTree::connectLogger( QLoggerInterface* logger, QLoggerInterface::LogId_t dest_logger_id )
{

    if( logger )
    {
        QLoggerInterface::LogId_t  dest_id = dest_logger_id;
        QLoggerInterface* destLogger =  m_id_obj_map.value( dest_id, NULL );
        if( NULL == destLogger )
        {
            if( QLoggerInterface::ROOT_ID != dest_id )
            {
                //Destination logger doesn't exist - Try to Connect ROOT logger
                destLogger = m_id_obj_map.value( QLoggerInterface::ROOT_ID, NULL );
            }
        }
        if( destLogger )
        {
            //Destination logger exist - Connect --->
            if( !instance()->isLoggerConected( logger, dest_id ) )
            {
                instance()->connect( logger, destLogger );
            }
            else
            {
                //WARNING("Logger Already connected")
            }
        }
        else
        {
            //WARNING("Root Logger doesn' exist - SOMETHING IS VERY WRONG!!!")
            return -1;
        }
    }
    return 0;
}

int LogerTree::disconnectLogger( QLoggerInterface* logger ){
    int ret = -1;
    if( logger )
    {
        QLoggerInterface::LogId_t id = logger->getId();
        if( id != QLoggerInterface::INALID_ID )
        {
            QList<QLoggerInterface::LogId_t> con_ids = m_id_con_map.values(id);
            if( con_ids.count() > 0 )
            {
                for( int i = 0; i < con_ids.count(); i++ )
                {
                    if( 0 != disconnectLogger( logger, con_ids.value( i, QLoggerInterface::INALID_ID ) ) )
                    {
                        //TODO - dump some error
                    }
                }
                if( m_id_con_map.values( id ).size() > 0 )
                {
                    //DBG!!! - something wrong not removed all connections
                }
            }
        }
        ret = 0;
    }
    return ret;
}

int LogerTree::disconnectLogger( QLoggerInterface* logger, QLoggerInterface::LogId_t id_dest ){
    int ret = -1;

    if( logger  )
    {
        if( logger == m_id_obj_map.value( logger->getId(), NULL ) )
        {
            QLoggerInterface* dest_log = m_id_obj_map.value( id_dest, NULL );
            disconnect( logger, dest_log );
            m_id_con_map.remove( logger->getId(), id_dest );
            ret = 0;
        }
        else
        {
            //DBG logerId doesn't correspond to logger object ????
            ret = -2;//TODO
        }
    }
    return ret;
}

MainLogger::MainLogger():QLoggerInterface( QLoggerInterface::ROOT_ID )
{

}

LogerTree*  LogerTree::m_Tree;
int         LogerTree::m_NextId;
QMap<QLoggerInterface::LogId_t, QLoggerInterface*>               LogerTree::m_id_obj_map;   /**/
QMultiMap<QLoggerInterface::LogId_t, QLoggerInterface::LogId_t>  LogerTree::m_id_con_map;
LogerTree::LogerTree()
{

}

LogerTree* LogerTree::instance()
{
    if( 0 == m_Tree )
    {
        m_Tree = new LogerTree();
        /*m_MailLogger = */new MainLogger();
    }
    return m_Tree;
}
