#include "hexagontile.h"
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QStyleOptionGraphicsItem>

HexagonTile::HexagonTile(float size, HexagonType type, QGraphicsItem * parent): QGraphicsPolygonItem(parent)
{
    setAcceptDrops(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag( QGraphicsItem::ItemClipsToShape );
    setFlag( QGraphicsItem::ItemClipsChildrenToShape );

    m_size = size;
    m_type = type;
    m_gridSize = 2;
    m_focusColor = Qt::red;
    m_defaultColor = QColor::fromRgbF(1,0,0,0.5);// Qt::white;

    setBrush( QBrush() );


    m_background = new QGraphicsPixmapItem(this);
    m_background->setZValue( 100 );


    m_gliph = new QGraphicsPixmapItem(this);
    m_gliph->setZValue( 90 );

    m_highlight = new QGraphicsPolygonItem( this );
    m_background->setZValue( 0 );

    updateShape();
}


void HexagonTile::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    m_highlight->setPen(   QPen( QBrush( m_focusColor) , m_gridSize * 3 )   );
}

void HexagonTile::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    m_highlight->setPen(   QPen( QBrush( m_defaultColor) , m_gridSize )   );
}

void HexagonTile::hoverMoveEvent(QGraphicsSceneHoverEvent*)
{
}

void HexagonTile::dragEnterEvent(QGraphicsSceneDragDropEvent*)
{
}

void HexagonTile::dragLeaveEvent(QGraphicsSceneDragDropEvent*)
{
}

void HexagonTile::dragMoveEvent(QGraphicsSceneDragDropEvent*)
{
}

void HexagonTile::dropEvent(QGraphicsSceneDragDropEvent*)
{
}

void HexagonTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QStyleOptionGraphicsItem *_option = const_cast<QStyleOptionGraphicsItem*>(option);

    _option->state &= ~QStyle::State_Selected;
    QGraphicsPolygonItem::paint( painter, _option, widget );
}

QGraphicsPixmapItem *HexagonTile::gliph() const
{
    return m_gliph;
}


QGraphicsPixmapItem *HexagonTile::background() const
{
    return m_background;
}


void HexagonTile::setGliph(QPixmap &newGliph)
{
    updateShape();

    QRect bound = shape().boundingRect().toRect();
    QPixmap p = newGliph.scaled( qSqrt(3)/2 * bound.width(), qSqrt(3)/2 * bound.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    QRect r = p.rect();

    m_gliph->setPixmap( p );
    m_gliph->setPos( bound.center() - r.center() );
}

void HexagonTile::setGliph(const QString &path)
{
    QPixmap pix(path);
    setGliph(pix);
}


void HexagonTile::setGridSize(int newGridSize)
{
    m_gridSize = newGridSize;
    updateShape();
}

int HexagonTile::gridSize() const
{
    return m_gridSize;
}

QColor HexagonTile::defaultColor() const
{
    return m_defaultColor;
}

void HexagonTile::setDefaultColor(const QColor &newDefaultColor)
{
    m_defaultColor = newDefaultColor;
    updateShape();
}

QColor HexagonTile::focusColor() const
{
    return m_focusColor;
}


void HexagonTile::setFocusColor(const QColor &newFocusColor)
{
    m_focusColor = newFocusColor;
    updateShape();
}

void HexagonTile::setBackground(QPixmap &pix)
{
    updateShape();
    QRectF bound = shape().boundingRect();
    QPixmap p = pix.scaled( bound.width(), bound.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    m_background->setPixmap( p );
    m_background->setPos(-bound.width()/2,-bound.height()/2);

}

void HexagonTile::setBackground(const QString &path)
{
    QPixmap pix(path);
    setBackground(pix);
}

HexagonTile::HexagonType HexagonTile::hexagonType() const
{
    return m_type;
}

void HexagonTile::setHexagonType(HexagonTile::HexagonType newType)
{
    m_type = newType;
    updateShape();
}

float HexagonTile::sideSize() const
{
    return m_size;
}

void HexagonTile::setSideSize(float newSize)
{
    m_size = newSize;
    updateShape();
}

void HexagonTile::updateShape()
{
    QPolygonF polygon;

    qreal dx = qSqrt(3)/2 * m_size;

    if ( m_type == eNormal )
    {
        // standing on a point
        polygon << QPointF(dx, -m_size/2)
                << QPointF(0, -m_size)
                << QPointF(-dx, -m_size/2)
                << QPointF(-dx, m_size/2)
                << QPointF(0, m_size)
                << QPointF(dx, m_size/2);
    }
    else
    {
        // Sitting flat
        polygon << QPointF(-m_size/2, dx)
                << QPointF(-m_size, 0)
                << QPointF(-m_size/2, -dx)
                << QPointF(m_size/2, -dx)
                << QPointF(m_size, 0)
                << QPointF(m_size/2, dx);
    }

    m_highlight->setPolygon( polygon );
    m_highlight->setPen(   QPen( QBrush( m_defaultColor) , m_gridSize )   );
    setPolygon( polygon );



}



