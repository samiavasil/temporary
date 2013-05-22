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

#include <QtGui>

#include "vdiagramitem.h"

//! [0]
VDiagramItem::VDiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    QPainterPath path;
    switch (myDiagramType) {
        case StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        case Conditional:
            myPolygon << QPointF(-10, 0) << QPointF(0, 10)
                      << QPointF(10, 0) << QPointF(0, -10)
                      << QPointF(-10, 0);
            break;
        case Step:
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
}

VDiagramItem::VDiagramItem(QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    myDiagramType = None;
    myContextMenu = contextMenu;

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
//! [0]
VDiagramItem::VDiagramItem(const VDiagramItem& diagram)
{
	QGraphicsPolygonItem(diagram.parentItem(),diagram.scene());
	//QGraphicsPolygonItem(static_cast<QGraphicsPolygonItem>(diagram));
	// copy from general GraphcsItem
	setBrush(diagram.brush());
	setPen(diagram.pen());
	setTransform(diagram.transform());

    // copy VDiagramItem
	myDiagramType = diagram.myDiagramType;
	myContextMenu = diagram.myContextMenu;

	QPainterPath path;
	switch (myDiagramType) {
		case StartEnd:
			path.moveTo(200, 50);
			path.arcTo(150, 0, 50, 50, 0, 90);
			path.arcTo(50, 0, 50, 50, 90, 90);
			path.arcTo(50, 50, 50, 50, 180, 90);
			path.arcTo(150, 50, 50, 50, 270, 90);
			path.lineTo(200, 25);
			myPolygon = path.toFillPolygon();
			break;
		case Conditional:
			myPolygon << QPointF(-100, 0) << QPointF(0, 100)
					  << QPointF(100, 0) << QPointF(0, -100)
					  << QPointF(-100, 0);
			break;
		case Step:
			myPolygon << QPointF(-100, -100) << QPointF(100, -100)
					  << QPointF(100, 100) << QPointF(-100, 100)
					  << QPointF(-100, -100);
			break;
		default:
			myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
					  << QPointF(120, 80) << QPointF(70, -80)
					  << QPointF(-120, -80);
			break;
	}
	setPolygon(myPolygon);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}


//! [4]
QPixmap VDiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}
//! [4]

//! [5]
void VDiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
//! [5]

//! [6]
QVariant VDiagramItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        ;
    }

    return value;
}
//! [6]
VDiagramItem* VDiagramItem::copy()
{
    VDiagramItem* newVDiagramItem=new VDiagramItem(*this);
    return newVDiagramItem;
}
#include<QDebug>
void VDiagramItem::hoverMoveEvent(QGraphicsSceneHoverEvent *e) {

  //
    QGraphicsItem *parent = parentItem();
    if( parent )
    {

      QPointF point =   e->scenePos() ;
      QRectF rect   =  parent->sceneBoundingRect();
      int x=point.x(),y=point.y();
      qDebug() << "point: " << point<<endl;

      qDebug() << "rect:  " << rect <<endl;

      if( x > ((rect.x() +rect.width())/2) )
      {
          x = rect.x()+rect.width();
      }
      else
      {
          x = rect.x();
      }


      if( y > ((rect.y()+rect.height())/2) )
      {
          y = rect.y()+rect.height();
      }
      else
      {
          y = rect.y();
      }
      setPos(parent->mapFromScene(QPointF(x,y)));
      qDebug() << "QPointF(x,y):  " << QPointF(x,y) <<endl<<endl<<endl<<endl<<endl;
   //   point = parent->pos();FromScene
     // setPos(10,10);// mapToParent( e->screenPos() ).x(),mapToParent( e->screenPos() ).y());
    }/**/
  //  QGraphicsPolygonItem::hoverEnterEvent(e);
}
