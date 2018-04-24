#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T15:25:41
#
#-------------------------------------------------




TEMPLATE = app
TARGET   = openglax

CONFIG += warn_off
QT += widgets axserver opengl

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IgrejaRioLargo
TEMPLATE = app


SOURCES += main.cpp \
    primitivas.cpp

HEADERS  += \
    primitivas.h

FORMS    += primitivas.ui


RC_FILE = opengl.rc
DEF_FILE = opengl.def

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/opengl
INSTALLS += target


