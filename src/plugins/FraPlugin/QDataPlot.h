#ifndef QDATAPLOT_H
#define QDATAPLOT_H

#include <QWidget>
#include <QMap>
#include<ui_qdataplot.h>
#include<qwt/qwt_plot_curve.h>
#include <qwt/qwt_picker_machine.h>
#include <qwt/qwt_plot_picker.h>
class QwtPlotGrid;
class QwtPlotZoomer;



class QDataPlot : public QWidget
{
    Q_OBJECT
    
public:
    explicit QDataPlot(QWidget *parent = 0);
    ~QDataPlot();
    
private slots:

    void on_actionGrid_X_on_triggered(bool checked);

    void on_actionGrid_Y_on_triggered(bool checked);

    void on_actionShowTable_triggered(bool checked);

    void on_actionAutoscale_triggered();

    void on_actionMouseTrack_toggled(bool arg1);

    void on_actionRectangle_Zoom_toggled(bool arg1);

protected:
    class MouseEvEater : public QObject
    {
    public:
        MouseEvEater( QDataPlot* plot , QObject* parent = NULL ):QObject(parent){
            m_Plot = plot;
        }

    protected:
        bool eventFilter(QObject *obj, QEvent *event);
    protected:
        QDataPlot* m_Plot;
    };

    QwtPlotGrid*         m_Grid;
    QwtPlotZoomer*       m_Zoomer[2];


    QMap<QwtPlot::Axis, QwtPlotZoomer*> m_ZoomerMap;
    QList<QwtPlotCurve*>  m_Curves;
    QwtPlotPicker*        m_picker;
    int m_CurCurve;
private:
    Ui::QDataPlot *ui;
};

#endif // QDATAPLOT_H
