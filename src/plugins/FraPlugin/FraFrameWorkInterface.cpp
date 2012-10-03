#include "FraFrameWorkInterface.h"
#include "QFraFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"
FraFrameWorkInterface::FraFrameWorkInterface(QObject* parent ):QObject(parent)
{
    DEBUG("frameworkinterface object created");
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

FraFrameWorkInterface::~FraFrameWorkInterface(  )
{
    DEBUG("frameworkinterface object removed");
}

QFrameWork* FraFrameWorkInterface::getFrameWork( QWidget* parent ){
    // FIX ME - remove input params. New creted here framework should
    // have a parent this - In this way we can attach new created QFrameWork
    // destroy signal whit FrameWorkInterface onFrameDestroySlot.
    // There we check is have aFraFrameWorkInterface->childs, aand
    // if No we can call deleteLater  FrameWorkInterface (there are no
    // objects associated with FraFrameWorkInterface). This will
    // send destroy signal to assoxiates QPluginLoaderExt object and it
    // can unload plugin wthout crashes
    return new QFraFrameWork( new QFrameWorkElementsFactory(), parent/*this*/ );
}



Q_EXPORT_PLUGIN2(pnp_graplugin, FraFrameWorkInterface)
