#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <string.h>
#include <QWidget>
#include <QtGui>

#include <QKeyEvent>
#include <QDebug>

#include <QApplication>

enum CircleType
{
    FULL, SEMI, INVERTEDSEMI, BORDERLEFT, BORDERRIGHT, INVERTEDBORDERLEFT, INVERTEDBORDERIGHT
};

struct Point
{
    GLint x, y;
};

struct Color
{
    GLfloat r, g, b;
};

class OGLWidget : public QOpenGLWidget
{

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

    static Color _COLOR;
    static bool _NAIVE1ALGO;
    static bool _NAIVE2ALGO;
    static GLfloat _LINESIZE;
    static std::vector<int> _COORDINATES;
    static GLfloat _x;
    static GLfloat _y;
    static GLfloat _z;
    static GLchar _aux;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
 // void keyPress(QKeyEvent *event);
 // void keyPressEvent(QKeyEvent *event);

 //void paintEvent(QPaintEvent *event);
private:




};

#endif // OGLWIDGET_H
