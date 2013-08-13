#ifndef DESIGNERTAMPLATE_H
#define DESIGNERTAMPLATE_H

#include<QListWidget>
#include <QtDesigner/QDesignerExportWidget>
 #include <QBrush>
class QDESIGNER_WIDGET_EXPORT DesignerTamplate:public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(Color color READ color WRITE setColor NOTIFY colorChanged)
    Q_ENUMS(Color)
public:
    DesignerTamplate(QWidget* parent=NULL);
    enum Color { R, G, B };
    void setColor(Color color)
    {
        m_color = color;
        insertItem(0,new QListWidgetItem());
        switch(m_color)
        {
        case R:
        {
            item(0)->setBackground(QBrush(Qt::red));
            break;
        }
        case G:
        {
            item(0)->setBackground(QBrush(Qt::green));
            break;
        }
        case B:
        {
            item(0)->setBackground(QBrush(Qt::blue));
            break;
        }

        }
        emit colorChanged(color);
    }
    Color color() const
    {
        return m_color;
    }
public slots:
    void Dgd();
signals:
    void colorChanged(Color);
protected:
    Color m_color;
};


#endif // DESIGNERTAMPLATE_H
