#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T20:20:07
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH+=$$PWD $$PWD/src/

DESTDIR+=$$PWD/build

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hexagons
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc
UIC_DIR = uic



SOURCES +=  $$PWD/src/main.cpp\
            $$PWD/src/graphicsscene.cpp \
            $$PWD/src/draggablepiece.cpp \
            $$PWD/src/hexagonboard.cpp \
            $$PWD/src/hexagontile.cpp \
            $$PWD/src/baseabstracttile.cpp

HEADERS  += \
            $$PWD/src/graphicsscene.h \
            $$PWD/src/draggablepiece.h \
            $$PWD/src/hexagonboard.h \
            $$PWD/src/hexagontile.h \
            $$PWD/src/baseabstracttile.h
