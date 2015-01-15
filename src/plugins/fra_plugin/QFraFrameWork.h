#ifndef QFRAFRAMEWORK_H
#define QFRAFRAMEWORK_H
#include"qt/QFrameWork.h"
#include<QWidget>



namespace Ui {
class QFraFrameWorkView;
}



class QFraFrameWork:public QFrameWork
{
    Q_OBJECT
public:
    explicit QFraFrameWork(QCreator * creator = 0, QObject * parent = 0);
    virtual ~QFraFrameWork();
    virtual void AddWidgetToDataViewArrea( QWidget* widget );
    void AddWidgetToControlArrea ( QWidget* widget );

private slots:
    void on_mdi_change_view_mode(int);
    void on_detach_MDI_window(bool togg);
    void newView();
    void dbg(QObject* obj);
private:
    Ui::QFraFrameWorkView* ui;
    QList<QObject*> nonAutoCleanList;

};
#endif // QFRAFRAMEWORK_H
