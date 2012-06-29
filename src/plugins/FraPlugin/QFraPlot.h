#ifndef _QFRAPLOT_H
#define _QFRAPLOT_H
#include "global.h"

#include "basic/QDataPlot.h"
#include <ui_fra_plotform.h>


/**
 *  \brief 
 * 
 */
class MYSHAREDLIB_EXPORT QFraPlot : public QDataPlot {
  public:
QFraPlot(QWidget * parent = 0);

~QFraPlot();


  private:
    Ui::QFraPlot * ui;


  public:
virtual void InitUI();

};
#endif
