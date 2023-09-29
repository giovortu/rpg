#ifndef HEXAGONBOARD_H
#define HEXAGONBOARD_H

#include <QWidget>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QGraphicsView>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

#include "graphicsscene.h"
#include "hexagontile.h"

class HexagonBoard : public QWidget
{
    Q_OBJECT

public:
    HexagonBoard(int width, int height, QWidget *parent = 0);

    virtual ~HexagonBoard() = default;

    HexagonTile::HexagonType type() const;
    float sideSize() const;
    QColor backgroundColor() const;
    int gridSize() const;


public slots:

    int loadBoard( const QString &filename );

    void setBackgroundColor(const QColor &newBackgroundColor);
    void setGridColor(const QColor &newGridColor);
    void setGridSize(int newGridSize);
    void setGridWidth( float value );
    void setGridHeight( float value );
    void setType(HexagonTile::HexagonType newType);
    void setSideSize(float newSideSize);

protected:

    void updateBoard();
    void updateGrid();

    void makeDraggable(QGraphicsItem *item);

    HexagonTile::HexagonType m_type;

    QHBoxLayout * m_hbox;
    QGraphicsView * m_view;
    GraphicsScene * m_scene;

    float m_sideSize;

    float w,h;

    QColor m_backgroundColor;
    QColor m_gridColor;

    int m_gridSize;

    QList<HexagonTile*> m_hexagons;


};

#endif // HEXAGONBOARD_H
