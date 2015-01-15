#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include "frame_work_global.h"
#include "base/CFrameWork.h"
#include<QMainWindow>
#include <QList>
#include <QObject>

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

class FRAME_WORKSHARED_EXPORT QFrameWork : public QObject, public CFrameWork {
Q_OBJECT

  public:
    explicit QFrameWork(QCreator * creator = 0, QObject *parent = 0);

    virtual ~QFrameWork();

//    bool Create();

    virtual void AddWidgetToControlArrea ( QWidget* widget ) = 0;
    virtual void AddWidgetToDataViewArrea( QWidget* widget ) = 0;
    virtual QWidget* getFrameWorkWindow(){
        return m_FwWin;
    }
signals:
    void fwDestroy();

protected:
     QMainWindow* m_FwWin;

};
#endif
