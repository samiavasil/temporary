#include "DataPlotWorkInterface.h"
#include "QDataPlot.h"
#include <QDynamicPropertyChangeEvent>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

DataPlotWorkInterface::DataPlotWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "DataPlotWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

DataPlotWorkInterface::~DataPlotWorkInterface(  )
{
    DEBUG << "DataPlotWorkInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aDataPlotWorkInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with DataPlotWorkInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* DataPlotWorkInterface::getFrameWork( QWidget* parent )
QObject*  DataPlotWorkInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;

    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    QWidget * obj = new QDataPlot(parent_widget);
    obj->setAttribute(Qt::WA_DeleteOnClose, true); /*Wajno - tova kazwa da se wika delete na
                                                    widget-a pri closeEvent*/
    obj->setWindowTitle( name() );
/*
    obj->setProperty( "TestPropety", 0 );
    PropertyChangedFilter*  Filter = new PropertyChangedFilter( obj );
    obj->installEventFilter( Filter );
    QObject::connect( Filter, SIGNAL(debug(bool)), m_Debug, SLOT(logEnable(bool) ) );
*/
    return obj;
}
Q_EXPORT_PLUGIN2(pnp_dataplotplugin, DataPlotWorkInterface)
