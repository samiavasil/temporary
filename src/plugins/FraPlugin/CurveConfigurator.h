#ifndef CURVECONFIGURATOR_H
#define CURVECONFIGURATOR_H

#include <QWidget>
#include <QList>
#include "qwt/qwt_plot_curve.h"

namespace Ui {
class CurveConfigurator;
}

class CurveConfigurator : public QWidget
{
    Q_OBJECT
    
public:
    explicit CurveConfigurator(QWidget *parent = 0);
    ~CurveConfigurator();
    int addCurve( QwtPlotCurve* curve );

protected:
    void updateConfigurator();
protected:
    QList<QwtPlotCurve*> m_Curves;
private:
    Ui::CurveConfigurator *ui;
};

#endif // CURVECONFIGURATOR_H
