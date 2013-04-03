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
private:
    Ui::QFraFrameWorkView* ui;
};

#endif // QFRAFRAMEWORK_H
