#ifndef HEXAGONTILE_H
#define HEXAGONTILE_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QFocusEvent>
#include <QGraphicsItem>
//#include <QGraphicsScene

class HexagonTile : public QGraphicsPolygonItem
{
public:


    typedef enum HexagonType
    {
        eNormal = 0,
        eFlat

    }HexagonType;

    HexagonTile(float size, HexagonType type, QGraphicsItem *parent = 0);
    virtual ~HexagonTile() = default;


    HexagonType hexagonType() const;
    float sideSize() const;
    QColor focusColor() const;
    QColor defaultColor() const;
    int gridSize() const;
    QGraphicsPixmapItem *background() const;
    QGraphicsPixmapItem *gliph() const;


public slots:


    void setHexagonType(HexagonType newType);
    void setSideSize(float newSize);
    void setFocusColor(const QColor &newFocusColor);
    void setGridSize(int newGridSize);
    void setBackground( QPixmap &pix );
    void setBackground( const QString &path );
    void setGliph(QPixmap &newGliph);
    void setGliph( const QString &path );
    void setDefaultColor(const QColor &newDefaultColor);

protected:
    void updateShape();

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent*)override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent*)override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent*)override;
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent*)override;
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent*)override;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent*)override;
    virtual void dropEvent(QGraphicsSceneDragDropEvent *)override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;



private:

    float m_size;
    HexagonType m_type;

    QColor m_focusColor;
    QColor m_defaultColor;

    int m_gridSize;

    QGraphicsPixmapItem *m_background;
    QGraphicsPixmapItem *m_gliph;


    QGraphicsPolygonItem *m_highlight;



};

#endif // HEXAGONTILE_H
