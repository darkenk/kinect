#-------------------------------------------------
#
# Project created by QtCreator 2011-03-05T23:09:19
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = kinect
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgetgl.cpp \
    kinect.cpp

HEADERS  += mainwindow.h \
    widgetgl.h \
    kinect.h

CONFIG += link_pkgconfig
PKGCONFIG += libfreenect


FORMS    += mainwindow.ui
