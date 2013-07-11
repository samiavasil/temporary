#include "DesignerFrameWork.h"
#include <QDebug>
#include "ui_desinger.h"
#include "base/CCreator.h"
namespace Plugins
{
DesignerFrameWork::DesignerFrameWork(QCreator * creator  , QWidget * parent ):
                        QFrameWork( creator , parent ),ui(new Ui::Designer)
{
    ui->setupUi( this );
    setAttribute(Qt::WA_DeleteOnClose, true);
}

DesignerFrameWork::~DesignerFrameWork()
{
 //qDebug()<<"iooopiop"<<endl<<endl<<endl;
    m_creator->Free();
    delete ui;
}

void DesignerFrameWork::AddWidgetToControlArrea ( QWidget* widget )
{

  if( widget )
      ui->layout->addWidget( widget, ui->layout->count()/3,ui->layout->count()%3   );
}

void DesignerFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{

}
}
