#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include "frame_work_global.h"
#include "base/CFrameWork.h"
#include <QList>
#include <QObject>

class QCreator;
class QWidget;

class FRAME_WORKSHARED_EXPORT QFrameWork : public QObject, public CFrameWork {
Q_OBJECT

  public:
    explicit QFrameWork(QCreator * creator = 0, QObject *parent = 0);

    virtual ~QFrameWork();

//    bool Create();

    virtual void AddWidgetToControlArrea ( QWidget* widget ) = 0;
    virtual void AddWidgetToDataViewArrea( QWidget* widget ) = 0;
    virtual QWidget* getFrameWorkWindow(  ) = 0;
signals:
    void fwDestroy();

};
#endif
