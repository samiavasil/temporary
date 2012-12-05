#ifndef CURVECONFIGURATIONMENU_H
#define CURVECONFIGURATIONMENU_H
#include <QMenu>
#include "CurveConfigurator.h"

class QWidgetAction;
class CurveConfigurationMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CurveConfigurationMenu(QWidget *parent = 0);
    
signals:
    void setAsCurrent( QwtPlotCurve*  );
public slots:
    void setMenuCurve();

protected slots:
    void setCurent();
    void setVisibleLine(bool visible);
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
protected:
    CurveConfigurator* m_curve_conf;
    QWidgetAction* m_WidedAct;
    QAction* m_actSetCurrent;
    QAction* m_actVisible;
    QwtPlotCurve* m_curCurve;
};

#endif // CURVECONFIGURATIONMENU_H
