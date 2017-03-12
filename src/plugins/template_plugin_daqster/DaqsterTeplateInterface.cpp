#include "DaqsterTeplateInterface.h"
#include<qwt/qwt_plot.h>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"
using namespace Daqster;

DaqsterTeplateInterface::DaqsterTeplateInterface(QObject* parent ):QPluginBaseInterface(parent)
{
    DEBUG << "QwtPlotWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

DaqsterTeplateInterface::~DaqsterTeplateInterface(  )
{
    DEBUG << "QwtPlotWorkInterface object delete";
}

Daqster::QBasePluginObject *DaqsterTeplateInterface::createPluginInternal(QObject *Parrent)
{

}



#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(DaqsterTemlatePlugin, DaqsterTeplateInterface)
#endif

