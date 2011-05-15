#-------------------------------------------------
#
# Project created by QtCreator 2011-05-11T09:08:49
#
#-------------------------------------------------

QT       += core gui

TARGET = uQuarto
TEMPLATE = app

INCLUDEPATH += . \
               GUI \
               engine

SOURCES += main.cpp\
    GUI/QPiece.cpp \
    engine/PlayGame.cpp \
    GUI/MainWindow.cpp \
    engine/MCTS.cpp \
    engine/Board.cpp \
    engine/Piece.cpp

HEADERS  += \
    GUI/QPiece.h \
    engine/PlayGame.h \
    GUI/MainWindow.h \
    engine/MCTS.h \
    engine/Board.h \
    engine/Piece.h

RESOURCES += \
    uQuarto.qrc
