#include "QTcpIpPortWorkInterface.h"
#include "qt/QSerialPortIO.h"//TODO Fix me

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QTcpIpPortWorkInterface::QTcpIpPortWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QTcpIpPortWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QTcpIpPortWorkInterface::~QTcpIpPortWorkInterface(  )
{
    DEBUG << "QTcpIpPortWorkInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aQTcpIpPortWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with QTcpIpPortWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* QTcpIpPortWorkInterface::getFrameWork( QWidget* parent )
QObject*  QTcpIpPortWorkInterface::allocateObject( QObject* parent ){
    return new QSerialPortIO(parent);
}
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(pnp_serialportplugin, QTcpIpPortWorkInterface)
#endif
