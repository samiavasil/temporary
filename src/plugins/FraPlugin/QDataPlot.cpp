#include "QDataPlot.h"
#include "ui_qdataplot.h"
#include<QBoxLayout>
#include<QToolBar>
#include<qwt/qwt_plot_curve.h>
#include<qwt/qwt_plot_canvas.h>
#include<QMenuBar>
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

    ui->PlotQwt->enableAxis ( QwtPlot::yRight, true );
    // We don't need the cache here
    //ui->PlotQwt->canvas()->setPaintAttribute ( QwtPlotCanvas::PaintCached, false );
    //ui->PlotQwt->canvas()->setPaintAttribute ( QwtPlotCanvas::PaintPacked, true );
    //alignScales();

    // Assign a title to plot
    ui->PlotQwt->setTitle ( "Impedance" );

    //ui->PlotQwt->insertLegend ( new QwtLegend(), QwtPlot::BottomLegend );
    ui->PlotQwt->setCanvasBackground ( QColor ( Qt::black ) );

    //DELL ME
    // copy the data into the curves
    for( int i=0; i<100; i++){
        x[i] = i;
        y[i] = i;
        z[i] = 100*sin((6.28*i)/100);
    }
    curve1->setSamples( x,y,100 );
    curve2->setSamples( x,z,100 );

    curve1->setPen(QPen(Qt::green));
    curve2->setPen(QPen(Qt::darkRed));
    curve1->attach(ui->PlotQwt);
    curve2->attach(ui->PlotQwt);

    // finally, refresh the plot
    ui->PlotQwt->replot();



}

QDataPlot::~QDataPlot()
{
    delete ui;
}
