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

#include "ui_desinger.h"

class PyNotoIntegration: public qdesigner_internal::QDesignerIntegration
{
public:
    PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent = 0);
    ~PyNotoIntegration();
};

PyNotoIntegration::PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent  ):
    qdesigner_internal::QDesignerIntegration(core, parent)
{

    setSlotNavigationEnabled(true);
}

PyNotoIntegration::~PyNotoIntegration()
{

//    delete core()->widgetBox();
//    delete core()->objectInspector();
//    delete core()->propertyEditor();
//    delete core()->actionEditor();
}

DesignerCreator:: DesignerCreator( QObject * parent ):QCreator(parent),ui(new Ui::Designer)
{
}


DesignerCreator::~DesignerCreator( )
{
//    _designer->core()->widgetBox()->deleteLater();
//    _designer->core()->objectInspector()->deleteLater();
//    _designer->core()->propertyEditor()->deleteLater();
//    _designer->core()->actionEditor()->deleteLater();
delete ui;
//    delete _designer;
//    delete _menu;
//    delete form;
}


bool DesignerCreator::Create( CFrameWork *fW )
{
    if( fW )
    {
        DesignerFrameWork* qfW =  dynamic_cast<DesignerFrameWork*>(fW);

        QWidget* wid =   new QWidget( qfW );
        ui->setupUi( wid );
        if( qfW )
        {
            QDesignerFormEditorInterface *iface = QDesignerComponents::createFormEditor( wid->parent() );

            //    QObject* obj = wid->parentWidget();
            _menu = QDesignerComponents::createTaskMenu(iface, wid );

            QStringList m = iface->pluginManager()->pluginPaths();
            m.append("/home/vasil/projects/Daqster/bin/plugins/designer");
            iface->pluginManager()->setPluginPaths( m );
            QDesignerComponents::initializePlugins( iface );
            QDesignerComponents::initializeResources();
//_menu->deleteLater();
          //      wid->layout()->setMenuBar((QWidget*)_menu);

            iface->setTopLevel(wid);
            iface->setWidgetBox(QDesignerComponents::createWidgetBox(iface, wid));

            iface->widgetBox()->setFileName(QLatin1String(":/trolltech/widgetbox/widgetbox.xml"));
            iface->widgetBox()->load();

            iface->setPropertyEditor(QDesignerComponents::createPropertyEditor(iface, wid));
            iface->setObjectInspector(QDesignerComponents::createObjectInspector(iface, wid));
            iface->setActionEditor(QDesignerComponents::createActionEditor(iface, wid));


            _designer = new /*PyNotoIntegration*/qdesigner_internal::QDesignerIntegration(iface, wid);
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
            ui->layout->addWidget( widgetBox, ui->layout->count()/3,ui->layout->count()%3   );

            QWidget * widgetObjectInspector = qobject_cast<QDesignerObjectInspectorInterface *>(_designer->core()->objectInspector());
            ui->layout->addWidget( widgetObjectInspector, ui->layout->count()/3,ui->layout->count()%3   );

            QWidget * widgetPropertyEditor = qobject_cast<QDesignerPropertyEditorInterface * >(_designer->core()->propertyEditor());
            ui->layout->addWidget( widgetPropertyEditor, ui->layout->count()/3,ui->layout->count()%3   );

            QWidget *signalSlotEditor = QDesignerComponents::createSignalSlotEditor(iface, wid);
            ui->layout->addWidget( signalSlotEditor, ui->layout->count()/3,ui->layout->count()%3   );

            QDesignerActionEditorInterface * actionEditor = _designer->core()->actionEditor();
            ui->layout->addWidget( (QWidget*)actionEditor, ui->layout->count()/3,ui->layout->count()%3   );


            //form->setCurrentTool(1);
            form = iface->formWindowManager()->createFormWindow(wid, Qt::Widget );
            ui->layout->addWidget( form, ui->layout->count()/3,ui->layout->count()%3   );

            QFile f("/home/vasil/tmp/Appearance.ui");
            f.open(QIODevice::ReadOnly | QIODevice::Text);
            form->setContents(f.readAll());
            f.close();
            //form->addResourceFile("/home/vasil/tmp/test.qrc");

            //form->setMainContainer(new QWidget(wid));

            form->setGrid(QPoint(10,10));
            //form->setFileName("/home/vasil/tmp/Appearance.ui");
            form->show();

            form->setCurrentTool(0);
            iface->formWindowManager()->setActiveFormWindow(form);
            qfW->AddWidgetToControlArrea( wid );

        }

    }
    return true;
}

void DesignerCreator::Free()
{
   //delete _designer;
}



