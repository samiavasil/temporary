#ifndef QDATAPLOT_H
#define QDATAPLOT_H

#include <QWidget>
#include <QMap>
#include<ui_qdataplot.h>
#include<qwt/qwt_plot_curve.h>
#include <qwt/qwt_picker_machine.h>
#include <qwt/qwt_plot_picker.h>
#include <qwt/qwt_symbol.h>

class QwtPlotGrid;
class QwtPlotZoomer;

#define INVAL_LINE_ID ( (QDataPlot::lineId_t)(-1) )

class QDataPlot : public QWidget
{
    Q_OBJECT
    
public:
    enum Axes
    {
        BottomLeftAxes,
        TopRightAxes
    };
    typedef int lineId_t;

public:
    explicit QDataPlot(QWidget *parent = 0);
    ~QDataPlot();

    QDataPlot::lineId_t addLine( QDataPlot::Axes axes = QDataPlot::BottomLeftAxes,
                                 const QString& name =  QString(),
                                 QwtPlotCurve::CurveStyle curveStyle = QwtPlotCurve::Lines,
                                 Qt::PenStyle pen_style     = Qt::SolidLine,
                                 QColor pen_color = QColor(m_NextColor),
                                 QwtSymbol::Style symbol = QwtSymbol::NoSymbol
                                );
    int removeLine( QDataPlot::lineId_t id );
    int setLineData  ( lineId_t id, const QVector<QPointF> &  );
    QVector<QPointF>* getLineData( lineId_t id );
protected:
    void updateNextColor();

public slots:

private slots:

    void on_actionGrid_X_on_triggered(bool checked);

    void on_actionGrid_Y_on_triggered(bool checked);

    void on_actionShowTable_triggered(bool checked);

    void on_actionAutoscale_triggered();

    void on_actionMouseTrack_toggled(bool arg1);

    void on_actionRectangle_Zoom_toggled(bool arg1);
    void on_actionActionEnablePicker_triggered(bool checked);

    void on_actionShowLegend_toggled(bool arg1);

protected:
    class CanvasEventFilter : public QObject
    {
    public:
        CanvasEventFilter(  QDataPlot* parent ):QObject(parent){
            m_Plot = parent;
        }
        ~CanvasEventFilter(){

        }
    protected:
        bool eventFilter(QObject *obj, QEvent *event);
    protected:
        QDataPlot* m_Plot;

    };

    QwtPlotCurve* currentCurve();
    void enableSnapPickerToCurve( bool enble );
    bool isEnabledSnapPickerToCurve( );
    QwtPlotCurve* showPopupMenu(const QPoint &pos );
    QwtPlotCurve* findFirstVisibleCurve(  );
    int setCurrentCurve( QwtPlotCurve *curve );
protected slots:
    void selectCurveActionSlot(  bool sel );
    void showLinesConfigurationDialog( );
protected:
    QwtPlotGrid*          m_Grid;
    QwtPlotZoomer*        m_Zoomer[2];
    QMap<QwtPlot::Axis,   QwtPlotZoomer*> m_ZoomerMap;

    QwtPlotPicker*        m_picker;
    bool                  m_EnblPickerSnap;
    CanvasEventFilter*    m_CanvasEventFilter;

    QMap< QDataPlot::lineId_t, QwtPlotCurve*> m_CurveMap;
    QwtPlotCurve*         m_CurCurve;

    QDataPlot::lineId_t   m_NextId;
    static QColor         m_NextColor;
protected slots:
    void legendClicked(QwtPlotItem* item);
private:
    Ui::QDataPlot *ui;
};

#endif // QDATAPLOT_H
