#include "VDesignerInterface.h"
#include "DesignerFrameWork.h"
#include "DesignerCreator.h"
#include<QWidget>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"



namespace Plugins
{


VDesignerInterface::VDesignerInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "VDesignerInterface object create";
    //m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

VDesignerInterface::~VDesignerInterface(  )
{
    DEBUG << "VDesignerInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aVDesignerInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with VDesignerInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* VDesignerInterface::getFrameWork( QWidget* parent )
QObject*  VDesignerInterface::allocateObject( QObject* parent ){
    DesignerFrameWork*fw = new DesignerFrameWork(  new DesignerCreator(),  parent);

    return fw;

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(VDesignerPlugin, Plugins::VDesignerInterface )
#endif
