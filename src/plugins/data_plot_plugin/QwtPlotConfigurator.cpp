#include "QwtPlotConfigurator.h"
#include "ui_QwtPlotConfigurator.h"

#include"qt/debug.h"


QwtPlotConfigurator::QwtPlotConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QwtPlotConfigurator)
{
    ui->setupUi(this);
    DEB1("QwtPlotConfigurator TEST2");
}

QwtPlotConfigurator::~QwtPlotConfigurator()
{
    delete ui;
}
