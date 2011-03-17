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
    kinect.cpp \
    dataprocessor.cpp

HEADERS  += mainwindow.h \
    widgetgl.h \
    kinect.h \
    dataprocessor.h

CONFIG += link_pkgconfig
PKGCONFIG += libfreenect opencv


FORMS    += mainwindow.ui
