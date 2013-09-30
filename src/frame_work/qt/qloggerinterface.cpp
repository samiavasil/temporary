#include "qloggerinterface.h"
#include<QMap>
class LogerTree
{
public:
    static   LogerTree* instance();
    int      connectLogger( QloggerInterface* logger, QloggerInterface::LogId_t dest_logger_id );
    int      disconnectLogger( QloggerInterface* logger );
    int      disconnectLogger( QloggerInterface* logger, QloggerInterface::LogId_t id );
protected:
    explicit LogerTree();
    virtual  bool connect( QloggerInterface* Logg, QloggerInterface* destLogg );//= 0;
    virtual  bool disconnect( QloggerInterface* Logg, QloggerInterface* destLogg );
    virtual  bool isLoggerConected( QloggerInterface* Logg, QloggerInterface::LogId_t dest_logger )                   ;// = 0;
    virtual  QloggerInterface::LogId_t getNewLoggerId()                        ;// = 0;
    virtual  int addToLoggerList( QloggerInterface* log );// = 0;
/*
    QList< QloggerInterface::LogId_t > getConnectionsToLoggerId( QloggerInterface::LogId_t id );
    virtual  QloggerInterface* getLoggerFromId( QloggerInterface::LogId_t id ) ;// = 0;

    virtual  int removeFromLoggerList( QloggerInterface* log )                ;// = 0;
*/
protected:
    static   LogerTree*  m_Tree;
    static   int         m_NextId;
    QMap<QloggerInterface::LogId_t, QloggerInterface*>          m_id_obj_map;   /**/
    QMap<QloggerInterface::LogId_t, QloggerInterface::LogId_t>  m_id_con_map;
};


QloggerInterface::QloggerInterface(QObject * obj, LogId_t id ):m_ConnId(id),m_Id( INALID_ID )
{
    m_myObj = obj;
}

QloggerInterface::LogId_t QloggerInterface::getId()
{
    return m_Id;
}

QloggerInterface::LogId_t QloggerInterface::getConnId()
{
    return m_ConnId;
}

void QloggerInterface::setId( QloggerInterface::LogId_t id)
{
    m_Id = id;
}


bool LogerTree::connect( QloggerInterface* Logg, QloggerInterface* destLogg ){

}

bool LogerTree::disconnect( QloggerInterface* Logg, QloggerInterface* destLogg ){

}

bool LogerTree::isLoggerConected( QloggerInterface* Logg, QloggerInterface::LogId_t dest_logger ){

}


QloggerInterface::LogId_t LogerTree::getNewLoggerId(){
    m_NextId++;
    return m_NextId;
}

int LogerTree::addToLoggerList( QloggerInterface* log  ){
    int ret = -1;
    if( log )
    {
        QloggerInterface* tempLog = m_id_obj_map.value( log->getId(), NULL );
        if( tempLog == NULL )
        {
            m_id_obj_map.insert( log->getId(), log );
            ret = 0;
        }
        else if( tempLog != log )
        {
            //DBG someting wrong - ID not correspond to object???
            ret = -2;
        }
        else
        {
            ret = 1;//Already added
        }
    }
    return ret;
}

/*
QList< QloggerInterface::LogId_t > LogerTree::getConnectionsToLoggerId( QloggerInterface::LogId_t id ){
    return m_id_con_map.values(id);
}

QloggerInterface* LogerTree::getLoggerFromId( QloggerInterface::LogId_t id ){
    return m_id_obj_map.value( id, NULL );
}



int LogerTree::removeFromLoggerList( QloggerInterface* log ){
    int ret = -1;
    if( log )
    {
        m_id_obj_map.remove( log->getId() );
        ret = 0;
    }
    return ret;
}

*/

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
            if( !isLoggerConected( logger, dest_id ) )
            {
                connect( logger, destLogger );
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
                QloggerInterface::LogId_t temp_id;
                QloggerInterface* dest_log;
                for( int i = 0; i < con_ids.count(); i++ )
                {
                    temp_id  = con_ids.value( i, QloggerInterface::INALID_ID );
                    dest_log = m_id_obj_map.value( temp_id, NULL );
                    if( dest_log != NULL && 0 != disconnect( logger, dest_log ) )
                    {
                        //DBG something
                    }
                }
            }
        }
        // ret = removeFromLoggerList( logger );
        // m_id_obj_map.remove( logger->getId() );
        ret = 0;
    }
    return ret;
}

int LogerTree::disconnectLogger( QloggerInterface* logger, QloggerInterface::LogId_t id ){
    int ret = -1;

    if( logger )
    {

    }
    return ret;
}

MainLogger::MainLogger():QloggerInterface( this, QloggerInterface::ROOT_ID )
{

}

LogerTree*  LogerTree::m_Tree;
int  LogerTree::m_NextId;

LogerTree::LogerTree()
{

}



LogerTree* LogerTree::instance()
{
    if( 0 == m_Tree )
    {
        m_Tree = new LogerTree();
        m_Tree->addToLoggerList( new MainLogger() );
    }
    return m_Tree;
}
