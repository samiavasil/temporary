#include "QCryptoWorkInterface.h"
#include<QWidget>
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QCryptoWorkInterface::QCryptoWorkInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QCryptoWorkInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QCryptoWorkInterface::~QCryptoWorkInterface(  )
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
QObject*  QCryptoWorkInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    QWidget * obj = new QWidget(parent_widget);
    return obj;
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(QCryptoPlugin, QCryptoWorkInterface)
#endif

