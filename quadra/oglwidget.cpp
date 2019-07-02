#include "oglwidget.h"
#include <QKeyEvent>
#include <string.h>
#include <stdio.h>
#include <QDebug>
#include <iostream>

using namespace std;

#define PI 3.14159265359

int time_casa = 0;
int time_visitante = 0;
char texto[30];
GLfloat win;

GLfloat x = 50.0f;
GLfloat y = 50.0f;
GLfloat z = 15.0f;

GLfloat posX = 0.0, posY= 0.0;
GLint time1 = 0, time2 = 0;

#define SPEEDBALL 0.02

bool OGLWidget::_NAIVE1ALGO = true;
bool OGLWidget::_NAIVE2ALGO = true;
GLfloat OGLWidget::_LINESIZE = 1.0f;

GLfloat OGLWidget::_x = 50.0f;
GLfloat OGLWidget::_y = 50.0f;
GLfloat OGLWidget::_z = 15.0f;

GLchar OGLWidget::_aux ;

Color OGLWidget::_COLOR = {.r = 1.0, .g = 1.0, .b = 1.0};
vector<int> OGLWidget::_COORDINATES;

static double fullcircle = 2 * PI;
static double semicircle = PI;
static double borderrounded = PI / 2;



void draw_point(Point p, Color c);
void draw_point(Point p, GLfloat size, Color c);
void draw_circle_aux(Point center, Point p, CircleType type, Color c);
void draw_bresenham_circle(Point center, int r, CircleType type, Color c);
void draw_naive_circle(Point center, int r, CircleType type, Color c);
void draw_naive_circle_cartesian(Point center, int r, CircleType type, Color c);
void draw_naive_line(Point p1, Point p2, Color c);
void draw_breseham_line_low(Point p1, Point p2, Color c);
void draw_breseham_line_high(Point p1, Point p2, Color c);
void draw_bresenham_line(Point p1, Point p2, Color c);

void draw_line(Point p1, Point p2, Color color);
void draw_circle(Point center, int r, CircleType type, Color color);
void draw_rectangle(int width, int height, Color color);

function<void(Point, Point, Color)> method_line = draw_naive_line;
function<void(Point, int, CircleType, Color)> method_circle = draw_naive_circle;

void top();
void top_circle();
void middle();
void center_circle();
void bottom_circle();
void bottom();
void icehockeycourt();



void draw_point(Point p, Color c)
{
    glPointSize(OGLWidget::_LINESIZE);

    glBegin(GL_POINTS);
    glColor3f(c.r, c.g, c.b);
    glVertex2i(p.x, p.y);
    glEnd();
}

void draw_point(Point p, GLfloat size, Color c)
{
    glPointSize(size);

    glBegin(GL_POINTS);
    glColor3f(c.r, c.g, c.b);
    glVertex2i(p.x, p.y);
    glEnd();
}

void draw_circle_aux(Point center, Point p, CircleType type, Color c)
{
    if (type == INVERTEDSEMI)
    {
        draw_point({.x = center.x + p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x + p.y, .y = center.y - p.x}, c);

        draw_point({.x = center.x - p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x - p.y, .y = center.y - p.x}, c);
    }
    else if (type == SEMI)
    {
        draw_point({.x = center.x + p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x + p.y, .y = center.y + p.x}, c);

        draw_point({.x = center.x - p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x - p.y, .y = center.y + p.x}, c);
    }
    else if (type == FULL)
    {
        draw_point({.x = center.x + p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x + p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x + p.y, .y = center.y + p.x}, c);
        draw_point({.x = center.x + p.y, .y = center.y - p.x}, c);

        draw_point({.x = center.x - p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x - p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x - p.y, .y = center.y + p.x}, c);
        draw_point({.x = center.x - p.y, .y = center.y - p.x}, c);
    }
    else if (type == BORDERLEFT)
    {
        draw_point({.x = center.x - p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x - p.y, .y = center.y - p.x}, c);

    }
    else if (type == BORDERRIGHT)
    {
        draw_point({.x = center.x + p.x, .y = center.y - p.y}, c);
        draw_point({.x = center.x + p.y, .y = center.y - p.x}, c);

    }
    else if (type == INVERTEDBORDERLEFT)
    {
        draw_point({.x = center.x - p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x - p.y, .y = center.y + p.x}, c);
    }
    else if (type == INVERTEDBORDERIGHT)
    {
        draw_point({.x = center.x + p.x, .y = center.y + p.y}, c);
        draw_point({.x = center.x + p.y, .y = center.y + p.x}, c);
    }
}

void draw_bresenham_circle(Point center, int r, CircleType type, Color c) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    draw_circle_aux(center, {.x = x, .y = y}, type, c);

    while (y >= x)
    {
        x++;

        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }

        draw_circle_aux(center, {.x = x, .y = y}, type, c);
    }
}

void draw_naive_circle(Point center, int r, CircleType type, Color c)
{
    double angle = 0.0;
    double max_angle = 0.0;

    short flag = 1;

    switch (type) {
    case FULL:
        max_angle = fullcircle;
        break;
    case SEMI:
        max_angle = semicircle;
        break;
    case INVERTEDSEMI:
        max_angle = semicircle;
        flag = -1;
        break;

    case BORDERLEFT:
        max_angle = borderrounded;
        flag = -1;
        break;

    case BORDERRIGHT:
        angle = borderrounded;
        max_angle = PI;
        flag = -1;
        break;

    case INVERTEDBORDERIGHT:
        max_angle = borderrounded;
        break;

    case INVERTEDBORDERLEFT:
        angle = (3 * PI) / 2;
        max_angle = 2 * PI ;
        flag = -1;
        break;

    default:
        break;
    }

    while (angle <= max_angle)
    {
        int x = center.x + r * cos(angle) * flag;
        int y = center.y + r * sin(angle) * flag;

        draw_point({.x = x, .y = y}, c);

        angle += 0.01;
    }

}

void draw_naive_line(Point p1, Point p2, Color c)
{
    if (p2.x < p1.x)
    {
        int tmpx = p2.x;
        p2.x = p1.x;
        p1.x = tmpx;

        int tmpy = p2.y;
        p2.y = p1.y;
        p1.y = tmpy;
    }

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    double m = (double) dy / (double) dx;

    if (m == INFINITY)
    {
        for (int y = p1.y; y <= p2.y; ++y)
        {
            draw_point({. x = p1.x, .y = y}, c);
        }
    }
    else
    {
        int x0 = p2.x;
        int y0 = p2.y;

        if (p2.y > p1.y)
        {
            int tmp = p2.y;
            p2.y = p1.y;
            p1.y = tmp;

            y0 = p1.y;
        }

        for (int x = p1.x; x <= p2.x; ++x)
        {
            int y = y0 + (int) (m * (x - x0));
            draw_point({. x = x, .y = y}, c);
        }
    }
}

void draw_breseham_line_low(Point p1, Point p2, Color c)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = p1.y;

    for (int x = p1.x; x <= p2.x; ++x)
    {
        draw_point({. x = x, .y = y}, c);

        if (D > 0)
        {
            y = y + yi;
            D = D - 2 * dx;
        }

        D = D + 2 * dy;
    }
}

void draw_breseham_line_high(Point p1, Point p2, Color c)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = 2 * dx - dy;
    int x = p1.x;

    for (int y = p1.y; y <= p2.y; ++y)
    {
        draw_point({. x = x, .y = y}, c);

        if (D > 0)
        {
            x = x + xi;
            D = D - 2 * dy;
        }

        D = D + 2 * dx;
    }
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

void draw_bresenham_line(Point p1, Point p2, Color c)
{
    if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
    {
        if (p1.x > p2.x)
        {
            draw_breseham_line_low(p2, p1, c);
        }
        else
        {
            draw_breseham_line_low(p1, p2, c);
        }
    }
    else
    {
        if (p1.y > p2.y)
        {
            draw_breseham_line_high(p2, p1, c);
        }
        else
        {
            draw_breseham_line_high(p1, p2, c);
        }
    }

}

void draw_line(Point p1, Point p2, Color color)
{
    method_line(p1, p2, color);
}

void draw_circle(Point center, int r, CircleType type, Color color)
{
    method_circle(center, r, type, color);
}

void draw_naive_circle_cartesian(Point center, int r, CircleType type, Color c)
{
    int xi = center.x - r;
    int xf = center.x + r;

    switch (type) {
    case BORDERLEFT:
    case INVERTEDBORDERLEFT:
        xf = center.x;
        break;
    case BORDERRIGHT:
    case INVERTEDBORDERIGHT:
        xi = center.x;
        break;
    default:
        break;
    }

    for (int x = xi; x <= xf; ++x)
    {
        int square = (int) sqrt(pow(abs(r), 2.0) - pow((x - center.x), 2.0));

        int y1 = center.y + square;
        int y2 =  center.y - square;

        switch (type) {
        case FULL:
            draw_point({.x = x, .y = y2}, c);
            draw_point({.x = x, .y = y1}, c);
            break;
        case SEMI:
            draw_point({.x = x, .y = y1}, c);
            break;
        case BORDERLEFT:
        case BORDERRIGHT:
            draw_point({.x = x, .y = y2}, c);
            break;
        case INVERTEDSEMI:
            draw_point({.x = x, .y = y2}, c);
            break;
        case INVERTEDBORDERLEFT:
        case INVERTEDBORDERIGHT:
            draw_point({.x = x, .y = y1}, c);
            break;
        default:
            break;
        }
    }
}

void draw_rectangle(int width, int height, Color color)
{
    Point p0 = {.x = 0, .y = 0};
    Point p1 = {.x = width, .y = 0};
    Point p2 = {.x = 0, .y = height};
    Point p3 = {.x = width, .y = height};

    draw_line(p0, p1, color);
    draw_line(p2, p3, color);
    draw_line(p0, p2, color);
    draw_line(p1, p3, color);
}

void top()
{
    draw_line({.x = 20, .y = -115}, {.x = 170, .y = -115}, OGLWidget::_COLOR);
    draw_circle({.x = 20, .y = -95}, 20, BORDERLEFT, OGLWidget::_COLOR);
    draw_circle({.x = 170, .y = -95}, 20, BORDERRIGHT, OGLWidget::_COLOR);
}

void middle()
{
    draw_point({.x = 300, .y = 200}, OGLWidget::_COLOR);
}

void bottom()
{
    draw_line({.x = 20, .y = 225}, {.x = 170, .y = 225}, OGLWidget::_COLOR);
    draw_circle({.x = 20, .y = 205}, 20, INVERTEDBORDERLEFT, OGLWidget::_COLOR);
    draw_circle({.x = 170, .y = 205}, 20, INVERTEDBORDERIGHT, OGLWidget::_COLOR);
}

void top_circle()
{
    draw_circle({.x = 97, .y = -95}, 10, SEMI, OGLWidget::_COLOR);

}

void bottom_circle()
{
    draw_circle({.x = 97, .y = 205}, 10, INVERTEDSEMI, OGLWidget::_COLOR);

}

void center_circle()
{
    draw_circle({.x = 100, .y = 50}, 25, FULL, OGLWidget::_COLOR);

    draw_point({.x = 100, .y = 50},5, OGLWidget::_COLOR);


}

// Desenha um texto na janela GLUT
void DesenhaPlacar(char *string)
{
    glPushMatrix();
    // Posição no universo onde o texto será colocado
    //glRasterPos2f(-0.90,0.8);
    glRasterPos2f(0.0,350.0);
    //glRasterPos2f(0,0-(0*0.08));
    //glRasterPos2f(0,0);
    // Exibe caracter a caracter
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
    glPopMatrix();
}


void bola(){
    glBegin(GL_QUADS);
        glColor3f(0.0, 200.0, 200.0);
        glVertex2f(x, y + z);
        glVertex2f(x, y);
        glVertex2f(x + z, y);
        glVertex2f(x + z , y + z);
    glEnd();

}

void fotbool()
{
   // glTranslatef(180.0, -200.0, 0.0);
   // createBall();
    bola();


    glPushMatrix();
       glTranslatef(180.0, -320.0, 0.0);
       sprintf(texto, " IC %d x %d VISITANTES", time_casa, time_visitante);
       DesenhaPlacar(texto);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(200.0, 50.0, 0.0);
        draw_rectangle(200, 300, OGLWidget::_COLOR);
        glTranslatef(0.0, 95.0, 0.0);
        draw_line({.x = 0, .y = 50}, {.x = 200, .y = 50}, OGLWidget::_COLOR);
        center_circle();
    glPopMatrix();

    // area goleira cima
    glPushMatrix();
        glTranslatef(250.0, 50.0, 0.0);
        draw_rectangle(100, 60, OGLWidget::_COLOR);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(275.0, 50.0, 0.0);
        draw_rectangle(50, 35, OGLWidget::_COLOR);
    glPopMatrix();

    // semi circulo area goleiro cima
    glPushMatrix();
        glTranslatef(203.0, 210.0, 0.0);
        top_circle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(220.0, 80.0, 0.0);
        draw_point({.x = 80, .y = 14}, 2, OGLWidget::_COLOR);
    glPopMatrix();

    // area goleiro baixo
    glPushMatrix();
        glTranslatef(250.0, 290.0, 0.0);
        draw_rectangle(100, 60, OGLWidget::_COLOR);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(272.0, 315.0, 0.0);
        draw_rectangle(55, 35, OGLWidget::_COLOR);
    glPopMatrix();
    // semi circulo area goleiro baixo
    glPushMatrix();
        glTranslatef(205.0, 80.0, 0.0);
        bottom_circle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(220.0, 80.0, 0.0);
        draw_point({.x = 80, .y = 225}, 2, OGLWidget::_COLOR);
    glPopMatrix();

}

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    timer->start(10);

    cout << "Construtor" << endl;
}

OGLWidget::~OGLWidget(){

}

void OGLWidget::initializeGL()
{
    resizeGL(this->width(),this->height());
}

void OGLWidget::paintGL()
{
    if (OGLWidget::_NAIVE1ALGO)
    {
        method_line = draw_naive_line;
        method_circle = draw_naive_circle_cartesian;
    }
    else if (OGLWidget::_NAIVE2ALGO)
    {
        method_line = draw_naive_line;
        method_circle = draw_naive_circle;
    }
    else
    {
        method_line = draw_bresenham_line;
        method_circle = draw_bresenham_circle;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    if (_COORDINATES.size() >= 4)
//    {
//        for (unsigned int n = 2; n < _COORDINATES.size(); ++n)
//        {
//            if (n % 2 != 0)
//            {
//                int x1 = _COORDINATES.at(n - 3);
//                int y1 = _COORDINATES.at(n - 2);

//                int x2 = _COORDINATES.at(n - 1);
//                int y2 = _COORDINATES.at(n);

//                draw_line({.x = x1, .y = y1}, {.x = x2, .y = y2}, OGLWidget::_COLOR);
//            }
//        }
//    } else
//    {
//        if (_COORDINATES.size() == 2)
//        {
//            draw_point({.x = _COORDINATES.at(0), .y = _COORDINATES.at(1)}, OGLWidget::_COLOR);
//        }
//    }


//    if (_aux == 1){
//        _x = _x + 10;
//    }
//    if(){
//        _x = _x - 10;
//    }
//    if(){
//        _y = _y + 10;
//    }
//    if(){
//        _y =_y - 10;
//    }

    fotbool();


    //cout << _COLOR.r << " " << _COLOR.g << " " << _COLOR.b << endl;

    //    draw_naive_circle_cartesian({.x = 300, .y = 200}, 50, SEMI, _COLOR);

    glFlush();

}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    //    cout << "x: " << event->x() << " y: " << event->y() << endl;

    int x = event->x();
    int y = event->y();

    _COORDINATES.push_back(x);
    _COORDINATES.push_back(y);
}

//void OGLWidget::keyPress(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_A:

//        break;
//    case Qt::Key_Left:

//        break;
//    case Qt::Key_Right:


//        break;
//    case Qt::Key_Up:


//        break;
//    default:
//        break;
//    }
//}


void OGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);
}
