#ifndef QDATAPLOT_H
#define QDATAPLOT_H

#include <QWidget>
#include<ui_qdataplot.h>

class QDataPlot : public QWidget
{
    Q_OBJECT
    
public:
    explicit QDataPlot(QWidget *parent = 0);
    ~QDataPlot();
    
private:
    Ui::QDataPlot *ui;
};

#endif // QDATAPLOT_H
