#ifndef _QCOMMAND_H
#define _QCOMMAND_H

#include "base/CCommand.h"
#include <QObject>

class QCommand : public CCommand, public QObject {
  public:
    explicit QCommand(QObject * parent = NULL);
  public slots:
    virtual void finish() {}
};
#endif
