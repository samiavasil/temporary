#ifndef QDBG_H
#define QDBG_H

#include <QObject>
#include<QString>
#include<QEvent>



class PropertyChangedFilter : public QObject
{
    Q_OBJECT
public:
    explicit PropertyChangedFilter(  QObject *parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void debug( bool );
};



class QDbg : public QObject
{
    Q_OBJECT
public:
    explicit QDbg( const QString& s, QObject *parent = 0);
    ~QDbg( );
    void log(QString Bla);
signals:
    
public slots:
    void logEnable( bool en );
protected:
    QString m_Local;
    bool    m_Enable;
    static int ctr;
    int m_ctr;
};

int EnableQDbg( QDbg* qdb, bool en );
#endif // QDBG_H
