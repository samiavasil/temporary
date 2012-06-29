#ifndef QFRAFRAMEWORK_H
#define QFRAFRAMEWORK_H
#include "QFrameWork.h"

#include <ui_qframeworkview.h>
#include "fra_plugin_global.h"
class QWidget;

class FRA_PLUGIN_EXPORT QFraFrameWork:public QFrameWork
{
public:
   QFraFrameWork(QWidget * parent = 0 );
   ~QFraFrameWork();

protected:
   Ui::QFrameWorkView * ui;
};

#endif // QFRAFRAMEWORK_H
