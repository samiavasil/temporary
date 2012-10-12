#include "FraFrameWorkInterface.h"
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
FraFrameWorkInterface::FraFrameWorkInterface(QObject* parent ):QObject(parent)
{
    DEBUG("FraFrameWorkInterface object create");
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

FraFrameWorkInterface::~FraFrameWorkInterface(  )
{
    DEBUG("FraFrameWorkInterface object delete");
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aFraFrameWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with FraFrameWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* FraFrameWorkInterface::getFrameWork( QWidget* parent )
QObject*  FraFrameWorkInterface::createObject( QObject* parent ){

    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    QObject *new_fw = dynamic_cast<QObject *> ( new QFraFrameWork( new QFrameWorkElementsFactory(), parent_widget ) );
    if( 0 != new_fw ){
        connect( new_fw,SIGNAL(destroyed(QObject*)), this, SLOT(frameWorkDestroyed(QObject*)),Qt::QueuedConnection);
        m_fw_objects.append( new_fw );
    }
    return new_fw;
}

void FraFrameWorkInterface::frameWorkDestroyed( QObject* fw ){
    if(  fw && m_fw_objects.contains(  fw ) ){
        qDebug("Remove from list Destroyed QFraFrameWork[%x]",(unsigned int)fw);
        m_fw_objects.takeAt(m_fw_objects.indexOf( fw ));
        qDebug("On List %d",m_fw_objects.count());
        if( 0 == m_fw_objects.count() ){
           deleteLater();
        }
    }
}

Q_EXPORT_PLUGIN2(pnp_graplugin, FraFrameWorkInterface)
