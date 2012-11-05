#include "QDataPlot.h"
#include "ui_qdataplot.h"
#include<QBoxLayout>
#include<QToolBar>
#include<QMenuBar>
#include<qwt/qwt_plot_curve.h>
#include<qwt/qwt_plot_canvas.h>
#include<qwt/qwt_plot_grid.h>
#include<qwt/qwt_plot_zoomer.h>
#include <qwt/qwt_painter.h>
#include <qwt/qwt_plot_layout.h>

QDataPlot::QDataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataPlot)
{
    // add curves
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    QwtPlotCurve *curve2 = new QwtPlotCurve("Curve 2");
    double x[100],y[100],z[100];

    ui->setupUi(this);




    /* */
    QMenuBar* ptr1 = new QMenuBar();
    ptr1->addMenu("ALABALA")->addMenu("BEB");
    ptr1->addMenu("ALABALA")->addMenu("BEB");
    ptr1->addMenu("ALABALA")->addMenu("BEB");
    ptr1->addMenu("ALABALA")->addMenu("BEB");

    QBoxLayout* l = new QBoxLayout( QBoxLayout::TopToBottom, this );
    l->setMenuBar(ptr1);
    QToolBar* ptr = new QToolBar("OPAA");

    ptr->addAction(ui->actionShowTable);
    ptr->addAction(ui->actionAutoscale);
    ptr->addAction(ui->actionGrid_X_on);
    ptr->addAction(ui->actionGrid_Y_on);
    ptr->addAction(ui->actionMagnifier);
    ptr->addAction(ui->actionMagnifier);
    ptr->addAction(ui->actionMouseTrack);
    ptr->addAction(ui->actionRectangle_Zoom);
    //l->setMenuBar(ptr);
    l->addWidget(ptr);
    ptr->show();
    l->addWidget(ui->splitter);

    ptr->addWidget(ui->ComboLineColor);







    ui->PlotQwt->canvas()->setPaintAttribute( QwtPlotCanvas::BackingStore, false );
    ui->PlotQwt->canvas()->setFrameStyle ( QFrame::Box | QFrame::Plain );
    ui->PlotQwt->canvas()->setLineWidth ( 1 );

    //ui->PlotQwt->setMargin ( 5 );
    ui->PlotQwt->enableAxis ( QwtPlot::yRight, true );
    ui->PlotQwt->setAutoReplot ( false );
    ui->PlotQwt->plotLayout()->setAlignCanvasToScales( true );

    ui->PlotQwt->setAxisAutoScale(QwtPlot::yLeft);
    ui->PlotQwt->setAxisAutoScale(QwtPlot::yRight);
    ui->PlotQwt->setAxisAutoScale(QwtPlot::xBottom);

    // We don't need the cache here
    //ui->PlotQwt->canvas()->setPaintAttribute ( QwtPlotCanvas::PaintCached, false );
    //ui->PlotQwt->canvas()->setPaintAttribute ( QwtPlotCanvas::PaintPacked, true );
    //alignScales();

    // Assign a title to plot
    ui->PlotQwt->setTitle ( "Impedance" );
    //ui->PlotQwt->insertLegend ( new QwtLegend(), QwtPlot::BottomLegend );
    ui->PlotQwt->setCanvasBackground ( QColor ( Qt::black ) );
    ui->PlotTable->setVisible( false );






    m_Grid = new QwtPlotGrid;
    m_Grid->enableXMin ( true );
    m_Grid->setMajPen ( QPen ( Qt::green, 0, Qt::DotLine ) );
    m_Grid->setMinPen ( QPen ( Qt::gray , 0, Qt::DotLine ) );
    m_Grid->enableX ( false );
    m_Grid->enableY ( false );
    m_Grid->attach ( ui->PlotQwt );
    m_Grid->setPen ( QPen ( Qt::white ) );




    //DELL ME
    // copy the data into the curves
    for( int i=0; i<100; i++){
        x[i] = i;
        y[i] = i;
        z[i] = 100*sin((6.28*i)/100);
    }
    curve1->attach(ui->PlotQwt);
    curve2->attach(ui->PlotQwt);

    curve1->setSamples( x,y,100 );
    curve2->setSamples( x,z,100 );

    curve1->setPen(QPen(Qt::green));
    curve2->setPen(QPen(Qt::red));
    //;
    //curve1->data()->boundingRect().height();
  //  on_actionAutoscale_triggered();

    // finally, refresh the plot
//    ui->PlotQwt->replot();

   m_Zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yLeft,ui->PlotQwt->canvas());
   m_Zoomer->setTrackerMode(QwtPicker::AlwaysOff);
   //m_Zoomer->setRubberBand(QwtPicker::NoRubberBand);
   m_Zoomer->setRubberBand(QwtPicker::RectRubberBand);
   m_Zoomer->setRubberBandPen(QColor ( Qt::green ) );
   m_Zoomer->setTrackerMode(QwtPicker::ActiveOnly);
   m_Zoomer->setTrackerPen( QColor ( Qt::green ) );

   m_Zoomer->setMousePattern ( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
   m_Zoomer->setMousePattern ( QwtEventPattern::MouseSelect3, Qt::RightButton );



   //  m_Zoomer->initMousePattern(2);

  // m_Zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yRight,ui->PlotQwt->canvas());

  /* m_Zoomer->setMousePattern ( QwtEventPattern::MouseSelect1,
                     Qt::LeftButton );

   m_Zoomer->setMousePattern ( QwtEventPattern::MouseSelect4,
                     Qt::NoButton );
   m_Zoomer->setMousePattern ( QwtEventPattern::MouseSelect6,
                     Qt::NoButton );  */

}

QDataPlot::~QDataPlot()
{
    delete ui;
    if( m_Grid ){
        delete m_Grid;
    }
}


void QDataPlot::on_actionMouseTrack_triggered()
{

}

void QDataPlot::on_actionGrid_X_on_triggered(bool checked)
{
    if( m_Grid ){
        m_Grid->enableX( checked );
        ui->PlotQwt->replot();
    }
}

void QDataPlot::on_actionGrid_Y_on_triggered(bool checked)
{
    if( m_Grid ){
        m_Grid->enableY( checked );
        ui->PlotQwt->replot();
    }

}

void QDataPlot::on_actionShowTable_triggered( bool checked )
{
    ui->PlotTable->setVisible( checked );
}

void QDataPlot::on_actionAutoscale_triggered()
{
    ui->PlotQwt->setAxisAutoScale(QwtPlot::yLeft);
    ui->PlotQwt->setAxisAutoScale(QwtPlot::yRight);
    ui->PlotQwt->setAxisAutoScale(QwtPlot::xBottom);
    ui->PlotQwt->replot();
}
