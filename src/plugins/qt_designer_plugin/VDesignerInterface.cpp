#include "VDesignerInterface.h"
#include "DesignerFrameWork.h"
#include "DesignerCreator.h"

#include<QWidget>
namespace Plugins
{


VDesignerInterface::VDesignerInterface(QObject* parent ):QPluginObjectsInterface(parent)
{
    DEBUG("VDesignerInterface object create");
    //m_Icon.addFile(QString::fromUtf8(":/fra/icons/FrameWork.png"));
}

VDesignerInterface::~VDesignerInterface(  )
{
    DEBUG("VDesignerInterface object delete");
}

/* FIX ME - remove input params. New creted here framework should
// have a parent this - In this way we can attach new created QFrameWork
// destroy signal whit FrameWorkInterface onFrameDestroySlot.
// There we check is have aVDesignerInterface->childs, aand
// if No we can call deleteLater  FrameWorkInterface (there are no
// objects associated with VDesignerInterface). This will
// send destroy signal to assoxiates QPluginLoaderExt object and it
// can unload plugin wthout crashes*/
//QFrameWork* VDesignerInterface::getFrameWork( QWidget* parent )
QObject*  VDesignerInterface::allocateObject( QObject* parent ){
    QWidget* parent_widget = 0;
    if( parent && parent->isWidgetType() ){
        parent_widget = dynamic_cast<QWidget *> (parent);
    }
    DesignerCreator* c = new DesignerCreator();
    DesignerFrameWork*fw = new DesignerFrameWork( c,  parent_widget );
    fw->setAttribute(Qt::WA_DeleteOnClose, true); /*Wajno - tova kazwa da se wika delete na
                                                    widget-a pri closeEvent*/
    return fw;

}
}
Q_EXPORT_PLUGIN2(VDesignerPlugin, Plugins::VDesignerInterface )
