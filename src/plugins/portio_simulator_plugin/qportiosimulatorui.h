#ifndef QPORTIOSIMULATORUI_H
#define QPORTIOSIMULATORUI_H

#include <QWidget>

namespace Ui {
class QportIoSimulatorUI;
}

class QportIoSimulatorUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit QportIoSimulatorUI(QWidget *parent = 0);
    ~QportIoSimulatorUI();
    
private:
    Ui::QportIoSimulatorUI *ui;
};

#endif // QPORTIOSIMULATORUI_H
