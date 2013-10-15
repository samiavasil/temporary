#ifndef DESIGNERTAMPLATE_H
#define DESIGNERTAMPLATE_H

#include<QWidget>
#include <QtDesigner/QDesignerExportWidget>
 #include <QBrush>
class QTimer;
class QListWidget;
class QDESIGNER_WIDGET_EXPORT DesignerTamplate:public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Color color READ color WRITE setColor NOTIFY colorChanged)
    Q_ENUMS(Color)
public:
    DesignerTamplate(QWidget* parent=NULL);
    ~DesignerTamplate();
    enum Color { R, G, B };
    void setColor(Color color);
    Color color() const;
public slots:
    void update();
    void start_stop();
signals:
    void colorChanged(Color);
protected:
    Color m_color;
    QTimer* m_timer;
    QListWidget* list;
};


#endif // DESIGNERTAMPLATE_H
