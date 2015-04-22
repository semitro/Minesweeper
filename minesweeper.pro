#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T19:03:47
#
#-------------------------------------------------

QT       += core gui
RC_FILE = res.qrc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minesweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    render.cpp \
    logic.cpp

HEADERS  += mainwindow.h \
    render.h \
    logic.h

FORMS    += mainwindow.ui


LIBS += -L"/home/semitro/libs/SFML-2.2/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += "/home/semitro/libs/SFML-2.2/include"
DEPENDPATH += "/home/semitro/libs/SFML-2.2/include"

#где /home/user/Projects/SFML/lib - путь к только что собранным вами библиотекам, а
#/home/user/Projects/SFML/include - путь к загруженным вами исходникам

DISTFILES +=

RESOURCES += \
    res.qrc
