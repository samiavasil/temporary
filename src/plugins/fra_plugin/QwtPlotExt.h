#ifndef QWTPLOTEXT_H
#define QWTPLOTEXT_H
#include<qwt/qwt_plot.h>
#include "plugin_global.h"
#include <QObject>
#include<QContextMenuEvent>
class QContextMenuEvent;
class PLUGIN_EXPORT QwtPlotExt : public QwtPlot
{
    Q_OBJECT
public:
    explicit QwtPlotExt( QWidget * = NULL );
    explicit QwtPlotExt( const QwtText &title, QWidget *p = NULL );

    virtual ~QwtPlotExt();
Q_SIGNALS:
    void showContextMenuEvent(QContextMenuEvent *event);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

};

#endif // QWTPLOTEXT_H
