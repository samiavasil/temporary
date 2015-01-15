#ifndef VDESIGNERUI_H
#define VDESIGNERUI_H


#include"qt/QFrameWork.h"


class   DesignerFrameWork:public QFrameWork
{
    Q_OBJECT
public:
    explicit DesignerFrameWork(QCreator * creator = 0, QObject *  parent = 0);
    virtual ~DesignerFrameWork();
    virtual void AddWidgetToControlArrea ( QWidget* widget );
    virtual void AddWidgetToDataViewArrea( QWidget* widget );
};

#endif // VDESIGNERUI_H
