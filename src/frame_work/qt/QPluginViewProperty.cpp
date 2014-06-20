#include "QPluginViewProperty.h"
#include "ui_QPluginViewProperty.h"

QPluginViewProperty::QPluginViewProperty( const cfgViewTypeT &type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPluginViewProperty)
{
    ui->setupUi(this);
    ui->checkCategory->setChecked( type.category() );
    ui->checkDescription->setChecked( type.description() );
    ui->checkEnabled->setChecked( type.enable() );
    ui->checkIcon->setChecked( type.icon() );
    ui->checkLocation->setChecked( type.location() );
    ui->checkName->setChecked( type.name() );
    ui->checkType->setChecked( type.type() );
    ui->checkVersion->setChecked( type.version() );
}

QPluginViewProperty::~QPluginViewProperty()
{
    delete ui;
}

cfgViewTypeT QPluginViewProperty::getProperties()
{
     cfgViewTypeT type;
     type.category(ui->checkCategory->isChecked()).description(ui->checkDescription->isChecked());
     type.enable(ui->checkEnabled->isChecked()).icon(ui->checkIcon->isChecked());
     type.location(ui->checkLocation->isChecked()).name(ui->checkName->isChecked());
     type.type(ui->checkType->isChecked()).version(ui->checkVersion->isChecked());
     return type;
}
