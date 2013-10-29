#ifndef QFRAFRAMEWORK_H
#define QFRAFRAMEWORK_H
#include"qt/QFrameWork.h"


namespace Ui {
class QFraFrameWorkView;
}

class QFraFrameWork:public QFrameWork
{
    Q_OBJECT
public:
    explicit QFraFrameWork(QCreator * creator = 0, QWidget * parent = 0);
    virtual ~QFraFrameWork();
    virtual void AddWidgetToDataViewArrea( QWidget* widget );
    void AddWidgetToControlArrea ( QWidget* widget );
private slots:
    void on_StartButton_clicked();
    void on_mdi_change_view_mode(int);
private:
    Ui::QFraFrameWorkView* ui;
    QList<QObject*> list;
};

#endif // QFRAFRAMEWORK_H
