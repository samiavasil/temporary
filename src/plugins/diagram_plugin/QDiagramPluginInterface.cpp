#include "QDiagramPluginInterface.h"
#include "DiagMainWindow.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QDiagramPluginInterface::QDiagramPluginInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QDiagramPluginInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QDiagramPluginInterface::~QDiagramPluginInterface(  )
{
    DEBUG << "QDiagramPluginInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aQDiagramPluginInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with QDiagramPluginInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* QDiagramPluginInterface::getFrameWork( QWidget* parent )
QObject*  QDiagramPluginInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }

    QWidget * obj = new DiagMainWindow( );
    obj->setAttribute(Qt::WA_DeleteOnClose, true); /*Wajno - tova kazwa da se wika delete na
                                                    widget-a pri closeEvent*/
    return obj;
}
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(pnp_diagramplugin, QDiagramPluginInterface)
#endif
