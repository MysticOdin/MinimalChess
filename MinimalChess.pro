TEMPLATE = app

QT += qml quick widgets

TARGET = MinimalChess

SOURCES += main.cpp \
    Place.cpp \
    Board.cpp \
    IPiece.cpp \
    Pawn.cpp \
    Knight.cpp \
    Queen.cpp \
    Rook.cpp \
    Bishop.cpp \
    King.cpp \
    BoardQObjectAbstraction.cpp \
    Serialization.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    IPiece.h \
    Place.h \
    ChessGenericTypes.h \
    Board.h \
    Pawn.h \
    Knight.h \
    Queen.h \
    Rook.h \
    Bishop.h \
    King.h \
    BoardQObjectAbstraction.h \
    Move.h \
    Serialization.h

INCLUDEPATH += D:/MinGW/lib/boost_1_59_0
