#ifndef QPLUGINVIEWPROPERTY_H
#define QPLUGINVIEWPROPERTY_H

#include <QDialog>
#include"qt/QPluginListWidget.h"

namespace Ui {
class QPluginViewProperty;
}

class QPluginViewProperty : public QDialog
{
    Q_OBJECT

public:
    explicit QPluginViewProperty( const cfgViewTypeT &type,  QWidget *parent = 0);
    ~QPluginViewProperty();
    cfgViewTypeT getProperties();
    
private:
    Ui::QPluginViewProperty *ui;
};

#endif // QPLUGINVIEWPROPERTY_H
