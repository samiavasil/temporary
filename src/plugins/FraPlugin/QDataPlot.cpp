#include<QDebug>
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
#include <QPainter>
#include<QPointF>
#define FIRST_LINE_COLOR 255,0,125

class MenuLines:public QMenu{
public:
    explicit MenuLines(QWidget *parent = 0):QMenu(parent){

    }
protected:
    virtual void paintEvent ( QPaintEvent * event ){
        QMenu::paintEvent( event );
        QPainter painter(this);
        QList<QAction *> act = actions();
        QRect rect;
        for (int i = 0; i < act.size(); ++i) {
            QwtPlotCurve* curve =  (QwtPlotCurve*)( act.at(i)->data().toULongLong() );
            if( curve ){
               rect = actionGeometry( act.at(i) );
               curve->drawLegendIdentifier(&painter,QRectF(rect.width()/2,rect.y()+(rect.height()/4),rect.width()/8,rect.height()/2) );
               qDebug() <<  curve->title().text();
            }
        }
    }
};

bool QDataPlot::CanvasEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    static int i;
    QwtPlotCurve* curve = m_Plot->m_CurCurve;
    QwtPlot* plotQwt    = m_Plot->ui->PlotQwt;

    if ( event->type() == QEvent::MouseButtonRelease ) {
        if(  !m_Plot->m_Zoomer[0]->isEnabled() ){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if( Qt::RightButton == mouseEvent->button() ){
                m_Plot->selectCurrentCurveMenu(mouseEvent->globalPos());
            }
        }
    }

    if( m_Plot->m_picker && m_Plot->m_picker->isEnabled() ){
        if ( event->type() == QEvent::MouseMove ) {

            i++;
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if( curve  && m_Plot->isEnabledSnapPickerToCurve() ){

                int size = curve->dataSize();
                QPointF data,data1;// = curve->sample(idx);
                const QwtScaleMap yMap = plotQwt->canvasMap( curve->yAxis() );
                const QwtScaleMap xMap = plotQwt->canvasMap( curve->xAxis() );
                QPointF point =  mouseEvent->pos();//plotQwt->m_picker->trackerPosition();
                qDebug("Tracker postion %f %f ", point.x(), point.y());
                double x = xMap.invTransform( point.x() );
                double y = yMap.invTransform( point.y() );
                QwtInterval interval = plotQwt->axisInterval( curve->xAxis() );
                double xx = interval.minValue();
                double ww = xx + interval.width();
                qDebug()<<"("<<point.x()<<","<<point.y()<<") " << "X="<<x<<" Y="<<y;
                y = yMap.transform( curve->sample(size-1).y() );
                for( int i=0; i < size; i++ ){
                    data = curve->sample(i);
                    if( ( xx <= data.x() )&&( ww >= data.x() ) ){
                        if( data.x() >= x ){
                            if( i > 0 ){
                                data  = curve->sample(i-1);
                                data1 = curve->sample(i);
                                double dY = data1.y() - data.y();
                                double dX = (  x - data.x()  )/(data1.x()-data.x());
                                qDebug("dX = %f dY = %f Y=%f", dX, dY,data.y()+(dY*dX));
                                y = yMap.transform( data.y()+(dY*dX) );
                            }
                            else{
                                data = curve->sample(i);
                                y = yMap.transform( data.y() );
                            }
                            break;
                        }
                    }
                }
                qDebug()<<curve->title().text() << "pointY="<<point.y()<<"  Y="<<y;
                ((QPoint*)(&(mouseEvent->pos())))->setY(y);
                qDebug()<<curve->title().text() << "mapedY="<<mouseEvent->pos().y();
                if( x < curve->sample( 0 ).x() ){
                    x = xMap.transform( curve->sample( 0 ).x() );
                }
                else  if(  x > curve->sample(size-1).x() ){
                    x = xMap.transform( curve->sample(size-1).x() );
                }
                else{
                    x = xMap.transform( x );
                }

                ((QPoint*)(&(mouseEvent->pos())))->setX(x);
            }
            // standard event processing
            return QObject::eventFilter(obj, mouseEvent);
        }

    }
    return QObject::eventFilter(obj, event);

}

QColor QDataPlot::m_NextColor;
#include <QGraphicsOpacityEffect>
QDataPlot::QDataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataPlot)
{
    m_CurCurve    =  0;
    m_NextId      =  0;
    m_CanvasEventFilter = NULL;

    //m_NextColor.setRgb( FIRST_LINE_COLOR );
    updateNextColor();
    //curve2->setStyle( QwtPlotCurve::NoCurve );

    ui->setupUi(this);
ui->PlotQwt->legend();

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
    ptr->addAction(ui->actionActionEnablePicker);
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
    m_CanvasEventFilter  = new CanvasEventFilter( this  );

    on_actionActionEnablePicker_triggered( false );
    enableSnapPickerToCurve( true );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );

    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    /*
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
   */

    addLine( QDataPlot::TopRightAxes   );
    addLine( QDataPlot::BottomLeftAxes );
    addLine( QDataPlot::TopRightAxes   );
    QwtLegend *legend =  new QwtLegend();
    legend->setItemMode( QwtLegend::ClickableItem );
    ui->PlotQwt->insertLegend( legend );
    connect( ui->PlotQwt, SIGNAL(legendClicked(QwtPlotItem*)),this, SLOT(legendClicked(QwtPlotItem*)) );
    connect(ui->PlotQwt, SIGNAL(showContextMenuEvent(QContextMenuEvent *event)),this, SLOT(showPlotContextMenuEvent(QContextMenuEvent *event)));
    m_Zoomer[0]->setZoomBase( false );
}

QDataPlot::~QDataPlot()
{
    if( m_CanvasEventFilter ){
        ui->PlotQwt->canvas()->installEventFilter( NULL );
        delete m_CanvasEventFilter;
        m_CanvasEventFilter = NULL;
    }
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
        curve = new QwtPlotCurve(QString("Curve %1").arg(m_NextId));
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

        curve->setStyle( QwtPlotCurve::Steps );
        curve->setLegendAttribute( QwtPlotCurve::LegendShowLine );
        curve->setLegendAttribute( QwtPlotCurve::LegendShowSymbol);
        curve->setLegendAttribute( QwtPlotCurve::LegendShowBrush );
        curve->setSymbol(new QwtSymbol( QwtSymbol::Diamond,curve->brush(),curve->pen(),QSize(5,5)));
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

        m_CurveMap.insert( m_NextId, curve );
        id = m_NextId;
        m_NextId++;
        updateNextColor();
    }
    if( 0 == m_CurCurve ){
        setCurrentCurve( curve );
    }
    return id;
}

int QDataPlot::removeLine( QDataPlot::lineId_t id )
{
    QwtPlotCurve* curve = m_CurveMap.value( id, NULL );
    if( curve ){
        curve->detach();
        m_CurveMap.remove(id);
        if( curve == m_CurCurve ){
            setCurrentCurve(findFirstVisibleCurve());
        }
        delete curve;
    }
    return 0;
}

int QDataPlot::setLineData  ( lineId_t id, const QVector<QPointF> &  ){
    return 0;
}

QVector<QPointF>* QDataPlot::getLineData( lineId_t id ){

}

/*TODO - generate next line color */
void QDataPlot::updateNextColor(){
    static int i;
    int r,g,b,a;

    m_NextColor.getRgb(&r,&g,&b,&a);
    r = ( ( (((i/4)+1)*244 )) )%256;
    g = ( ((i/3)*110) )%256;
    b = ( (i*110))%256;

    m_NextColor.setRgb(r,g,b,a);
    i++;
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
    ui->PlotQwt->setAxisAutoScale(QwtPlot::xTop);
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

void QDataPlot::legendClicked( QwtPlotItem* item ){
    QwtPlotCurve* curve = dynamic_cast<QwtPlotCurve*>(item);
    if( curve ){
        curve->setVisible(!curve->isVisible());
        if( curve == m_CurCurve ){
            setCurrentCurve(findFirstVisibleCurve());
        }
    }
    item->plot()->replot();
}

void QDataPlot::on_actionActionEnablePicker_triggered( bool checked )
{
    if( m_picker ){
        m_picker->setEnabled(checked);
    }
    ui->PlotQwt->canvas()->installEventFilter( m_CanvasEventFilter );
}

void QDataPlot::enableSnapPickerToCurve( bool enble ){
    m_EnblPickerSnap = enble;
}

bool QDataPlot::isEnabledSnapPickerToCurve( ){
    return m_EnblPickerSnap;
}

int QDataPlot::setCurrentCurve( QwtPlotCurve *curve ){
    int ret = 1;
    const QwtPlotItemList &list = ui->PlotQwt->itemList();
    m_CurCurve = NULL;/* If curve not founded current curve set to NULL (not selected current curve)*/
    for (QwtPlotItemIterator it = list.begin();it!=list.end();++it)
    {
        if ( ( *it == curve ) && ( (*it)->rtti() == QwtPlotItem::Rtti_PlotCurve ) ){
            m_CurCurve = curve;
            m_picker->setRubberBandPen ( curve->pen().color() );
            m_picker->setTrackerPen ( curve->pen().color() );
            ret = 0;
        }
    }
    return ret;
}

QwtPlotCurve* QDataPlot::currentCurve( ){
    return m_CurCurve;
}
#include<QWidgetAction>
QwtPlotCurve* QDataPlot::selectCurrentCurveMenu( const QPoint &pos ){
    MenuLines menu;
    QAction* action = new QAction("Select current line",&menu);
    QFont font  = action->font();
    font.setBold(true);
    font.setStyle(QFont::StyleItalic);
    action->setFont(font);
    action->setEnabled(false);
    menu.addAction(action);
    action = new QAction("No current line selection",&menu);
    action->setData((qlonglong)NULL);
    connect( action, SIGNAL(triggered(bool)), this, SLOT(selectCurveActionSlot(bool)),Qt::DirectConnection );
    if( NULL == m_CurCurve ){
        action->setCheckable(true);
        action->setChecked(true);
    }
    menu.addAction( action  );
    QwtPlotCurve* curve;
    QMapIterator<QDataPlot::lineId_t, QwtPlotCurve*> it( m_CurveMap );
    while( it.hasNext() )
    {
        it.next();
        curve = it.value();
        if( curve&&curve->isVisible() ){
            action = new QAction( curve->title().text(), &menu );
            if( curve == m_CurCurve ){
                action->setCheckable(true);
                action->setChecked(true);
            }
            action->setData((qlonglong)curve);
            connect( action, SIGNAL(triggered(bool)), this, SLOT(selectCurveActionSlot(bool)),Qt::DirectConnection );
            menu.addAction( action  );
        }
        else{
            qDebug("Misterious NULL Pointer");
        }
    }
    menu.exec(pos);
}

void QDataPlot::selectCurveActionSlot( bool sel ){
    QAction* action = dynamic_cast<QAction*>(sender());
    if( action ){
        QwtPlotCurve* curve =  (QwtPlotCurve*)( action->data().toULongLong() );
        setCurrentCurve( curve );
    }
}

QwtPlotCurve* QDataPlot::findFirstVisibleCurve(){
    QwtPlotCurve* curve;
    QMapIterator<QDataPlot::lineId_t, QwtPlotCurve*> it( m_CurveMap );
    while( it.hasNext() )
    {
        it.next();
        curve = it.value();
        if( curve ){
            if( curve->isVisible() ){
                return curve;
            }
        }
        else{
            qDebug("Misterious NULL Pointer");
        }
    }
    return NULL;
}
