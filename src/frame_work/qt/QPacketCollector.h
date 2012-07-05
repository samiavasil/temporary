#ifndef _QPACKETCOLLECTOR_H
#define _QPACKETCOLLECTOR_H


#include <QObject>

#include "base/CPacketCollector.h"

class QPacketCollector : public QObject, public CPacketCollector {
};
#endif
