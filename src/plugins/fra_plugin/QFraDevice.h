#ifndef QFRADEVICE_H
#define QFRADEVICE_H

#include <QWidget>

namespace Ui {
class QFraDevice;
}
class QPortsIoView;
class QFraDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit QFraDevice(QWidget *parent = 0);
    ~QFraDevice();

private slots:
    void on_StartButton_clicked(bool clicked);
protected:
    QPortsIoView* m_PIOList;
private:
    Ui::QFraDevice *ui;
};

#endif // QFRADEVICE_H
