#include "CurveConfigurator.h"
#include "ui_CurveConfigurator.h"
#include "qwt/qwt_symbol.h"
#include "qwt/qwt_plot.h"

enum{
     LINE_NAME_COL ,
     LINE_COLOR_COL,
     LINE_STYLE_COL,
     COLUMS_NUM
};

CurveConfigurator::CurveConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveConfigurator)
{

    ui->setupUi(this);
    ui->curvesTable->clear();
    ui->curvesTable->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    ui->curvesTable->horizontalHeader()->setStretchLastSection( true );

    ui->curvesTable->setColumnCount(5);
    QStringList header_list;
    header_list << "Line Name" << "Line Color"<<"Dran"<<"Dran Dran"<<"Dran Dran Dran";
    ui->curvesTable->setHorizontalHeaderLabels(header_list);
    ui->curvesTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->curvesTable->setSelectionMode( QAbstractItemView::NoSelection);

    connect(ui->curvesTable,SIGNAL(cellPressed(int,int)),this,SLOT(cellPressed(int,int)));
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
#include<QComboBox>
void CurveConfigurator::updateConfigurator()
{
    QwtPlotCurve* curve;
    for( int i = 0; i < m_Curves.count(); i++ )
    {
        if( i == ui->curvesTable->rowCount() )
        {
            QTableWidgetItem *newItem;
            curve = m_Curves.value( i, NULL );
            if( curve ){
                int new_row = ui->curvesTable->rowCount();
                ui->curvesTable->insertRow(new_row);


                newItem = new QTableWidgetItem( tr("%1").arg(curve->title().text()) );
                ui->curvesTable->setItem( new_row,LINE_NAME_COL ,newItem );

                newItem = new QTableWidgetItem();
                newItem->setBackgroundColor( curve->pen().color() );
                ui->curvesTable->setItem( new_row,LINE_COLOR_COL,newItem );

                newItem = new QTableWidgetItem();

                ui->curvesTable->setCellWidget( new_row,LINE_STYLE_COL,new  QComboBox(ui->curvesTable));

              //  ui->curvesTable->setItem( ,newItem );

                //ui->curvesTable->setItem( new_row,2,newItem );

            }
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

#include <QColorDialog>
void CurveConfigurator::cellPressed(int r,int c ){
    QwtPlotCurve* curve = m_Curves.value( r, NULL );
    if( curve ){
        if( LINE_COLOR_COL == c ){
            QColorDialog color( curve->pen().color(), this );
            if( QDialog::Accepted == color.exec() ){
                ui->curvesTable->item(r,c)->setBackgroundColor( color.selectedColor() );
            }
        }
    }
}

void CurveConfigurator::on_buttonOk_clicked()
{

}

void CurveConfigurator::on_buttonApply_clicked()
{
    QwtPlotCurve* curve;
    QwtPlot* plot = NULL;
    QPen pen;
    for( int i = 0; i < m_Curves.count(); i++ )
    {
        curve = m_Curves.value( i, NULL );
        if( curve ){
            if( NULL == plot ){
                plot = curve->plot();
            }
            /*Set title*/
            curve->setTitle( ui->curvesTable->item( i,LINE_NAME_COL )->text() );
            /*Set color*/
            pen = curve->pen();
            pen.setColor( ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() );
            curve->setPen( pen );
            if( curve->symbol() ){
                QwtSymbol* sym = new QwtSymbol( curve->symbol()->style(), curve->symbol()->brush(),
                                                curve->symbol()->pen(), curve->symbol()->size() );
                sym->setPen(pen);
                sym->setColor(QColor(ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() ));
                curve->setSymbol( sym );
            }
        }
    }
    if( plot ){
        plot->replot();
    }

}

void CurveConfigurator::on_buttonCancel_clicked()
{

}
