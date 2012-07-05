#ifndef _QCOMMAND_H
#define _QCOMMAND_H


#include "base/CCommand.h"
#include <QObject>


class QCommand : public CCommand, public QObject {
  public:
    ~QCommand();

    /**
     * Command handler
     */
    virtual int handler() const;

};
#endif
