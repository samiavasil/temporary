#ifndef _QPORTIO_H
#define _QPORTIO_H


#include "frame_work_global.h"
#include <QWidget>

#include "base/CPortIO.h"

class FRAME_WORKSHARED_EXPORT QPortIO : public QObject, public CPortIO {
Q_OBJECT

  public:
    explicit QPortIO(QObject * parent);
    virtual ~QPortIO();
    virtual void showPortConfiguration(QWidget * parent) = 0;

signals:
    void readyReadBytesSignal();

protected:
    QWidget* m_PioWidget;
};
#endif
