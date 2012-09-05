#ifndef _QCOMMAND_H
#define _QCOMMAND_H


#include "base/CCommand.h"
#include <QObject>


class QFrameWork;

class QCommand : public CCommand, public QObject {
  public:
    QCommand(QFrameWork * fWork = NULL);

    ~QCommand();

    /**
     * Command handler
     */
    virtual int handler();


  protected:
    QFrameWork* m_fWork;

    int a;

};
#endif
