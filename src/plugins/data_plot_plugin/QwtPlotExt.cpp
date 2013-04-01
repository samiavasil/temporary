#include "QwtPlotExt.h"
#include<QMessageBox>


QwtPlotExt::QwtPlotExt( QWidget * parent ):QwtPlot( parent ){

}

QwtPlotExt::QwtPlotExt( const QwtText &title, QWidget *parent ):QwtPlot(title,parent){

}

QwtPlotExt::~QwtPlotExt(){

}


void QwtPlotExt::contextMenuEvent(QContextMenuEvent *event){
    emit showContextMenuEvent( event );
}


