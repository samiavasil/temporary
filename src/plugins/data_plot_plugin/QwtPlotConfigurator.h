#ifndef QWTPLOTCONFIGURATOR_H
#define QWTPLOTCONFIGURATOR_H

#include <QWidget>

namespace Ui {
class QwtPlotConfigurator;
}

class QwtPlotConfigurator : public QWidget
{
    Q_OBJECT
    
public:
    explicit QwtPlotConfigurator(QWidget *parent = 0);
    ~QwtPlotConfigurator();
    
private:
    Ui::QwtPlotConfigurator *ui;
};

#endif // QWTPLOTCONFIGURATOR_H
