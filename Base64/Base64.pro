#-------------------------------------------------
#
# Project created by QtCreator 2021-02-14T23:25:47
#
#-------------------------------------------------

QT   += core gui
RC_ICONS += Base64.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Base64
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    base64.h

FORMS    += widget.ui

CONFIG += C++11

DISTFILES +=

RESOURCES += \
    res.qrc
