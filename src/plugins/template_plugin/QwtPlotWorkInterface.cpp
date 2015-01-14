#include "QwtPlotWorkInterface.h"
#include<qwt/qwt_plot.h>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QwtPlotWorkInterface::QwtPlotWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QwtPlotWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QwtPlotWorkInterface::~QwtPlotWorkInterface(  )
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
QObject*  QwtPlotWorkInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    QWidget * obj = new QwtPlot(parent_widget);
    obj->setWindowTitle( name() );
    obj->setAttribute(Qt::WA_DeleteOnClose, true); /*Wajno - tova kazwa da se wika delete na
                                                    widget-a pri closeEvent*/
    obj->setObjectName( name() );
    return obj;
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(QwtPlotPlugin, QwtPlotWorkInterface)
#endif

