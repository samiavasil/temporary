#ifndef QTESTCOMMAND_H
#define QTESTCOMMAND_H

#include <qt/QCommand.h>

class QtestCommand : public QCommand
{
    Q_OBJECT
public:
    explicit QtestCommand(QFrameWork * fWork);
    ~QtestCommand();
    
signals:
    
public slots:
    
};

#endif // QTESTCOMMAND_H
