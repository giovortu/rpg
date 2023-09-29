#include "draggablepiece.h"
#include <QDrag>
#include <QMimeData>

DraggablePiece::DraggablePiece()
{
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QMimeData *data = new QMimeData;
    data->setColorData( QColor( Qt::green) );

    QDrag *drag = new QDrag( nullptr );
    drag->setMimeData(data);
    drag->exec();
}
