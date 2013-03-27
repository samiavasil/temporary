#ifndef QFRACREATOR_H
#define QFRACREATOR_H

#include"qt/QCreator.h"


class QFraCreator :  public QCreator
{
public:
    explicit QFraCreator( QObject * parent = NULL );
    ~QFraCreator( );
    virtual bool Create(CFrameWork *fW);
    virtual void Free();
protected:


};

#endif // QFRACREATOR_H
