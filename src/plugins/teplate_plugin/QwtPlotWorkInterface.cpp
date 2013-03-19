#include "QwtPlotWorkInterface.h"
#include<qwt/qwt_plot.h>

QwtPlotWorkInterface::QwtPlotWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG("QwtPlotWorkInterface object create");
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QwtPlotWorkInterface::~QwtPlotWorkInterface(  )
{
    DEBUG("QwtPlotWorkInterface object delete");
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
    QWidget * obj = new QWidget(parent_widget);//TODOOOOOOOOOOOOOOOOOOOOOOOOOO
    new QwtPlot( obj );
    return obj;
}
Q_EXPORT_PLUGIN2(pnp_qwtplotplugin, QwtPlotWorkInterface)
