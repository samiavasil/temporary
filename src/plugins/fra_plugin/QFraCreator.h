#ifndef QFRACREATOR_H
#define QFRACREATOR_H
#include "plugin_global.h"
#include"qt/QCreator.h"
#include "qt/QFrameWork.h"

class PLUGIN_EXPORT QFraCreator :  public QCreator
{
    Q_OBJECT
public:
    explicit QFraCreator( QObject * parent = NULL );
    ~QFraCreator( );
    virtual bool Create(CFrameWork *fW);
public slots:
    virtual void Free();
protected:


};

#endif // QFRACREATOR_H
