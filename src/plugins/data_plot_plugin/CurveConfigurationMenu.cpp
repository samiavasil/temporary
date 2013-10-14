#include "base/global.h"
#include "CurveConfigurationMenu.h"
#include<QWidgetAction>

CurveConfigurationMenu::CurveConfigurationMenu(QWidget *parent) :
    QMenu(parent)
{
    m_curCurve      = NULL;
    m_actSetCurrent = new QAction( "Set As Current Line", this );
    m_actSetCurrent->setCheckable(false);
    addAction( m_actSetCurrent );
    m_actVisible = new QAction( "Visible", this );
    m_actVisible->setCheckable(true);
    m_actVisible->setChecked(false);
    addAction( m_actVisible );
    m_WidedAct = new QWidgetAction( this );
    m_curve_conf = new CurveConfigurator( this, true );
    m_WidedAct->setDefaultWidget(m_curve_conf);
    addAction(m_WidedAct);
    connect( m_actSetCurrent, SIGNAL( triggered() ) , this, SLOT( setCurent() ), Qt::DirectConnection );
    connect( m_actVisible   , SIGNAL( toggled(bool)), this, SLOT(setVisibleLine( bool )), Qt::DirectConnection );
}
void CurveConfigurationMenu::mousePressEvent ( QMouseEvent * event ){
    if( activeAction() != m_WidedAct  ){
          QMenu::mousePressEvent (  event );
          DEBUG( " activeAction() != m_WidedAct" );
    }
    else{
        DEBUG( " activeAction() == m_WidedAct" );
    }
}

void CurveConfigurationMenu::setVisibleLine( bool visible ){
        if( m_curCurve ){
            m_curCurve->setVisible( visible );
        }
        else{
            DEBUG( "Errror!!Not defined curCurve" );
        }
}

void CurveConfigurationMenu::setCurent(){
    if( m_curCurve ){
       emit setAsCurrent( m_curCurve );
    }
    else{
        DEBUG( "Errror!!Not defined curCurve" );
    }
}

void CurveConfigurationMenu::setMenuCurve(){

    QAction* action = dynamic_cast<QAction*>(sender());
    // action;
    if( action ){
        if( action->data().isValid()&&( !action->data().isNull() ) ){
            m_curCurve =  dynamic_cast<QwtPlotCurve*>( (QwtPlotCurve*)action->data().toULongLong() );
            if( m_curCurve && m_curve_conf ){
                DEBUG("1 %x",(qlonglong)m_curCurve);
                m_curve_conf->removeCurves( );
                m_curve_conf->addCurve( m_curCurve );
                m_actVisible->setChecked( m_curCurve->isVisible() );
            }
        }
    }
}
