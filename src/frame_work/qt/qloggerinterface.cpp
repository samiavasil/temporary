#include "qloggerinterface.h"




QloggerInterface::QloggerInterface(QObject * obj, LogId_t id ):m_myObj( obj ),m_Id( id )
{

    LogerTree::instance()->addToLoggerList( this );
}

QloggerInterface::LogId_t QloggerInterface::getId()
{
    return m_Id;
}



void QloggerInterface::setId( QloggerInterface::LogId_t id)
{
    m_Id = id;
}

QObject * QloggerInterface::getObject()
{
   return m_myObj;
}

void QloggerInterface::Log( QString& data )
{
    emit LogOutput( data );
}

bool LogerTree::connect( QloggerInterface* Logg, QloggerInterface* destLogg ){
    QObject::connect( Logg->getObject(),SIGNAL(LogOutput(QString&)), destLogg->getObject(), SLOT(Log(QString&)) );
}

bool LogerTree::disconnect( QloggerInterface* Logg, QloggerInterface* destLogg ){
    QObject::connect( Logg->getObject(),SIGNAL(LogOutput(QString&)), destLogg->getObject(), SLOT(Log(QString&)) );
}

bool LogerTree::isLoggerConected( QloggerInterface* Logg, QloggerInterface::LogId_t dest_logger ){
     return false;//TODO - fix me
}



QloggerInterface::LogId_t LogerTree::getNewLoggerId(){
    m_NextId++;
    return m_NextId;
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

MainLogger::MainLogger():QloggerInterface( this, QloggerInterface::ROOT_ID )
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
