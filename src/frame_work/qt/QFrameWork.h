#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include "frame_work_global.h"
#include <QWidget>

#include "base/CFrameWork.h"
#include <QList>


class QCreator;

class FRAME_WORKSHARED_EXPORT QFrameWork : public QWidget, public CFrameWork {
Q_OBJECT

  public:
    explicit QFrameWork(QCreator * creator = 0, QWidget * parent = 0);

    virtual ~QFrameWork();

    bool Create();

    QList<QObject*> CreateObjectFromType(QObject * parent);

signals:
    void fwDestroy();

};
#endif
