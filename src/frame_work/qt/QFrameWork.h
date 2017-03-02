#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H

#include "base/global.h"
#include<QMainWindow>

class QCreator;
class QWidget;

class QFwWidget: public QMainWindow{
    Q_OBJECT
public:
    explicit QFwWidget( QWidget *parent = 0, Qt::WindowFlags f = 0 );
    virtual ~QFwWidget();
    void     closeEvent(QCloseEvent *event);

signals:
    void destroyFW();
};

class FRAME_WORKSHARED_EXPORT QFrameWork : public QObject {
Q_OBJECT
  public:
    explicit QFrameWork(QCreator * creator = 0, QObject *parent = 0);
    virtual ~QFrameWork();
    virtual void AddWidgetToControlArrea ( QWidget* widget ) = 0;
    virtual void AddWidgetToDataViewArrea( QWidget* widget ) = 0;
    virtual bool Create();
    virtual void setCreator(QCreator *creator);
    virtual QMainWindow* getFrameWorkWindow();

signals:
    void fwDestroy();

protected:
     QMainWindow* m_FwWin;
     QCreator* m_creator;

};
#endif
