#include "QwtPlotConfigurator.h"
#include "ui_QwtPlotConfigurator.h"

QwtPlotConfigurator::QwtPlotConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QwtPlotConfigurator)
{
    ui->setupUi(this);
}

QwtPlotConfigurator::~QwtPlotConfigurator()
{
    delete ui;
}
