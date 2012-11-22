#include "CurveConfigurator.h"
#include "ui_CurveConfigurator.h"
#include "qwt/qwt_symbol.h"
#include "qwt/qwt_plot.h"
#include <QColorDialog>

enum{
    LINE_NAME_COL ,
    LINE_COLOR_COL,
    LINE_STYLE_COL,
    SYMBOL_STYLE_COL,
    COLUMS_NUM
};

typedef struct curve_styles_names_{
    const char* name;
    QwtPlotCurve::CurveStyle style;
} curve_styles_names_t;


typedef struct curve_symbol_styles_{
    const char* name;
    QwtSymbol::Style style;
} curve_symbol_styles_t;

static curve_styles_names_t curve_styles_names[]={
    {"No Curve",QwtPlotCurve::NoCurve},
    {"Lines"   ,QwtPlotCurve::Lines  },
    {"Sticks"  ,QwtPlotCurve::Sticks },
    {"Steps"   ,QwtPlotCurve::Steps  },
    {"Dots"    ,QwtPlotCurve::Dots   },

};

static curve_symbol_styles_t curve_symbol_styles[]={
    { "No Style"          ,QwtSymbol::NoSymbol  },
    { "Ellipse or circle" ,QwtSymbol::Ellipse   },
    { "Rectangle"         ,QwtSymbol::Rect      },
    { "Diamond"           ,QwtSymbol::Diamond   },
    { "Triangle upwards"  ,QwtSymbol::Triangle  },
    { "Triangle downwards",QwtSymbol::DTriangle },
    { "Triangle upwards"  ,QwtSymbol::UTriangle },
    { "Triangle left"     ,QwtSymbol::LTriangle },
    { "Triangle right"    ,QwtSymbol::RTriangle },
    { "Cross"             ,QwtSymbol::Cross     },
    { "Diagonal cross"    ,QwtSymbol::XCross    },
    { "Horizontal line"   ,QwtSymbol::HLine     },
    { "Vertical line"     ,QwtSymbol::VLine     },
    { "X combined with +" ,QwtSymbol::Star1     },
    { "Six-pointed star"  ,QwtSymbol::Star2     },
    { "Hexagon"           ,QwtSymbol::Hexagon   },

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
    header_list << "Line Name" << "Line Color"<<"Line Style"<<"Line Symbol Style"<<"Dran Dran Dran";
    ui->curvesTable->setHorizontalHeaderLabels(header_list);
    ui->curvesTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->curvesTable->setSelectionMode( QAbstractItemView::NoSelection);

    QPalette palete = ui->curvesTable->palette();
    palete.setColor( QPalette::Background,QColor(255,0,0) );
    ui->curvesTable->setBackgroundRole ( QPalette::NoRole );
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

                // newItem = new QTableWidgetItem();
                QComboBox* combo = new  QComboBox(ui->curvesTable);
                for( int j=0; j < ( sizeof(curve_styles_names)/sizeof(curve_styles_names[0]) ); j++ ){
                    combo->addItem( curve_styles_names[j].name );
                    if( curve_styles_names[j].style == curve->style() ){
                        combo->setCurrentIndex(j);
                    }
                }
                ui->curvesTable->setCellWidget( new_row,LINE_STYLE_COL,combo);

                combo = new  QComboBox( ui->curvesTable );
                for( int j=0; j < ( sizeof(curve_symbol_styles)/sizeof(curve_symbol_styles[0]) ); j++ ){
                    combo->addItem( curve_symbol_styles[j].name );
                    if( curve->symbol()&&( curve_symbol_styles[j].style == curve->symbol()->style() ) ){
                        combo->setCurrentIndex(j);
                    }
                }
                ui->curvesTable->setCellWidget( new_row,SYMBOL_STYLE_COL,combo);

            }
        }
    }
    ui->curvesTable->resizeColumnsToContents();
    /*
    ui->availablePlugins->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availablePlugins->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->availablePlugins,SIGNAL(itemChanged(QTableWidgetItem*) ),this, SLOT(listSelectionChanged(QTableWidgetItem*)));
    connect(this,SIGNAL(reload()) ,this, SLOT(reloadPlugins()));
    connect(ui->reloadButton,SIGNAL(clicked()) ,this, SLOT(reloadPlugins()));
    */

}


void CurveConfigurator::cellPressed( int r, int c ){
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
    bool change_symbol;
    for( int i = 0; i < m_Curves.count(); i++ )
    {
        change_symbol = false;
        curve = m_Curves.value( i, NULL );
        if( curve ){
            if( NULL == plot ){
                plot = curve->plot();
            }
            /*Set title*/
            curve->setTitle( ui->curvesTable->item( i,LINE_NAME_COL )->text() );
            if( curve->pen().color() !=  ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() ){
                /*Set color*/
                pen = curve->pen();
                pen.setColor( ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() );
                curve->setPen( pen );
                if( curve->symbol() ){
                    change_symbol = true;
                }
            }


            if( ui->curvesTable->cellWidget( i,LINE_STYLE_COL) ){
                QComboBox* combo = static_cast<QComboBox*>(ui->curvesTable->cellWidget( i,LINE_STYLE_COL));
                if( curve_styles_names[combo->currentIndex()].style != curve->style() ){
                    curve->setStyle( curve_styles_names[combo->currentIndex()].style );
                }
            }

            if( ui->curvesTable->cellWidget( i,SYMBOL_STYLE_COL) ){
                QComboBox* combo = static_cast<QComboBox*>(ui->curvesTable->cellWidget( i,SYMBOL_STYLE_COL));
                if( curve_symbol_styles[combo->currentIndex()].style != curve->style() ){
                    change_symbol = true;
                }
            }

            if( change_symbol ){
                /*Set color*/
                pen = curve->pen();
                pen.setColor( ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() );
                QComboBox* combo = static_cast<QComboBox*>(ui->curvesTable->cellWidget( i,SYMBOL_STYLE_COL));
                QSize symbol_size(5,5);
                if( curve->symbol() ){
                   symbol_size   = curve->symbol()->size();
                }
                QwtSymbol* sym = new QwtSymbol( curve_symbol_styles[combo->currentIndex()].style,
                                                curve->brush(),curve->pen(),
                                                symbol_size );
                sym->setPen(pen);
                sym->setColor(QColor(ui->curvesTable->item( i,LINE_COLOR_COL )->backgroundColor() ));
                curve->setSymbol( sym );
            }
            /**/

            //  curve->setLegendAttribute( LegendAttribute, bool on = true )



        }
    }
    if( plot ){
        plot->replot();
    }

}

void CurveConfigurator::on_buttonCancel_clicked()
{

}
