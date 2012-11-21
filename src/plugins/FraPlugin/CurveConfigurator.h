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

protected slots:
    void cellPressed(int r,int c );
protected:
    QList<QwtPlotCurve*> m_Curves;
private slots:
    void on_buttonOk_clicked();

    void on_buttonApply_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::CurveConfigurator *ui;
};

#endif // CURVECONFIGURATOR_H
