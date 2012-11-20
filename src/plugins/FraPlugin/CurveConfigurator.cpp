#include "CurveConfigurator.h"
#include "ui_CurveConfigurator.h"


CurveConfigurator::CurveConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveConfigurator)
{
    ui->setupUi(this);
    ui->curvesTable->clear();
    for(int i=0;i<20;i++)
    addCurve( (QwtPlotCurve*)i );

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
    for( int i=0; i < m_Curves.count(); i++ )
    {
        if( i == ui->curvesTable->rowCount() )
        {
            QTableWidgetItem *newItem;
            int new_row = ui->curvesTable->rowCount();
            ui->curvesTable->insertRow(new_row);
            ui->curvesTable->setColumnCount(5);
            for( int j =0; j < 5; j++ ){
                newItem = new QTableWidgetItem(tr("%1,%2").arg(i).arg(j));
                ui->curvesTable->setItem( new_row,j,newItem );
            }
            ui->curvesTable->item(new_row,0)->setBackgroundColor
                    (QColor(qrand()%255,qrand()%255,qrand()%255));
        }
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


