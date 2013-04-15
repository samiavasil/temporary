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

#include "diagramitem.h"

//! [0]
DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    int pos;
    myDiagramType = diagramType;
    myContextMenu = contextMenu;
qDebug("DiagramItem %d DiagramType %d\n",this->type(),this->diagramType());
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
        case TestPoint:
            //QRectF rect = parent->boundingRect();
             pos = (int)parent->boundingRect().width()/2;
            myPolygon << QPointF(pos-5, -5) << QPointF(pos+5, -5)
                      << QPointF(pos-5, 5)  ;
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);

    if( myDiagramType == Step )
    {
        new DiagramItem( TestPoint, NULL, this );
    }
    if( myDiagramType != TestPoint )
    {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    if( myDiagramType == TestPoint  )
    {
        setAcceptsHoverEvents(true);
    }
}

DiagramItem::DiagramItem(QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    myDiagramType = None;
    myContextMenu = contextMenu;
qDebug("DiagramItem %d DiagramType %d\n",this->type(),this->diagramType());
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
//! [0]
DiagramItem::DiagramItem(const DiagramItem& diagram)
{
	QGraphicsPolygonItem(diagram.parentItem(),diagram.scene());
	//QGraphicsPolygonItem(static_cast<QGraphicsPolygonItem>(diagram));
	// copy from general GraphcsItem
    qDebug("DiagramItem %d DiagramType %d\n",this->type(),this->diagramType());
	setBrush(diagram.brush());
	setPen(diagram.pen());
	setTransform(diagram.transform());

	// copy DiagramItem
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

void DiagramItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e) {
#ifdef DEBUG
    std::cout << "entered" << std::endl;
    std::cout << e->pos().x() << "/" << e->pos().y() << std::endl;
#endif
     if ( myDiagramType == TestPoint )
    {
        setPen(QColor(Qt::red));
        setBrush(QColor(Qt::red));
        update();
    }
    QGraphicsPolygonItem::hoverEnterEvent(e);
}

void DiagramItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e) {
#ifdef DEBUG
    std::cout << "entered" << std::endl;
    std::cout << e->pos().x() << "/" << e->pos().y() << std::endl;
#endif
     if ( myDiagramType == TestPoint )
    {
        setPen(QColor(Qt::black));
        setBrush(QColor(Qt::white));
        update();
    }
    QGraphicsPolygonItem::hoverLeaveEvent(e);
}

//! [4]
QPixmap DiagramItem::image() const
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
void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    if( myContextMenu )
    myContextMenu->exec(event->screenPos());
}
//! [5]

//! [6]
QVariant DiagramItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        ;
    }

    return value;
}
//! [6]
DiagramItem* DiagramItem::copy()
{
    DiagramItem* newDiagramItem=new DiagramItem(*this);
    return newDiagramItem;
}
