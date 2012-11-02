#ifndef QDATAPLOT_H
#define QDATAPLOT_H

#include <QWidget>
#include<ui_qdataplot.h>


class QwtPlotGrid;
class QwtPlotZoomer;
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

    void on_actionAutoscale_triggered();

protected:
    QwtPlotGrid*   m_Grid;
    QwtPlotZoomer* m_Zoomer;
private:
    Ui::QDataPlot *ui;
};

#endif // QDATAPLOT_H
