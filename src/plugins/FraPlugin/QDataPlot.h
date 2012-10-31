#ifndef QDATAPLOT_H
#define QDATAPLOT_H

#include <QWidget>
#include<ui_qdataplot.h>


class QwtPlotGrid;
class QDataPlot : public QWidget
{
    Q_OBJECT
    
public:
    explicit QDataPlot(QWidget *parent = 0);
    ~QDataPlot();
    
private slots:
    void on_actionMouseTrack_triggered();
    void on_actionGrid_X_on_triggered(bool checked);

    void on_actionGrid_Y_on_triggered(bool checked);

    void on_actionShowTable_triggered(bool checked);

protected:
    QwtPlotGrid* m_Grid;
private:
    Ui::QDataPlot *ui;
};

#endif // QDATAPLOT_H
