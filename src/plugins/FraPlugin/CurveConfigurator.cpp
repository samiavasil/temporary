#include "CurveConfigurator.h"
#include "ui_CurveConfigurator.h"


CurveConfigurator::CurveConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveConfigurator)
{
    ui->setupUi(this);
}

CurveConfigurator::~CurveConfigurator()
{
    delete ui;
}

int CurveConfigurator::addCurve( QwtPlotCurve* curve ){
    int ret = -1;
    if( curve ){
        if( !m_Curves.contains( curve ) ){
           m_Curves.append( curve );
        }
        ret = 0;
    }
    updateConfigurator();
    return ret;
}

void CurveConfigurator::updateConfigurator()
{
    ui->curvesTable->clear();
    for( int i=0; i < m_Curves.count(); i++ ){
          /*
              void setStyle( CurveStyle style )
              void setSymbol( const QwtSymbol *s )
              setLegendAttribute( LegendAttribute, bool on = true )
          */
    }

    /*
    ui->availablePlugins->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availablePlugins->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->availablePlugins,SIGNAL(itemChanged(QTableWidgetItem*) ),this, SLOT(listSelectionChanged(QTableWidgetItem*)));
    connect(this,SIGNAL(reload()) ,this, SLOT(reloadPlugins()));
    connect(ui->reloadButton,SIGNAL(clicked()) ,this, SLOT(reloadPlugins()));
    */
}


