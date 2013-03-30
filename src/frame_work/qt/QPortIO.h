#ifndef _QPORTIO_H
#define _QPORTIO_H


#include "frame_work_global.h"
#include <QObject>

#include "base/CPortIO.h"

class FRAME_WORKSHARED_EXPORT QPortIO : public QObject, public CPortIO {
Q_OBJECT

  public:
    explicit QPortIO(QObject * parent);

signals:
    void readyReadBytesSignal();

};
#endif
