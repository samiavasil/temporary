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

protected:
    CurveConfigurator* m_curve_conf;
    QWidgetAction* m_WidedAct;
};

#endif // CURVECONFIGURATIONMENU_H
