#ifndef _QCOMMAND_H
#define _QCOMMAND_H

#include "base/global.h"
#include <QObject>

class FRAME_WORKSHARED_EXPORT  QCommand : public QObject {
  public:
    QCommand(QObject * parent = 0);
    virtual int handler() = 0;
public slots:
    virtual void finish();

};
#endif
