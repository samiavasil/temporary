#include "FraFrameWorkInterface.h"
#include "QFraFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
#include "QFraCreator.h"
FraFrameWorkInterface::FraFrameWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG("FraFrameWorkInterface object create");
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

FraFrameWorkInterface::~FraFrameWorkInterface(  )
{
    DEBUG("FraFrameWorkInterface object delete");
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFraFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aFraFrameWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with FraFrameWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFraFrameWork* FraFrameWorkInterface::getFrameWork( QWidget* parent )
QObject*  FraFrameWorkInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    //return dynamic_cast<QObject *> ( new QFraFrameWork( new QFraFrameWorkElementsFactory(), parent_widget ) );
    QFraCreator* c = new QFraCreator();
    QFraFrameWork*fw = new QFraFrameWork( c ,  parent_widget );
    return fw;
}
Q_EXPORT_PLUGIN2(FraPlugin, FraFrameWorkInterface)
