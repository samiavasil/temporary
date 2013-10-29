#include "qportiosimulatorui.h"
#include "ui_qportiosimulatorui.h"

QportIoSimulatorUI::QportIoSimulatorUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QportIoSimulatorUI)
{
    ui->setupUi(this);
}

QportIoSimulatorUI::~QportIoSimulatorUI()
{
    delete ui;
}
