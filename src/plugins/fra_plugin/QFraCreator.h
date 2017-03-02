#ifndef QFRACREATOR_H
#define QFRACREATOR_H
#include "plugin_global.h"
#include"qt/QCreator.h"
//#include "qt/QFrameWork.h"
class CFrameWork;
class QFraFrameWork;
class QwtPlotItem;

class PLUGIN_EXPORT QFraCreator :  public QCreator
{
    Q_OBJECT
public:
    explicit QFraCreator( QObject * parent = NULL );
    virtual ~QFraCreator( );
    virtual bool Create(QFrameWork *fW);
public slots:
    virtual void Free();
protected:
    QFraFrameWork* m_qfW;

};

#endif // QFRACREATOR_H
