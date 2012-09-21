#include "QDataPlot.h"
#include "ui_qdataplot.h"

QDataPlot::QDataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataPlot)
{
    ui->setupUi(this);
}

QDataPlot::~QDataPlot()
{
    delete ui;
}
