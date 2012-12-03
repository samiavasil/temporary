#include "CurveConfigurationMenu.h"
#include<QWidgetAction>

CurveConfigurationMenu::CurveConfigurationMenu(QWidget *parent) :
    QMenu(parent)
{
    m_actSetCurrent = new QAction( "Current Line", this );
    m_actSetCurrent->setCheckable(true);
    m_actSetCurrent->setChecked(true);
    addAction( m_actSetCurrent );
    m_actVisible = new QAction( "Visible", this );
    m_actVisible->setCheckable(true);
    m_actVisible->setChecked(true);
    addAction( m_actVisible );
    m_WidedAct = new QWidgetAction( this );
    m_curve_conf = new CurveConfigurator( this, true );
    m_WidedAct->setDefaultWidget(m_curve_conf);
    addAction(m_WidedAct);
    connect( m_actSetCurrent, SIGNAL( triggered() ) , this, SLOT( setCurent() ) );
    connect( m_actVisible   , SIGNAL( toggled(bool)), this, SLOT(setVisible( bool )) );
}

void CurveConfigurationMenu::setVisible( bool visible ){

}

void CurveConfigurationMenu::setCurent(){

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
                   m_curve_conf->removeCurves( );
                   m_curve_conf->addCurve( CurCurve );
                  // m_WidedAct->setData((qlonglong)CurCurve);
                    qDebug("2 %x",(qlonglong)CurCurve);

            }
        }
    }
}
