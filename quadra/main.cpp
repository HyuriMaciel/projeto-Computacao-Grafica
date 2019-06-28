#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    //glutKeyboardFunc(GerenciaTeclado);
    MainWindow w;
    w.show();

    return a.exec();
}
