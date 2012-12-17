#ifndef _QPORTIO_H
#define _QPORTIO_H


#include <QObject>

#include "base/CPortIO.h"

class QPortIO : public QObject, public CPortIO {
Q_OBJECT

  public:
    explicit QPortIO(QObject * parent);

signals:
    void readyReadBytesSignal();

};
#endif
