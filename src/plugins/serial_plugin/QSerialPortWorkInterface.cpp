#include "QSerialPortWorkInterface.h"
#include "qt/QSerialPortIO.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QSerialPortWorkInterface::QSerialPortWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QSerialPortWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QSerialPortWorkInterface::~QSerialPortWorkInterface(  )
{
    DEBUG << "QSerialPortWorkInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aQSerialPortWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with QSerialPortWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* QSerialPortWorkInterface::getFrameWork( QWidget* parent )
QObject*  QSerialPortWorkInterface::allocateObject( QObject* parent ){
    return new QSerialPortIO(parent);
}
Q_EXPORT_PLUGIN2(pnp_serialportplugin, QSerialPortWorkInterface)
