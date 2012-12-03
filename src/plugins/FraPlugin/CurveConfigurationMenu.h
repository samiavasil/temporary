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
    
public slots:
    void setCurentCurve();

protected slots:
    void setCurent();
    void setVisible(bool visible);
protected:
    CurveConfigurator* m_curve_conf;
    QWidgetAction* m_WidedAct;
     QAction* m_actSetCurrent;
     QAction* m_actVisible;
};

#endif // CURVECONFIGURATIONMENU_H
