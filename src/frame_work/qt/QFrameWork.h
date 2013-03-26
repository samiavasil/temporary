#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include <QWidget>

#include "base/CFrameWork.h"
#include "qt/QCreator.h"

class QFrameWorkElementsFactory;

class Q_DECL_EXPORT QFrameWork : public QWidget, public CFrameWork {
Q_OBJECT

  public:
    QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent = 0);
    explicit QFrameWork( QCreator* creator = NULL , QWidget * parent = 0 );

    virtual ~QFrameWork();
    QList<QObject*>  CreateObjectFromType( );
};
#endif
