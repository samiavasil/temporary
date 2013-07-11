#ifndef VDESIGNERUI_H
#define VDESIGNERUI_H


#include"qt/QFrameWork.h"
#include "plugin_global.h"
namespace Ui {
class Designer;
}
namespace Plugins
{
class PLUGIN_EXPORT DesignerFrameWork:public QFrameWork
{
    Q_OBJECT
public:
    explicit DesignerFrameWork(QCreator * creator = 0, QWidget * parent = 0);
    virtual ~DesignerFrameWork();
    virtual void AddWidgetToControlArrea ( QWidget* widget );
    virtual void AddWidgetToDataViewArrea( QWidget* widget );


private:
   Ui::Designer   *ui;
};
}
#endif // VDESIGNERUI_H
