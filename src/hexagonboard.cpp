
#include <QDebug>

#include "hexagonboard.h"
#include <qmath.h>
#include "hexagontile.h"

HexagonBoard::HexagonBoard(int p_width, int p_height, QWidget *parent)
    : QWidget(parent)
{
    m_hbox = new QHBoxLayout;
    m_view = new QGraphicsView;
    m_scene = new GraphicsScene;

    m_sideSize = 15;
    m_gridColor = Qt::white;
    m_gridSize = 2;


#if 0
    QGraphicsEllipseItem * ellipse = m_scene->addEllipse(-20, -20, 20, 20,QPen(), QBrush(QColor(Qt::green)));
    this->makeDraggable(ellipse);
#endif

    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setScene(m_scene);

    m_view->setMouseTracking(true);

    m_hbox->addWidget(m_view);
    this->setLayout(m_hbox);

    this->resize(600, 400);

    w = p_width * 2;
    h = p_height;

    m_type = HexagonTile::eFlat;

    updateBoard();
}

void HexagonBoard::makeDraggable(QGraphicsItem *item)
{
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    item->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

int HexagonBoard::gridSize() const
{
    return m_gridSize;
}

int HexagonBoard::loadBoard(const QString &filename)
{
    QFile jsonFile( filename );
    if ( jsonFile.open( QIODevice::ReadOnly ))
    {

        QByteArray jsonData = jsonFile.readAll();

        // Close the file
        jsonFile.close();

        // Parse the JSON data into a JSON document
        QJsonParseError jsonError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &jsonError);

        if (jsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "Failed to parse JSON:" << jsonError.errorString();
            return -1;
        }

        // Check if the JSON document is an object
        if (!jsonDocument.isObject())
        {
            qDebug() << "JSON document is not an object.";
            return -1;
        }

        // Extract the JSON object from the document
        QJsonObject obj = jsonDocument.object();

        QString version = obj["version"].toString();

        if ( version != "0.1" )
        {
            return -1;
        }

        QJsonObject map = obj["map"].toObject();
        if ( map.isEmpty() )
        {
            return -1;
        }

        w = map["width"].toInt();
        h = map["height"].toInt();

        QJsonArray tiles = map["tiles"].toArray();
        if ( tiles.isEmpty() )
        {
            return -1;
        }

        foreach (QJsonValue value, tiles)
        {

        }



    }

    return 0;
}

void HexagonBoard::setGridSize(int newGridSize)
{
    m_gridSize = newGridSize;
    updateGrid();
}

void HexagonBoard::setGridColor(const QColor &newGridColor)
{
    m_gridColor = newGridColor;
    updateGrid();
}

QColor HexagonBoard::backgroundColor() const
{
    return m_backgroundColor;
}

void HexagonBoard::setBackgroundColor(const QColor &newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}



float HexagonBoard::sideSize() const
{
    return m_sideSize;
}

void HexagonBoard::setGridWidth(float value)
{
    w = value * 2;
    updateBoard( );
}

void HexagonBoard::setGridHeight(float value)
{
    h = value;
    updateBoard();
}

void HexagonBoard::setSideSize(float newSideSize)
{
    m_sideSize = newSideSize;
    updateBoard();
}



HexagonTile::HexagonType HexagonBoard::type() const
{
    return m_type;
}

void HexagonBoard::setType(HexagonTile::HexagonType newType)
{
    m_type = newType;
    updateBoard();
}

void HexagonBoard::updateBoard()
{
    m_scene->clear();
    m_hexagons.clear();

    int counter = 0;


    for(int c = 0; c < w; c++)
    {
        for(int r = 0; r < h; r++)
        {
            if( (r % 2 != c % 2))
            {
                // don't add a hexagon, it isn't on the board!
            }
            else
            {
                HexagonTile * hexagon = new HexagonTile(m_sideSize, m_type, nullptr);

                qreal dx = qSqrt(3)/2 * hexagon->sideSize();

                //hexagon->setGliph( "/data/tmp/Hexagons/build/Mountain.png" );

                hexagon->setBackground( "/data/tmp/Hexagons/assets/tiles/SBS - Tiny Texture Pack 512x512 A/Grass/Grass 1 - 512x512.png" );

                hexagon->setGridSize(  m_gridSize );
                m_scene->addItem(hexagon);
                m_hexagons.append( hexagon );
                if ( m_type == HexagonTile::eFlat )
                {
                    hexagon->setPos( hexagon->sideSize() * 1.5 * r, dx * c );
                }
                else
                {
                    hexagon->setPos( dx * c, hexagon->sideSize() * 1.5 * r  );
                }
                hexagon->setToolTip(QString::number(r) + "," + QString::number(c));
            }
        }
    }

}

void HexagonBoard::updateGrid()
{
    foreach( HexagonTile *tile, m_hexagons )
    {
        if ( nullptr != tile )
        {
            //tile->setPen( QPen( QBrush( m_gridColor) , m_gridSize ));
        }
    }
}
