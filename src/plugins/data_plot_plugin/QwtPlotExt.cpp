#include "QwtPlotExt.h"
#include<QMessageBox>
#include"qt/debug.h"


QwtPlotExt::QwtPlotExt( QWidget * parent ):QwtPlot( parent ){
    DEB1("QwtPlotExt TEST1");
}

QwtPlotExt::QwtPlotExt( const QwtText &title, QWidget *parent ):QwtPlot(title,parent){

}

QwtPlotExt::~QwtPlotExt(){

}


void QwtPlotExt::contextMenuEvent(QContextMenuEvent *event){
    emit showContextMenuEvent( event );
}


