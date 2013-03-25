#ifndef QFRAFRAMEWORK_H
#define QFRAFRAMEWORK_H
#include "qt/QFrameWork.h"

#include <ui_qfra_frame_work_view.h>
#include "plugin_global.h"
class QWidget;

class PLUGIN_EXPORT QFraFrameWork:public QFrameWork
{
Q_OBJECT
public:
   QFraFrameWork(QFrameWorkElementsFactory * factory,QWidget * parent = 0 );
   QFraFrameWork( QCreator* creator = NULL , QWidget * parent = 0 );
   virtual ~QFraFrameWork();

protected:
   Ui::QFraFrameWorkView * ui;
};

#endif // QFRAFRAMEWORK_H
