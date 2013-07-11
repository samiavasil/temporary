#include "DesignerCreator.h"
#include "DesignerFrameWork.h"

#include <QtDesigner>
#include <QtDesigner/qdesigner_components.h>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerComponents>
#include <QtDesigner/QDesignerWidgetBoxInterface>
#include <QtDesigner/QDesignerFormEditorPluginInterface>
#include <QtDesigner/QDesignerFormWindowManagerInterface>
#include <QtDesigner/QDesignerObjectInspectorInterface>
#include <QtDesigner/QDesignerPropertyEditorInterface>

#include<QAction>
#include<QLayout>

#include "internals/qdesigner_integration_p.h"
#include "internals/pluginmanager_p.h"
#include "internals/formwindowbase_p.h"
#include <QMainWindow>
namespace Plugins
{
class PyNotoIntegration: public qdesigner_internal::QDesignerIntegration
{
public:
    PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent = 0):
        qdesigner_internal::QDesignerIntegration(core, parent)
    {
        setSlotNavigationEnabled(true);
    }
};


DesignerCreator:: DesignerCreator( QObject * parent ):QCreator(parent)
{

}


DesignerCreator::~DesignerCreator( )
{

}


bool DesignerCreator::Create( CFrameWork *fW )
{
    if( fW )
    {
        DesignerFrameWork* qfW =  dynamic_cast<DesignerFrameWork*>(fW);

        QWidget* wid =  qfW;
        if( qfW )
        {
            QDesignerFormEditorInterface *iface = QDesignerComponents::createFormEditor(wid);
        //    QObject* obj = wid->parentWidget();
            QObject * _menu = QDesignerComponents::createTaskMenu(iface, wid->parent()  );
            QDesignerComponents::initializePlugins( iface );
            QDesignerComponents::initializeResources();
//_menu->deleteLater();
          //      wid->layout()->setMenuBar((QWidget*)_menu);

            iface->setTopLevel(wid);
            iface->setWidgetBox(QDesignerComponents::createWidgetBox(iface, wid));

            iface->widgetBox()->setFileName(QLatin1String(":/trolltech/widgetbox/widgetbox.xml"));
            iface->widgetBox()->load();

            iface->setPropertyEditor(QDesignerComponents::createPropertyEditor(iface, 0));
            iface->setObjectInspector(QDesignerComponents::createObjectInspector(iface, 0));
            iface->setActionEditor(QDesignerComponents::createActionEditor(iface, 0));


            _designer = new qdesigner_internal::QDesignerIntegration(iface, wid);
            iface->setIntegration(_designer);

            qdesigner_internal::QDesignerIntegration::initializePlugins( iface );

            QDesignerFormEditorPluginInterface *fep;
            foreach (QObject *plugin, QPluginLoader::staticInstances()) {
                if ( (fep = qobject_cast<QDesignerFormEditorPluginInterface*>(plugin)) ) {
                    if (!fep->isInitialized())
                        fep->initialize(_designer->core());

                    QString actionText = fep->action()->text();
                    if (actionText == "Edit Tab Order")
                       QAction * _editTabAction = fep->action();

                    if (actionText == "Edit Buddies")
                       QAction * _editBuddies = fep->action();
                }
            }

            QWidget * widgetBox = _designer->core()->widgetBox();
            //QDesignerWidgetBoxInterface *widgetBox = QDesignerComponents::createWidgetBox(iface, 0);
            qfW->AddWidgetToControlArrea(widgetBox);

            QWidget * widgetObjectInspector = qobject_cast<QDesignerObjectInspectorInterface *>(_designer->core()->objectInspector());
            qfW->AddWidgetToControlArrea(widgetObjectInspector);

            QWidget * widgetPropertyEditor = qobject_cast<QDesignerPropertyEditorInterface * >(_designer->core()->propertyEditor());
            qfW->AddWidgetToControlArrea(widgetPropertyEditor);

            QWidget *signalSlotEditor = QDesignerComponents::createSignalSlotEditor(iface, 0);
            qfW->AddWidgetToControlArrea(signalSlotEditor);

            QDesignerActionEditorInterface * actionEditor = _designer->core()->actionEditor();
            qfW->AddWidgetToControlArrea((QWidget*)actionEditor);
/**/
        }

    }
    return true;
}

void DesignerCreator::Free()
{
   //delete _designer;
}

}


