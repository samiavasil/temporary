#ifndef QTESTCOMMAND_H
#define QTESTCOMMAND_H

#include <qt/QCommand.h>
#include "qt/QFrameWork.h"
class QFrameWork;
class QtestCommand : public QCommand
{
    Q_OBJECT
public:
    explicit QtestCommand( QFrameWork* fw, QObject * parent = NULL );
    virtual ~QtestCommand();
signals:
    
public slots:
protected:
    virtual int handler();

    int a;
    QFrameWork* m_fWork;

};

#endif // QTESTCOMMAND_H
