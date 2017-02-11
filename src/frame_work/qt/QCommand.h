#ifndef _QCOMMAND_H
#define _QCOMMAND_H


#include "base/global.h"
#include "base/CCommand.h"
#include <QObject>


class FRAME_WORKSHARED_EXPORT  QCommand : public CCommand, public QObject {
  public:
    QCommand(QObject * parent = 0);

public slots:
    virtual void finish();

};
#endif
