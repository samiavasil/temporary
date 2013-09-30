#include"DesignerTamplate.h"
#include<QTimer>
#include<QListWidget>
#include<QVBoxLayout>
DesignerTamplate::DesignerTamplate(QWidget* parent):QWidget(parent){
    this->setLayout(new QVBoxLayout(this));
    list = new QListWidget(this);
    this->layout()->addWidget(list);
    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this, SLOT(update()));
}
DesignerTamplate::~DesignerTamplate()
{
    qDebug("DESTROY DesignerTamplate\n");
    m_timer->stop();
    m_timer->deleteLater();
}
void DesignerTamplate::setColor(Color color)
{
    m_color = color;
    list->insertItem(0,new QListWidgetItem());
    switch(m_color)
    {
    case R:
    {
        list->item(0)->setBackground(QBrush(Qt::red));
        break;
    }
    case G:
    {
       list->item(0)->setBackground(QBrush(Qt::green));
        break;
    }
    case B:
    {
        list->item(0)->setBackground(QBrush(Qt::blue));
        break;
    }

    }
    emit colorChanged(color);
}
DesignerTamplate::Color DesignerTamplate::color() const
{
    return m_color;
}
void DesignerTamplate::update()
{
   static  Qt::GlobalColor col = Qt::color0;
    QListWidgetItem *item = new QListWidgetItem();
    QColor color( col );
    item->setBackgroundColor( color );
    col=(Qt::GlobalColor)((int)col + 1);
    if( col > Qt::transparent)
    {
        col = Qt::color0;
    }
    list->insertItem(0, item);
    emit colorChanged(R);
}

void DesignerTamplate::start_stop()
{
    if( m_timer->isActive() )
    {
       m_timer->stop();
       list->clear();
    }
    else
    {
       m_timer->start(100);
    }
}
