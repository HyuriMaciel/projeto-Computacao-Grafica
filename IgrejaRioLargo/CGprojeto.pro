#-------------------------------------------------
#
# Project created by QtCreator 2018-09-17T20:59:34
#
#-------------------------------------------------

QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGprojeto
TEMPLATE = app



SOURCES += main.cpp\
           mainwindow.cpp\
          imagem.cpp \

HEADERS  += mainwindow.h \
            imagem.h \
           mainwindow.h

FORMS    += mainwindow.ui




LIBS += -lGL \
        -lGLU \
        -lglut \


LIBS += -lsfml-audio
LIBS += -lsfml-graphics
LIBS += -lsfml-network
LIBS += -lsfml-window
LIBS += -lsfml-system

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target

DISTFILES += \
    /home/hyuri/git/projetoCG/IgrejaRioLargo/img/piso.jpg




