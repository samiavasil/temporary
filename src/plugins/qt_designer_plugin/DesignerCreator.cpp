#include "base/global.h"
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
#include<QPushButton>
/*#include "internals/qdesigner_integration_p.h"
#include "internals/pluginmanager_p.h"
#include "internals/formwindowbase_p.h"*/
#include <QMainWindow>
#include "ui_desinger.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

#include<QDesignerIntegration>
#include "internals/pluginmanager_p.h" //QDesignerPluginManager
class PyNotoIntegration: public QDesignerIntegration
{
public:
    PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent = 0);
    ~PyNotoIntegration();
};

PyNotoIntegration::PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent  ):
    QDesignerIntegration(core, parent)
{

    // setSlotNavigationEnabled(true);   TODO WHAT ????
    setFeatures( 0 );

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

#include <QGridLayout>

bool DesignerCreator::Create(QFrameWork *fW )
{
    if( fW )
    {
        DesignerFrameWork* qfW =  dynamic_cast<DesignerFrameWork*>(fW);

        QWidget* wid =  new QWidget( qfW->getFrameWorkWindow() );


        /*Add plugins path*/
        QStringList mm = QCoreApplication::libraryPaths();
        mm.append("./plugins");
        QCoreApplication::setLibraryPaths( mm );

        ui->setupUi( wid );
        if( qfW )
        {
            QDesignerFormEditorInterface *iface = QDesignerComponents::createFormEditor( wid );

            //    QObject* obj = wid->parentWidget();
            _menu = QDesignerComponents::createTaskMenu(iface, wid );
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


            _designer = new  PyNotoIntegration (iface, wid);

            iface->setIntegration(_designer);

            QDesignerIntegration::initializePlugins( iface );

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
            ui->widgetsLayout->addWidget( widgetBox  );

            QWidget * widgetObjectInspector = qobject_cast<QDesignerObjectInspectorInterface *>(_designer->core()->objectInspector());
            ui->objectsLayout->addWidget( widgetObjectInspector  );

            QWidget * widgetPropertyEditor = qobject_cast<QDesignerPropertyEditorInterface * >(_designer->core()->propertyEditor());
            ui->propertyLayout->addWidget( widgetPropertyEditor );

            QWidget *signalSlotEditor = QDesignerComponents::createSignalSlotEditor(iface, wid);
            ui->signalslotsLayout->addWidget( signalSlotEditor );

            QDesignerActionEditorInterface * actionEditor = _designer->core()->actionEditor();
            ui->actionLayout->addWidget( (QWidget*)actionEditor   );



            form = iface->formWindowManager()->createFormWindow(wid, Qt::Widget );
            form->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            //  ui->scrollArea->setBackgroundRole(QPalette::Shadow);
            ui->scrollArea->setWidgetResizable(true);
            ui->scrollArea->setWidget( form   );
            ui->scrollArea->setAlignment( Qt::AlignHCenter| Qt::AlignVCenter);
            QSize size = ui->scrollArea->size();
            size.setWidth(size.width()/2);
            size.setHeight(size.height()/2);
            ui->scrollArea->setWidgetResizable(true);
            form->resize(size);

            form->setFileName("./plugins/test/Appearance.ui");
            QFile f(form->fileName());
            f.open(QIODevice::ReadOnly | QIODevice::Text);
            form->setContents(f.readAll());
            f.close();

            //form->addResourceFile("/home/vasil/tmp/test.qrc");

            // form->setMainContainer(new QWidget(wid));

            form->setGrid(QPoint(10,10));
            //form->setFileName("/home/vasil/tmp/Appearance.ui");
            form->show();
            iface->formWindowManager()->setActiveFormWindow(form);
            form->setCurrentTool(0);

            connect(ui->runButton,SIGNAL(clicked()),this,SLOT(save()));
            //   qfW->AddWidgetToControlArrea( saveBtn );
            //qfW->AddWidgetToControlArrea( wid );
            //          grid->addWidget(saveBtn,0,0,1,1);

            //grid->addWidget(wid,0,1,1,1);

            qfW->getFrameWorkWindow()->setCentralWidget(wid);
            wid->show();
            // qfW->AddWidgetToControlArrea(loadUiFile());


        }

    }
    return true;
}
#include<QtUiTools>
#include<QFile>
QWidget* DesignerCreator::loadUiFile( QWidget* parent, QString& file_name )
{
    QUiLoader loader;
    loader.addPluginPath("/home/vasil/Projects/Daqster/bin/plugins/designer");
    QFile file( file_name );
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load( &file, parent );
    file.close();
    connect( formWidget, SIGNAL(destroyed()), this, SLOT(Free()) );
    formWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    return formWidget;
}

void DesignerCreator::save()
{
    QString fname( form->fileName() );
    QFile file( fname );
    file.open( QFile::WriteOnly );
    file.write(form->contents().toLatin1());
    file.close();

    loadUiFile( NULL,fname)->show();
}

void DesignerCreator::Free()
{
    DEBUG << "Frees";
}



