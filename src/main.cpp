#include "hexagonboard.h"
#include <QApplication>

#include <QDoubleSpinBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexagonBoard w(30,30);
    w.show();


    QWidget w2;
    w2.setLayout( new QVBoxLayout() );
    QDoubleSpinBox * spinW = new QDoubleSpinBox;
    QDoubleSpinBox * spinH = new QDoubleSpinBox;
    QDoubleSpinBox * spinS = new QDoubleSpinBox;

    spinW->setValue( 30 );
    spinH->setValue( 30 );
    spinS->setValue( 45 );

    w2.layout()->addWidget( spinW );
    w2.layout()->addWidget( spinH );
    w2.layout()->addWidget( spinS );



    QObject::connect( spinW, &QDoubleSpinBox::valueChanged, &w, &HexagonBoard::setGridWidth );
    QObject::connect( spinH, &QDoubleSpinBox::valueChanged, &w, &HexagonBoard::setGridHeight );
    QObject::connect( spinS, &QDoubleSpinBox::valueChanged, &w, &HexagonBoard::setSideSize );

    w2.resize(350,200);
    w2.show();



    return a.exec();
}
