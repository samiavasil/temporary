#ifndef _QCREATOR_H
#define _QCREATOR_H


#include "base/global.h"
#include <QObject>

class QFrameWork;

class FRAME_WORKSHARED_EXPORT QCreator : public QObject {
  Q_OBJECT
  public:
    explicit QCreator( QObject * parent = NULL );

    virtual bool Create( QFrameWork * fW ) = 0;

    virtual void Free() = 0;

};
#endif
