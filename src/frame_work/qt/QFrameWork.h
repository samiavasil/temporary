#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include "base/CFrameWork.h"
#include <QWidget>


class QFrameWorkElementsFactory;

class Q_DECL_EXPORT QFrameWork : public QWidget,public CFrameWork  {
Q_OBJECT
public:
    QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent = 0);
    virtual ~QFrameWork(){ qDebug("Destroy QFrameWork");}
};
#endif
