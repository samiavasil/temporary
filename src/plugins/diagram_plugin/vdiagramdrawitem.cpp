/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include<QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtGui>
#else
#include <QtWidgets>
#endif

#include <iostream>

#include "vdiagramdrawitem.h"
#include "diagramscene.h"


//! [0]
VDiagramDrawItem::VDiagramDrawItem(VDiagramType diagramType, QMenu *contextMenu,
                                 QGraphicsItem *parent, QGraphicsScene *scene)
    : VDiagramItem(contextMenu,parent,scene)
{
    myPos2=pos();
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    myPolygon=createPath();
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    myHoverPoint=-1;
    mySelPoint=-1;
    myHandlerWidth=2.0;
    int j = rand()%10 + 1;
    for( int i = 0; i < j; i++ )
    {
        addInput();
    }
    j = rand()%10 + 1;
    for( int i = 0; i < j; i++ )
    {
        addOutput();
    }
}
//! [0]
VDiagramDrawItem::VDiagramDrawItem(const VDiagramDrawItem& diagram)
    : VDiagramItem(diagram.myContextMenu,diagram.parentItem(),0)
{

    myDiagramType = diagram.myDiagramType;
    myContextMenu = diagram.myContextMenu;
    // copy from general GraphcsItem
    setBrush(diagram.brush());
    setPen(diagram.pen());
    setTransform(diagram.transform());
    myPos2=diagram.myPos2;
    myPolygon=createPath();
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    myHoverPoint=-1;
    mySelPoint=-1;
    myHandlerWidth=2.0;

}

void SortItemsByPosition( QList<VDiagramItem*> &list )
{
    int i;
    bool sort;
    int count = list.count() - 1;
    if( count > 0 )
    {
        do
        {
            qreal pos1,pos2;
            sort = false;
            for( i = 0; i < count ; i++ )
            {
                pos1 = list[i]->pos().y();
                pos2 = list[ i+1 ]->pos().y();
                if( pos2 < pos1 )
                {
                   list.move( i+1, i );
                   sort = true;
                }
            }
        } while( sort );
    }
}

void VDiagramDrawItem::updateInOutView()
{

    qreal grid;
    if( scene() )
    {
        if( 0 < listIn.count() )
        {
           SortItemsByPosition( listIn );
           grid  = ( boundingRect().height()  -  2*(myHandlerWidth + pen().width()))/(listIn.count());
           for( int i = 0; i < listIn.count() ;i++ )
           {
               listIn[i]->setPos( 0, i*grid );
           }
        }

        if( 0 < listOut.count() )
        {
            SortItemsByPosition( listOut );
            grid  = ( boundingRect().height() -  2*(myHandlerWidth + pen().width()) )/(listOut.count());

            for( int i = 0; i < listOut.count() ;i++ )
            {
                listOut[i]->setPos( boundingRect().width()-listOut[i]->boundingRect().width()-2*(myHandlerWidth + pen().width()), i*grid );
            }
        }
    }
}

void VDiagramDrawItem::addInput()
{
    VDiagramItem* item = new VDiagramItem(VDiagramItem::Input,NULL,this);
    item->setToolTip( QString("%1").arg(listIn.count()+1) );
    listIn.append(item);
    updateInOutView();
}

void VDiagramDrawItem::addOutput()
{
    VDiagramItem* item = new VDiagramItem(VDiagramItem::Output,NULL,this);
    item->setToolTip( QString("%1").arg(listOut.count()+1) );
    listOut.append( item );
    updateInOutView();
}

//! [1]
QPolygonF VDiagramDrawItem::createPath()
{
    qreal dx=myPos2.x();
    qreal dy=myPos2.y();

    QPainterPath path;
    QPolygonF polygon;
    switch (myDiagramType) {
    case Rectangle:
        path.moveTo(0, 0);
        path.lineTo(dx,0);
        path.lineTo(dx,dy);
        path.lineTo(0,dy);
        path.lineTo(0,0);
        polygon = path.toFillPolygon();
        break;
    case Ellipse:
        path.addEllipse(0,0,dx,dy);
        polygon = path.toFillPolygon();
        break;
    default:
        break;
        polygon = QPolygonF();
    }
    return polygon;
}
//! [4]
QPixmap VDiagramDrawItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(10, 10);
    painter.drawPolyline(myPolygon);

    return pixmap;
}
//! [4]

//! [5]
void VDiagramDrawItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if( myContextMenu )
        myContextMenu->exec(event->screenPos());
}
//! [5]

//! [6]
QVariant VDiagramDrawItem::itemChange(GraphicsItemChange change,
                                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        ;
    }
    return value;
}

//! [6]
VDiagramItem* VDiagramDrawItem::copy()
{
    VDiagramDrawItem* newDiagramDrawItem=new VDiagramDrawItem(*this);
    return dynamic_cast<VDiagramItem*>(newDiagramDrawItem);
}

void VDiagramDrawItem::setPos2(qreal x,qreal y)
{
    myPos2=mapFromScene(QPointF(x,y));
    myPolygon=createPath();
    setPolygon(myPolygon);
}

void VDiagramDrawItem::setPos2(QPointF newPos)
{
    prepareGeometryChange();
    myPos2   = mapFromScene( newPos );
    if( myPos2.x() < getMinX() )
        myPos2.setX( getMinX()  );
    if( myPos2.y() < getMinY() )
        myPos2.setY( getMinY()  );
    myPolygon=createPath();
    setPolygon(myPolygon);
}

void VDiagramDrawItem::setDimension(QPointF newPos)
{
    prepareGeometryChange();
    myPos2=newPos;
    myPolygon=createPath();
    setPolygon(myPolygon);
}

QPointF VDiagramDrawItem::getDimension()
{
    return myPos2;
}
qreal VDiagramDrawItem::getMinX()
{
    qreal size = 10;

    if( 0 < listIn.count() )
    {
       size = 3 * listIn[0]->boundingRect().width();
    }
    if( 0 < listOut.count() )
    {
       size = 3 * listOut[0]->boundingRect().width();
    }

    return size;
}

qreal VDiagramDrawItem::getMinY()
{
    qreal size = 0;
    qreal outp_size = 0;
    qreal grid;

    if( 0 < listIn.count() )
    {
       grid = ((DiagramScene*)scene())->grid();
       grid = ceil( listIn[0]->boundingRect().height()/grid )*grid;
       size = ( ( listIn.count())  * grid ) + (2*(myHandlerWidth + pen().width()));
    }

    if( 0 < listOut.count() )
    {
        grid = ((DiagramScene*)scene())->grid();
        grid = ceil( listOut[0]->boundingRect().height()/grid )*grid;
        outp_size = (( listOut.count()) * grid) + - (2*(myHandlerWidth + pen().width()));
    }

    if(  size < outp_size )
    {
        size = outp_size;
    }
    return size;
}

void VDiagramDrawItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(pen());


    painter->setBrush(brush());

    painter->drawPolygon(polygon());

    // selected
    if(isSelected()){
        // Rect
        QPen selPen=QPen(Qt::DashLine);
        selPen.setColor(Qt::red);
        selPen.setWidth( 4 );
        QBrush selBrush=QBrush(Qt::NoBrush);
        painter->setBrush(selBrush);
        painter->setPen(selPen);
        painter->drawRect(QRectF(QPointF(0,0),myPos2));
        // Draghandles
        selBrush=QBrush(Qt::cyan,Qt::SolidPattern);
        selPen=QPen(Qt::cyan);
        painter->setBrush(selBrush);
        painter->setPen(selPen);
        QPointF point;
        for(int i=0;i<8;i++)
        {
            if(i<3) point=QPointF(myPos2.x()/2*i,0);
            if(i==3) point=QPointF(myPos2.x(),myPos2.y()/2);
            if(i>3 && i<7) point=QPointF(myPos2.x()/2*(i-4),myPos2.y());
            if(i==7) point=QPointF(0,myPos2.y()/2);
            if(i==myHoverPoint){
                painter->setBrush(QBrush(Qt::red));
            }
            // Rect around valid point
            painter->drawRect(QRectF(point-QPointF(2,2),point+QPointF(2,2)));
            if(i==myHoverPoint){
                painter->setBrush(selBrush);
            }
        }// foreach
    }// if
}

void VDiagramDrawItem::hoverMoveEvent(QGraphicsSceneHoverEvent *e) {
#ifdef DEBUG
    std::cout << "entered" << std::endl;
    std::cout << e->pos().x() << "/" << e->pos().y() << std::endl;
#endif

    if (isSelected()) {
        QPointF hover_point = e -> pos();
        QPointF point;
        for(myHoverPoint=0;myHoverPoint<8;myHoverPoint++){
            if(myHoverPoint<3) point=QPointF(myPos2.x()/2*myHoverPoint,0);
            if(myHoverPoint==3) point=QPointF(myPos2.x(),myPos2.y()/2);
            if(myHoverPoint>3 && myHoverPoint<7) point=QPointF(myPos2.x()/2*(myHoverPoint-4),myPos2.y());
            if(myHoverPoint==7) point=QPointF(0,myPos2.y()/2);
            if(hasClickedOn(hover_point,point)) break;
        }//for
        if(myHoverPoint==8) myHoverPoint=-1;
        else update();
    }
    VDiagramItem::hoverEnterEvent(e);
}

void VDiagramDrawItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e) {
#ifdef DEBUG
    std::cout << "left" << std::endl;
#endif
    if (isSelected()) {
        if(myHoverPoint>-1){
            myHoverPoint=-1;
            update();
        }
    }
    VDiagramItem::hoverLeaveEvent(e);
}

bool VDiagramDrawItem::hasClickedOn(QPointF press_point, QPointF point) const {
    return (
                press_point.x() >= point.x() - myHandlerWidth &&\
                press_point.x() <  point.x() + myHandlerWidth &&\
                press_point.y() >= point.y() - myHandlerWidth &&\
                press_point.y() <  point.y() + myHandlerWidth
                );
}


QPainterPath VDiagramDrawItem::shape() const {
    QPainterPath myPath;
    myPath.addPolygon(polygon());
    if(isSelected()){
        QPointF point;
        for(int i=0;i<8;i++)
        {
            if(i<3) point=QPointF(myPos2.x()/2*i,0);
            if(i==3) point=QPointF(myPos2.x(),myPos2.y()/2);
            if(i>3 && i<7) point=QPointF(myPos2.x()/2*(i-4),myPos2.y());
            if(i==7) point=QPointF(0,myPos2.y()/2);
            // Rect around valid point
            myPath.addRect(QRectF(point-QPointF(myHandlerWidth,myHandlerWidth),point+QPointF(myHandlerWidth,myHandlerWidth)));
        }// for
    }// if
    return myPath;
}

QRectF VDiagramDrawItem::boundingRect() const
{
    qreal extra = pen().width() / 2.0 + myHandlerWidth;
    qreal minx = myPos2.x() < 0 ? myPos2.x() : 0;
    qreal maxx = myPos2.x() < 0 ? 0 : myPos2.x() ;
    qreal miny = myPos2.y() < 0 ? myPos2.y() : 0;
    qreal maxy = myPos2.y() < 0 ? 0 : myPos2.y() ;

    QRectF newRect = QRectF(minx,miny,maxx-minx,maxy-miny)
            .adjusted(-extra, -extra, extra, extra);
    return newRect;
}

void VDiagramDrawItem::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    if(isSelected()){
        if (e -> buttons() & Qt::LeftButton) {
            QPointF mouse_point = e -> pos();
            QPointF point;
            for(mySelPoint=0;mySelPoint<8;mySelPoint++){
                if(mySelPoint<3) point=QPointF(myPos2.x()/2*mySelPoint,0);
                if(mySelPoint==3) point=QPointF(myPos2.x(),myPos2.y()/2);
                if(mySelPoint>3 && mySelPoint<7) point=QPointF(myPos2.x()/2*(mySelPoint-4),myPos2.y());
                if(mySelPoint==7) point=QPointF(0,myPos2.y()/2);
                if(hasClickedOn(mouse_point,point)) break;
            }//for
            if(mySelPoint==8) mySelPoint=-1;
            else e->accept();
        }
    }
    VDiagramItem::mousePressEvent(e);
}

void VDiagramDrawItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    // left click
    if ((e -> buttons() & Qt::LeftButton)&&(mySelPoint>-1)) {
        QPointF mouse_point = onGrid(e -> pos());
#ifdef DEBUG
        std::cout << "Corner: " << mySelPoint << std::endl;
        std::cout << "mouse: " << mouse_point.x() << "/" << mouse_point.y() << std::endl;
        std::cout << "pos2: " << myPos2.x() << "/" << myPos2.y() << std::endl;
#endif

        prepareGeometryChange();
        switch (mySelPoint) {
        case 0:
        {
            QPointF t(0,0);
            if( myPos2.x() - mouse_point.x() >= getMinX() )
            {
                t.setX( mouse_point.x() );
            }

            if( myPos2.y() - mouse_point.y() >= getMinY() )
            {
                t.setY( mouse_point.y() );
            }

            if( t != QPointF(0,0) )
            {
                myPos2 = myPos2-t;
                setPos(mapToScene(t));
            }
            break;
        }
        case 1:
            if( myPos2.y() - mouse_point.y() >= getMinY() )
            {
                setPos(pos().x(),mapToScene(mouse_point).y());
                myPos2.setY(myPos2.y()-mouse_point.y());
            }
            break;
        case 2:
            if( mouse_point.x() >= getMinX() )
            {
                myPos2.setX(mouse_point.x());
            }
            if( myPos2.y() - mouse_point.y() >= getMinY() )
            {
                setPos(pos().x(),mapToScene(mouse_point).y());
                myPos2.setY( myPos2.y() - mouse_point.y() );
            }
            break;
        case 3:
            if( mouse_point.x() < getMinX() )
            {
                myPos2.setX(getMinX());
            }
            else
            {
                myPos2.setX(mouse_point.x());
            }
            break;
        case 6:
            if( mouse_point.x() >= getMinX() )
                myPos2.setX(mouse_point.x());
            else
                myPos2.setX(getMinX());
            if( mouse_point.y()  >= getMinY() )
                myPos2.setY(mouse_point.y());
            else
                myPos2.setY(getMinY());
            break;
        case 5:
            if( mouse_point.y() >= getMinY() )
            {
                myPos2.setY(mouse_point.y());
            }
            else
            {
                myPos2.setY(getMinY());
            }

            break;
        case 4:
            if(   mouse_point.y() >= getMinY() )
            {
                myPos2.setY(  mouse_point.y() );
            }
            if( myPos2.x() - mouse_point.x() >= getMinX() )
            {
                setPos( mapToScene(mouse_point).x() , pos().y() );
                myPos2.setX(myPos2.x()-mouse_point.x());
            }
            break;
        case 7:
            if( myPos2.x() - mouse_point.x() >= getMinX() )
            {
               setPos(mapToScene(mouse_point).x(),pos().y());
               myPos2.setX(myPos2.x()-mouse_point.x());
            }
            break;
        default:
            break;
        }

        myPolygon=createPath();
        setPolygon(myPolygon);
        updateInOutView();
    }
    else
        VDiagramItem::mouseMoveEvent(e);

}

