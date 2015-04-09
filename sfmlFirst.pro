#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T13:27:37
#
#-------------------------------------------------

QT       += core gui

LIBS += -L"/home/semitro/libs/SFML-2.2/lib"



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sfmlFirst
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/release/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/debug/ -lsfml-system
else:unix: LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/ -lsfml-system

INCLUDEPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/System
DEPENDPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/System

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/release/ -lsfml-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/debug/ -lsfml-audio
else:unix: LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/ -lsfml-audio

INCLUDEPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Audio
DEPENDPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Audio

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/release/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/debug/ -lsfml-window
else:unix: LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/ -lsfml-window

INCLUDEPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Window
DEPENDPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Window

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/release/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/debug/ -lsfml-graphics
else:unix: LIBS += -L$$PWD/../../../../../lib/SFML-2.2/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Graphics
DEPENDPATH += $$PWD/../../../../../lib/SFML-2.2/include/SFML/Graphics

