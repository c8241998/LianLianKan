#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T11:38:42
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mybutton.cpp \
    gaming.cpp \
    gamesetup.cpp \
    ranklist.cpp \
    client.cpp \
    grade.cpp \
    howtoplay.cpp \
    login.cpp

HEADERS += \
        mainwindow.h \
    gaming.h \
    mybutton.h \
    gamesetup.h \
    header.hpp \
    ranklist.h \
    client.hpp \
    grade.h \
    howtoplay.h \
    login.h

FORMS += \
        mainwindow.ui \
    gaming.ui \
    gamesetup.ui \
    ranklist.ui \
    grade.ui \
    howtoplay.ui \
    login.ui

RESOURCES += \
    icon.qrc

DISTFILES +=
