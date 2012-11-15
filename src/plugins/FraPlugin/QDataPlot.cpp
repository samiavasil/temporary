#include "QDataPlot.h"
#include "ui_qdataplot.h"
#include<QBoxLayout>
#include<QToolBar>
#include<QMenuBar>
#include<qwt/qwt_plot_canvas.h>
#include<qwt/qwt_plot_grid.h>
#include<qwt/qwt_plot_zoomer.h>
#include <qwt/qwt_painter.h>
#include <qwt/qwt_plot_layout.h>
#include <qwt/qwt_legend.h>
#include <qwt/qwt_legend_item.h>
#include<QMenu>
#include<QAction>
#include <QMouseEvent>

#define FIRST_LINE_COLOR 255,0,125

bool QDataPlot::MouseEvEater::eventFilter(QObject *obj, QEvent *event)
{
    static int i;

    qDebug("Ate key press %d",i);
    // return QObject::eventFilter(obj, event);

    if ( event->type() == QEvent::MouseButtonRelease ) {
        QMenu menu;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QwtPlotCurve* curCurve = m_Plot->m_Curves.value(m_Plot->m_CurCurve,NULL);

        QAction* sep = new QAction("Plot Lines",&menu);
        QFont font  = sep->font();
        font.setBold(true);
        font.setStyle(QFont::StyleItalic);
        sep->setFont(font);
        //sep->setSeparator(true);
        sep->setEnabled(false);
        menu.addAction(sep);
      //  menu.setTitle("Plot Lines");
      //  menu.show
        menu.addAction(new QAction(QString("cutAct %1 %2").
                                   arg(curCurve->plot()->canvasMap( curCurve->xAxis()).invTransform(mouseEvent->x())).
                                   arg(curCurve->plot()->canvasMap( curCurve->yAxis()).invTransform(mouseEvent->y()))
                                   ,&menu));

        menu.addAction(new QAction("copyAct",&menu));
        menu.addAction(new QAction("pasteAct",&menu));
        menu.exec(mouseEvent->globalPos());
    }
    if ( event->type() == QEvent::MouseMove ) {
        i++;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        qDebug("Ate key press %d", mouseEvent->y());

        if( m_Plot ){
            if( ( 0 <= m_Plot->m_CurCurve )&&( m_Plot->m_CurCurve < m_Plot->m_Curves.count() ) ){
                QwtPlotCurve* curCurve = m_Plot->m_Curves.value(m_Plot->m_CurCurve,NULL);
                if( curCurve ){
                    //int idx = curCurve->closestPoint( mouseEvent->pos() );
                    int size = curCurve->dataSize();
                    QPointF data,data1;// = curCurve->sample(idx);
                    const QwtScaleMap yMap = curCurve->plot()->canvasMap( curCurve->yAxis() );
                    const QwtScaleMap xMap = curCurve->plot()->canvasMap( curCurve->xAxis() );
                    QPointF point =  mouseEvent->pos();//m_Plot->m_picker->trackerPosition();
                    qDebug("Tracker postion %f %f ", point.x(), point.y());
                    double x = xMap.invTransform( point.x() );
                    double y = yMap.invTransform( point.y() );
                    QwtInterval interval = curCurve->plot()->axisInterval(QwtPlot::xBottom);
                    double xx = interval.minValue();
                    double ww = xx + interval.width();
                    qDebug("Coordinate X = %f Y = %f ", x , y);
                    qDebug("Coordinate XX = %f WW = %f ", xx , ww);
                    y = yMap.transform( curCurve->sample(size-1).y() );
                    for( int i=0; i < size; i++ ){
                        data = curCurve->sample(i);
                        //  qDebug("Data X = %f Y = %f ", data.x() , data.y());
                        if( ( xx <= data.x() )&&( ww >= data.x() ) ){
                            if( data.x() >= x ){
                                if( i > 0 ){
                                    data  = curCurve->sample(i-1);
                                    data1 = curCurve->sample(i);
                                    double dY = data1.y() - data.y();
                                    double dX = (  x - data.x()  )/(data1.x()-data.x());
                                    qDebug("dX = %f dY = %f ", dX, dY);

                                    y = yMap.transform( data.y()+(dY*dX) );
                                }
                                else{
                                    data = curCurve->sample(i);
                                    y = yMap.transform( data.y() );
                                }
                                break;
                            }
                        }
                    }
                    ((QPoint*)(&(mouseEvent->pos())))->setY(y);
                    if( x < curCurve->sample( 0 ).x() ){
                        x = xMap.transform( curCurve->sample( 0 ).x() );
                    }
                    else  if(  x > curCurve->sample(size-1).x() ){
                        x = xMap.transform( curCurve->sample(size-1).x() );
                    }
                    else{
                        x = xMap.transform( x );
                    }

                    ((QPoint*)(&(mouseEvent->pos())))->setX(x);



                }
            }
            //
        }
        // standard event processing
        return QObject::eventFilter(obj, mouseEvent);
    }
    else{
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

QColor QDataPlot::m_NextColor;

QDataPlot::QDataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataPlot)
{
    m_CurCurve = -1;
    m_NextId   =  0;

    //m_NextColor.setRgb( FIRST_LINE_COLOR );
    updateNextColor();
    //curve2->setStyle( QwtPlotCurve::NoCurve );


    double x[100],y[100],z[100];

    ui->setupUi(this);

    // ui->PlotQwt->setAxisScale( );

    //ui->PlotQwt->setAxisAutoScale(QwtPlot::yLeft);
    //ui->PlotQwt->setAxisAutoScale(QwtPlot::yRight);
    //ui->PlotQwt->setAxisAutoScale(QwtPlot::xBottom);


    ui->PlotQwt->canvas()->setPaintAttribute( QwtPlotCanvas::BackingStore, false );
    ui->PlotQwt->canvas()->setFrameStyle ( QFrame::Box | QFrame::Plain );
    ui->PlotQwt->canvas()->setLineWidth ( 1 );
    ui->PlotQwt->setAutoReplot ( false );

    ui->PlotQwt->enableAxis ( QwtPlot::yRight, true );

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

    //ui->PlotQwt->setAxisAutoScale(QwtPlot::yRight);


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
    m_Grid->setYAxis(QwtPlot::yRight);

    m_Zoomer[0] = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yRight,ui->PlotQwt->canvas());
    m_Zoomer[0]->setTrackerMode(QwtPicker::AlwaysOff);
    m_Zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
    m_Zoomer[0]->setRubberBandPen(QColor ( Qt::green ) );
    m_Zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
    m_Zoomer[0]->setTrackerPen( QColor ( Qt::green ) );
    m_Zoomer[0]->setEnabled( false );

    m_Zoomer[0]->setMousePattern ( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    m_Zoomer[0]->setMousePattern ( QwtEventPattern::MouseSelect3, Qt::RightButton );

    //m_Zoomer[0]->setAxis();

    m_Zoomer[1] = new QwtPlotZoomer( QwtPlot::xTop, QwtPlot::yLeft, ui->PlotQwt->canvas() );
    m_Zoomer[1]->setEnabled( false );


    m_picker = new QwtPlotPicker ( QwtPlot::xBottom, QwtPlot::yLeft,
                                   QwtPlotPicker::CrossRubberBand,   QwtPicker::AlwaysOn,
                                   ui->PlotQwt->canvas() );
    m_picker->setMousePattern ( QwtEventPattern::MouseSelect1, Qt::LeftButton );
    m_picker->setRubberBand ( QwtPicker::CrossRubberBand );
    m_picker->setStateMachine(new QwtPickerTrackerMachine());
    m_picker->setRubberBandPen ( QColor ( Qt::green ) );
    m_picker->setTrackerPen ( QColor ( Qt::red ) );
    m_picker->setResizeMode(  QwtPicker::KeepSize );
    //m_picker->setEnabled(false);
    MouseEvEater* e = new MouseEvEater( this, m_picker  );

    QWidget *w = m_picker->parentWidget();
    if ( w )
    {
        w->installEventFilter( e );
    }
    //ui->PlotQwt->canvas()->installEventFilter(e);

    //m_picker->trackerWidget();


    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    QwtLegend *legend =  new QwtLegend();
    legend->setItemMode( QwtLegend::ClickableItem );
    ui->PlotQwt->insertLegend( legend );
    connect( ui->PlotQwt, SIGNAL(legendClicked(QwtPlotItem*)),this, SLOT(legendClicked(QwtPlotItem*)) );
    connect(ui->PlotQwt, SIGNAL(showContextMenuEvent(QContextMenuEvent *event)),this, SLOT(showPlotContextMenuEvent(QContextMenuEvent *event)));

    /*     addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
*/
    /*
    //DELL ME
    // copy the data into the curves
    // add curves
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    QwtPlotCurve *curve2 = new QwtPlotCurve("Curve 2");

    m_Curves.append(curve1);
    m_Curves.append(curve2);
    for( int i=0; i<100; i++){
        x[i] = i;
        z[i] = -50+i;
        y[i] = 400*sin((6.28*i)/100);
        qDebug("sin(%d)=%f",i,z[i]);
    }
    curve1->setYAxis( QwtPlot::yLeft );
    curve2->setYAxis( QwtPlot::yRight );
    curve1->attach(ui->PlotQwt);
    curve2->attach(ui->PlotQwt);

    curve1->setStyle( QwtPlotCurve::Sticks );

    curve1->setSamples( x,y,100 );
    curve2->setSamples( x,z,100);

    curve1->setPen(QPen(Qt::green));
    curve2->setPen(QPen(Qt::red));
    QwtSymbol* sym = new QwtSymbol(QwtSymbol::Rect,QBrush(Qt::blue),QPen( QBrush(Qt::blue),1 ),QSize(6,6) );
    curve2->setSymbol(sym);
*/

    m_CurCurve = 0;
    m_Zoomer[0]->setZoomBase( false );

    // m_Zoomer[1]->setZoomBase( true );
    // ui->PlotQwt->setAxisScale(QwtPlot::yLeft, 0, 100 );
    // ui->PlotQwt->setAxisScale(QwtPlot::yRight, -400, 400,1/4  );





    //  m_Zoomer[0]->initMousePattern(2);

    // m_Zoomer[0] = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::yRight,ui->PlotQwt->canvas());

    /* m_Zoomer[0]->setMousePattern ( QwtEventPattern::MouseSelect1,
                     Qt::LeftButton );

   m_Zoomer[0]->setMousePattern ( QwtEventPattern::MouseSelect4,
                     Qt::NoButton );
   m_Zoomer[0]->setMousePattern ( QwtEventPattern::MouseSelect6,
                     Qt::NoButton );  */

}

QDataPlot::~QDataPlot()
{
    delete ui;
    if( m_Grid ){
        delete m_Grid;
    }
}




QDataPlot::lineId_t QDataPlot::addLine( QDataPlot::Axes axes,
                                        const QString& name,
                                        QwtPlotCurve::CurveStyle curveStyle,
                                        Qt::PenStyle pen_style,
                                        QColor pen_color,
                                        QwtSymbol::Style symbol
                                        )
{
    QDataPlot::lineId_t id = INVAL_LINE_ID;
    QwtPlotCurve *curve;

    if( name.isEmpty() ){
        curve = new QwtPlotCurve(QString("Curve 1").arg(m_NextId));
    }
    else{
        curve = new QwtPlotCurve( name );
    }
    if( curve ){

        switch( axes ){
        case BottomLeftAxes:{
            curve->setAxes( QwtPlot::xBottom, QwtPlot::yLeft );
            break;
        }
        case TopRightAxes:{
            curve->setAxes( QwtPlot::xTop, QwtPlot::yRight );
            break;
        }
        default:
            break;
        }
        QPen c_pen( pen_style );

        c_pen.setColor( pen_color );
        curve->setPen( c_pen );
        curve->setStyle( curveStyle );
        if( QwtSymbol::NoSymbol != symbol ){
            QwtSymbol* c_symbol = new QwtSymbol(symbol);
            curve->setSymbol( c_symbol );
        }
        curve->attach(ui->PlotQwt);

        ////////////DELL ME
        double x[100],y[100];
        double phase = ((double)qrand());
        for( int i=0; i < 100; i++ ){
            x[i] = i;
            y[i] = 400*sin(((6.28*i)/100) + phase );
            //qDebug("sin(%d)=%f",i,z[i]);
        }
        curve->setSamples( x,y,100 );
        ////////////DELL ME

        m_Curves.append(curve);
        id = m_NextId;
        m_NextId++;

        updateNextColor();
    }
    return id;
}

/*TODO - generate next line color */
void QDataPlot::updateNextColor(){
    static int i;
    int r,g,b,a;
    m_NextColor.getRgb(&r,&g,&b,&a);
    // r = ( (((i/4)+1)*256)-1 )%256;
    // g = (  i*(r/63)*63   )%256;
    // b = (  i*126   )%256;

    r = ( ( (((i/4)+1)*244 )) )%256;
    g = ( ((i/3)*110) )%256;
    b = ( (i*110))%256;

    m_NextColor.setRgb(r,g,b,a);
    i++;
}

int QDataPlot::setLineData  ( lineId_t id, const QVector<QPointF> &  ){

}

QVector<QPointF>* QDataPlot::getLineData( lineId_t id ){

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

void QDataPlot::on_actionMouseTrack_toggled(bool arg1)
{

    if( arg1  ){
        m_Zoomer[0]->setTrackerMode(QwtPicker::AlwaysOn);
    }
    else{
        m_Zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly );
    }
}

void QDataPlot::on_actionRectangle_Zoom_toggled(bool arg1)
{
    if( arg1  ){
        //m_Zoomer[0]->setEnabled( true );
        ui->PlotQwt->setEnabled ( arg1 );
        m_Zoomer[0]->setZoomBase();
        m_Zoomer[1]->setZoomBase();
        m_Zoomer[0]->setEnabled ( arg1 );
        m_Zoomer[0]->zoom ( 0 );
        m_Zoomer[1]->setEnabled ( arg1 );
        m_Zoomer[1]->zoom ( 0 );
    }
    else{
        m_Zoomer[0]->setEnabled( false );
    }


}
#include<QDebug>
void QDataPlot::legendClicked( QwtPlotItem* item ){
    QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(item);
    if( curve ){
        curve->setVisible(!curve->isVisible());
    }
    item->plot()->replot();
}

QwtPlotCurve* QDataPlot::findPlotcurve(  ){

}

void QDataPlot::showPlotContextMenuEvent(QContextMenuEvent *event){

    QMenu menu(this);
    menu.addAction(new QAction("cutAct",&menu));
    menu.addAction(new QAction("copyAct",&menu));
    menu.addAction(new QAction("pasteAct",&menu));
    menu.exec(event->globalPos());
}





