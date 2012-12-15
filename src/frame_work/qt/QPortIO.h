#ifndef QPORTIO_H
#define QPORTIO_H

#include <QObject>

class QPortIO : public QObject
{
    Q_OBJECT
public:
    explicit QPortIO(QObject *parent = 0);
    
signals:
    void readyReadBytesSignal();
public slots:
    
};

#endif // QPORTIO_H
