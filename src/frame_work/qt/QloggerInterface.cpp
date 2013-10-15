#include "base/debug.h"
#include "QloggerInterface.h"

QloggerInterface_private::QloggerInterface_private( QObject* parent ):QObject( parent )
{

}

void QloggerInterface_private::Log( const QString& data )
{
    DUMP << "        LogHop: " <<  data.toAscii().constData();
    emit LogOutput( data );
}

QloggerInterface::QloggerInterface( QloggerInterface::LogId_t id  ):m_Id( id ),m_enLog(true)
{
    m_Object = new QloggerInterface_private( NULL );
    LogerTree::instance()->addToLoggerList( this );
    enableLog( m_enLog );
}

QloggerInterface::~QloggerInterface()
{
    LogerTree::instance()->removeFromLoggerList( this );
    if( m_Object )
    {
        m_Object->deleteLater();
    }
}

QloggerInterface::LogId_t QloggerInterface::getId()
{
    return m_Id;
}

void QloggerInterface::setId( QloggerInterface::LogId_t id)
{
    m_Id = id;
}

void QloggerInterface::Log( const QString &data )
{
    if( m_enLog )
    {
        DUMP << "LogFrom[" << m_Id << "]: " << data.toAscii().constData();
        getObject()->Log( data );
    }
    else
    {
        DUMP << "LogFrom[" << m_Id << "] disabled";
    }
}

void QloggerInterface::enableLog( bool enb )
{
   m_enLog = enb;
   getObject()->blockSignals( (!m_enLog) );
}

QloggerInterface_private *QloggerInterface::getObject()
{
    return m_Object;//TODO - fix me
}

bool LogerTree::connect( QloggerInterface* Logg, QloggerInterface* destLogg ){
    QObject::connect( Logg->getObject(),SIGNAL(LogOutput(const QString&)), destLogg->getObject(), SLOT(Log( const QString&)) );
    return true;//TODO - fix me
}

bool LogerTree::disconnect( QloggerInterface* Logg, QloggerInterface* destLogg ){
    QObject::disconnect( Logg->getObject(),SIGNAL(LogOutput(const QString&)), destLogg->getObject(), SLOT(Log(const QString&)) );
    return true;
}

bool LogerTree::isLoggerConected( QloggerInterface* Logg, QloggerInterface::LogId_t dest_logger ){
     return false;//TODO - fix me
}

QloggerInterface::LogId_t LogerTree::getNewLoggerId(){
    int i;
    m_NextId++;
    //return m_NextId;
    QList< QloggerInterface::LogId_t > keys = m_id_obj_map.keys();
    for( i = QloggerInterface::ROOT_ID + 1; i < keys.count() ; i++  )
    {
        if( i < keys.value( i, -1 ) )
        {
           break;
        }
    }
    return i;
}

int LogerTree::removeFromLoggerList( QloggerInterface* log )
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

int LogerTree::addToLoggerList( QloggerInterface* log  ){
    int ret = -1;
    if( log )
    {
        if( QloggerInterface::INALID_ID == log->getId() )
        {
            log->setId( instance()->getNewLoggerId() );
        }
        QloggerInterface* tempLog = m_id_obj_map.value( log->getId(), NULL );
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

int LogerTree::connectLogger( QloggerInterface* logger, QloggerInterface::LogId_t dest_logger_id )
{

    if( logger )
    {
        QloggerInterface::LogId_t  dest_id = dest_logger_id;
        QloggerInterface* destLogger =  m_id_obj_map.value( dest_id, NULL );
        if( NULL == destLogger )
        {
            if( QloggerInterface::ROOT_ID != dest_id )
            {
                //Destination logger doesn't exist - Try to Connect ROOT logger
                destLogger = m_id_obj_map.value( QloggerInterface::ROOT_ID, NULL );
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
                //DUMP("Logger Already connected")
            }
        }
        else
        {
            //DUMP("Root Logger doesn' exist - SOMETHING IS VERY WRONG!!!")
            return -1;
        }
    }
    return 0;
}

int LogerTree::disconnectLogger( QloggerInterface* logger ){
    int ret = -1;
    if( logger )
    {
        QloggerInterface::LogId_t id = logger->getId();
        if( id != QloggerInterface::INALID_ID )
        {
            QList<QloggerInterface::LogId_t> con_ids = m_id_con_map.values(id);
            if( con_ids.count() > 0 )
            {
                for( int i = 0; i < con_ids.count(); i++ )
                {
                    if( 0 != disconnectLogger( logger, con_ids.value( i, QloggerInterface::INALID_ID ) ) )
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

int LogerTree::disconnectLogger( QloggerInterface* logger, QloggerInterface::LogId_t id_dest ){
    int ret = -1;

    if( logger  )
    {
        if( logger == m_id_obj_map.value( logger->getId(), NULL ) )
        {
            QloggerInterface* dest_log = m_id_obj_map.value( id_dest, NULL );
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

MainLogger::MainLogger():QloggerInterface( QloggerInterface::ROOT_ID )
{

}

LogerTree*  LogerTree::m_Tree;
int         LogerTree::m_NextId;
QMap<QloggerInterface::LogId_t, QloggerInterface*>               LogerTree::m_id_obj_map;   /**/
QMultiMap<QloggerInterface::LogId_t, QloggerInterface::LogId_t>  LogerTree::m_id_con_map;
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
