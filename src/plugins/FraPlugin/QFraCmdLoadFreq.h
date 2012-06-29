#ifndef _QFRACMDLOADFREQ_H
#define _QFRACMDLOADFREQ_H
#include "global.h"

#include "basic/QCommand.h"
#include <QObject>


class QFraProtocolPacketsFabrique;
class QFrameWork;

class MYSHAREDLIB_EXPORT QFraCmdLoadFreq : public QCommand {
protected:
typedef enum{
      LF_INIT,
      LF_SEND_FEQ,
      LF_WAIT_ACK
}LoadFreqStates;

  protected:
    LoadFreqStates m_state;

    int local_number;

    static int number;


  public:
QFraCmdLoadFreq(QObject * parent = NULL);

virtual bool handler(QFrameWork * frame_work);

};
#endif
