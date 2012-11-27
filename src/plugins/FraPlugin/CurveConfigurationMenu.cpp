#include "CurveConfigurationMenu.h"
#include<QWidgetAction>

CurveConfigurationMenu::CurveConfigurationMenu(QWidget *parent) :
    QMenu(parent)
{
    m_WidedAct = new QWidgetAction( this );
    m_curve_conf = new CurveConfigurator(this,true );
    m_WidedAct->setDefaultWidget(m_curve_conf);
    m_WidedAct->setCheckable(true);
    m_WidedAct->setChecked(true);
    addAction(m_WidedAct);

}

void CurveConfigurationMenu::setCurentCurve(){
    QwtPlotCurve* CurCurve;
    QAction* action = dynamic_cast<QAction*>(sender());
   // action;
    if( action ){
        if( action->data().isValid()&&( !action->data().isNull() ) ){
            CurCurve =  dynamic_cast<QwtPlotCurve*>( (QwtPlotCurve*)action->data().toULongLong() );
            if( CurCurve && m_curve_conf ){
                   qDebug("1 %x",(qlonglong)CurCurve);
                 //   m_curve_conf->removeCurves( );
                   m_curve_conf->addCurve( CurCurve );
                  // m_WidedAct->setData((qlonglong)CurCurve);
                    qDebug("2 %x",(qlonglong)CurCurve);

            }
        }
    }
}
