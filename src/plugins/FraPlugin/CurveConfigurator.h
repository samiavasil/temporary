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
    explicit CurveConfigurator(QWidget *parent = 0, bool auto_update = false );
    ~CurveConfigurator();
    int addCurve( QwtPlotCurve* curve );
    bool auto_update(){
        return m_AutoUpdate;
    }
    void setAutoUpdate( bool auto_update ){
        m_AutoUpdate = auto_update;
    }

protected:
    void updateConfigurator();

protected slots:
    void cellPressed(int r,int c );
protected:
    QList<QwtPlotCurve*> m_Curves;
    bool m_AutoUpdate;
public slots:
    void on_buttonOk_clicked();

    void applyChanges();

    void on_buttonCancel_clicked();

private:
    Ui::CurveConfigurator *ui;
};

#endif // CURVECONFIGURATOR_H
