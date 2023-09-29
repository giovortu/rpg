#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class DraggablePiece : public QGraphicsItem
{
public:
    DraggablePiece();
    void mousePressEvent(QGraphicsSceneMouseEvent*);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};



#endif // DRAGGABLEPIECE_H
