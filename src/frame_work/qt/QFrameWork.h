#ifndef _QFRAMEWORK_H
#define _QFRAMEWORK_H


#include "base/CFrameWork.h"
#include <QWidget>
#include <QMainWindow>

class QFrameWorkElementsFactory;

class QFrameWork : public CFrameWork, public QWidget {
  public:
    QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent = 0);

};
#endif
