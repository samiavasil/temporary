#include "QhexEditInterface.h"
#include "qhexedit/qhexedit.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QhexEditInterface::QhexEditInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG << "QhexEditInterface object create";
    m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

QhexEditInterface::~QhexEditInterface(  )
{
    DEBUG << "QhexEditInterface object delete";
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aQhexEditInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with QhexEditInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* QhexEditInterface::getFrameWork( QWidget* parent )
QObject*  QhexEditInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    QHexEdit * obj = new QHexEdit(parent_widget);
    QByteArray byte;
    qsrand( 12345 );
    for( int i=0 ; i< 10000;i++ )
        byte.append(qrand());
    obj->setData( byte );
    obj->setWindowTitle( name() );
    obj->setObjectName( name() );
    obj->setAttribute(Qt::WA_DeleteOnClose, true); /*Wajno - tova kazwa da se wika delete na
                                                    widget-a pri closeEvent*/
    return obj;
}
Q_EXPORT_PLUGIN2(pnp_hexeditplugin, QhexEditInterface)
