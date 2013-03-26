#ifndef QFRACREATOR_H
#define QFRACREATOR_H

#include"qt/QCreator.h"

class QFraCreator :  public QCreator
{
public:
    explicit QFraCreator( QObject * parent = NULL );
    virtual void Create(CFrameWork *fW);
    virtual void Free();
};

#endif // QFRACREATOR_H
