#ifndef QFRAFRAMEWORK_H
#define QFRAFRAMEWORK_H
#include"qt/QFrameWork.h"
#include<QWidget>


namespace Ui {
class QFraFrameWorkView;
}

class QFwWidget: public QWidget{
    Q_OBJECT
public:
    explicit QFwWidget( QWidget *parent = 0, Qt::WindowFlags f = 0 );
    virtual ~QFwWidget();
    void     closeEvent(QCloseEvent *event);

signals:
    void destroyFW();
};

class QFraFrameWork:public QFrameWork
{
    Q_OBJECT
public:
    explicit QFraFrameWork(QCreator * creator = 0, QObject * parent = 0);
    virtual ~QFraFrameWork();
    virtual void AddWidgetToDataViewArrea( QWidget* widget );
    void AddWidgetToControlArrea ( QWidget* widget );
    virtual QWidget* getFrameWorkWindow();
private slots:
    void on_StartButton_clicked();
    void on_mdi_change_view_mode(int);
    void on_detach_MDI_window(bool togg);
private:
    Ui::QFraFrameWorkView* ui;
    QList<QObject*> listWin;
protected:
     QWidget* m_FwWin;
};
#endif // QFRAFRAMEWORK_H
