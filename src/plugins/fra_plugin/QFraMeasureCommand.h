#ifndef QFRAMEASURECOMMAND_H
#define QFRAMEASURECOMMAND_H
#include <qt/QCommand.h>


class QFraMeasurementContext;

class QFraMeasureCommand : public QCommand
{
    Q_OBJECT
public:
    explicit QFraMeasureCommand( QFraMeasurementContext* context, QObject *parent = NULL );
    virtual ~QFraMeasureCommand();
signals:

public slots:

protected:
    virtual int handler();
protected:
    QFraMeasurementContext* m_Ctx;
};

#endif // QFRAMEASURECOMMAND_H
