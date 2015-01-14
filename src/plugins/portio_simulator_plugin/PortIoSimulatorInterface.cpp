#include "PortIoSimulatorInterface.h"
#include <QPortIOSimulator.h>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

PortIoSimulatorInterface::PortIoSimulatorInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QwtPlotWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

PortIoSimulatorInterface::~PortIoSimulatorInterface(  )
{
    DEBUG << "QwtPlotWorkInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aQwtPlotWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with QwtPlotWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* QwtPlotWorkInterface::getFrameWork( QWidget* parent )
QObject*  PortIoSimulatorInterface::allocateObject( QObject* parent ){
    return new QPortIOSimulator(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(portio_simulator_plugin, PortIoSimulatorInterface)
#endif
