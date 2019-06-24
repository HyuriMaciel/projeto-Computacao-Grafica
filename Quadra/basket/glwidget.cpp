#include "glwidget.h"
#include <GL/glut.h>
#include <math.h>
#include <QMouseEvent>
#include <stdio.h>

void pixel(int x, int y);
void auxCircle(int xc, int yc, int x, int y, int tipo);

// Funções para desenho com equação da reta e circunferência
void line(int x1, int y1, int x2, int y2);
void semiCircle(int x, int y, int radius, int direction);
void circle(int x, int y, int radius);

// Funções para desenho com algoritmo de Bresenham
void lineB(int x1, int y1, int x2, int y2);
void semiCircleB(int xc, int yc, int r, int direction);
void circleB(int xc, int yc, int r);

void drawCourt(); // Desenha a quadra
void drawBleachers(); // Desenha as arquibancadas

//Padrão
void (*fctLinha)(int, int, int, int) = &line;
void (*fctCircle)(int, int, int) = &circle;
void (*fctSemiCircle)(int, int, int, int) = &semiCircle;

int lineSize = 1;

struct ponto {
    int x;
    int y;
};

struct ponto pontos[100];
int countPonto = 0;

enum formas {CIRCULO = 0, ESQUERDA = 1, DIREITA = 2};

double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

double to_rad(double degree) {
    return (degree * M_PI) / 180.0;
}

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    this->bresenham = false;
    this->lineColorR = 255;
    this->lineColorG = 255;
    this->lineColorB = 255;
    this->backColorR = 0;
    this->backColorG = 0;
    this->backColorB = 0;

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor((float) backColorR/255.0, (float) backColorG/255.0, (float) backColorB/255.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void GLWidget::paintGL()
{
    if(reset){
        countPonto = 0;
        reset = false;
    }

    lineSize = lineS;
    glClearColor((float) backColorR/255.0, (float) backColorG/255.0, (float) backColorB/255.0, 1.0);

    if(bresenham){
        fctLinha = &lineB;
        fctCircle = &circleB;
        fctSemiCircle = &semiCircleB;
    } else {
        fctLinha = &line;
        fctCircle = &circle;
        fctSemiCircle = &semiCircle;
    }
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f ((float) lineColorR/255.0, (float) lineColorG/255.0, (float) lineColorB/255.0);
    drawCourt();
    drawBleachers();
    glFlush();
}

void GLWidget::resizeGL(int w, int h)
{
    /**
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float) w/h, 0.01, 100.0);

    updateGL();
    **/
    // Não faz nada
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    pontos[countPonto].x = event->x();
    pontos[countPonto].y = 500 - event->y();
    countPonto++;

    paintGL();
}

void pixel(int x, int y) {
    glPointSize(lineSize);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void auxCircle(int xc, int yc, int x, int y, int tipo) {
    if (tipo == CIRCULO){
        auxCircle(xc, yc, x, y, ESQUERDA);
        auxCircle(xc, yc, x, y, DIREITA);
    } else if (tipo == ESQUERDA) {  //Barriga à esquerda
        pixel(xc-x, yc+y);
        pixel(xc-x, yc-y);
        pixel(xc-y, yc+x);
        pixel(xc-y, yc-x);
    } else if (tipo == DIREITA) {  //Barriga à esquerda
        pixel(xc+x, yc+y);
        pixel(xc+x, yc-y);
        pixel(xc+y, yc+x);
        pixel(xc+y, yc-x);
    }
}

void line(int x1, int y1, int x2, int y2) {
    int dx, dy;
    dx = x2 - x1;
    dy = y2 - y1;

    float m = (float) dy/(float) dx;

    if(abs(dx) >= abs(dy)){
        if(x1 < x2){
            for (int i = x1; i < x2; i++) {
                int j = m*(i - x1) + y1;
                pixel(i, j);
            }
        } else {
            for (int i = x2; i < x1; i++) {
                int j = m*(i - x2) + y2;
                pixel(i, j);
            }
        }
    } else {
        if(y1 < y2){
            for (int j = y1; j < y2; j++) {
                int i = (j - y1)/m + x1;
                pixel(i, j);
            }
        } else {
            for (int j = y2; j < y1; j++) {
                int i = (j - y2)/m + x2;
                pixel(i, j);
            }
        }
    }
}

void lineB(int x1, int y1, int x2, int y2) {
    int dx, dy;
    int e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if (dx < 0)
        dx = -dx;

    if (dy < 0)
        dy = -dy;

    // Se x e y vão para a direita/cima (1)
    incx = x2 < x1 ? -1 : 1;
    incy = y2 < y1 ? -1 : 1;

    x = x1; y = y1;

    // Distância de x > que de y
    if (dx > dy) {  //y em função de x
        pixel(x, y);  // desenha o primeiro ponto

        e = 2 * dy - dx;
        inc1 = 2 * (dy-dx);
        inc2 = 2 * dy;

        for (int i = 0; i < dx; i++) {
          if (e >= 0) {
            y += incy;
            e += inc1;  //NE
          } else{
            e += inc2;  //E
          }
          x += incx;
          pixel(x, y);
        }
    } else {  // x em função de y
        pixel(x, y);

        e = 2 * dx - dy;  //teste
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;

        for (int i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
            pixel(x, y);
        }
    }
}

void semiCircle(int x, int y, int radius, int direction) {
    int angle = (direction == ESQUERDA) ? 90 : 270;
    for(int i = 0; i < 180; i++){
        int x1 = x + radius * cos(to_rad(i+angle));
        int y1 = y + radius * sin(to_rad(i+angle));
        pixel(x1, y1);
    }
}

void semiCircleB(int xc, int yc, int r, int direction) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        auxCircle(xc, yc, x, y, direction);
        x++;
        // check for decision parameter and correspondingly update d, x, y
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else{
            d = d + 4 * x + 6;
        }
        auxCircle(xc, yc, x, y, direction);
    }
}

void circle(int x, int y, int radius) {
    for(int i = 0; i < 360; i++){
        int x1 = x + radius * cos(to_rad(i));
        int y1 = y + radius * sin(to_rad(i));
        pixel(x1, y1);
    }
}

void circleB(int xc, int yc, int r) {
   semiCircleB(xc, yc, r, CIRCULO);
}

void drawCourt(){

    int mH = 40;
    int mV = 10;

    // QUADRA
    (*fctLinha)(0 + mH, 0 + mV, 0 + mH, 225 + mV); // reta esquerda
    (*fctLinha)(0 + mH, 225 + mV, 420 + mH, 225 + mV); // reta superior
    (*fctLinha)(420 + mH, 0 + mV, 420 + mH, 225 + mV); // reta direita
    (*fctLinha)(0+ mH, 0 + mV, 420+ mH, 0 + mV);  // reta inferior

    (*fctLinha)(210 + mH, 0 + mV, 210 + mH, 225 + mV);  // reta do meio
    (*fctCircle)(210 + mH, 112 + mV, 27);  // círculo meio

    // LADO ESQUERDO

    (*fctLinha)(0 + mH, 67 + mV, 87+ mH, 85 + mV);  // diagonal inferior esquerda
    (*fctLinha)(0 + mH, 157 + mV, 87+ mH, 139 + mV);  // diagonal superior esquerda
    (*fctLinha)(87 + mH, 139 + mV, 87+ mH, 85 + mV);  // vertical pequena esquerda

    (*fctSemiCircle)(24 + mH, 112 + mV, 91, DIREITA);  // semi grande da esquerda

    (*fctLinha)(0+ mH, 21 + mV, 23+ mH, 21 + mV);  // reta pequena inferior esquerda
    (*fctLinha)(0+ mH, 203 + mV, 23+ mH, 203 + mV);  // reta pequena superior esquerda

    (*fctSemiCircle)(87+ mH, 112 + mV, 27, DIREITA);  // semi da esquerda

    (*fctLinha)(24 + mH, 125 + mV, 24 + mH, 100 + mV);  // cesta reta
    (*fctCircle)(28 + mH, 112 + mV, 4);  // círculo meio

    // LADO DIREITO

    (*fctLinha)(333+ mH, 85 + mV, 420+ mH, 67 + mV);  // diagonal inferior esquerda
    (*fctLinha)(333+ mH, 139 + mV, 420+ mH, 157 + mV);  // diagonal superior esquerda
    (*fctLinha)(333+ mH, 85 + mV, 333+ mH, 139 + mV);  // vertical pequena esquerda

    (*fctSemiCircle)(396+ mH, 112 + mV, 91, ESQUERDA);  // semi grande da direita

    (*fctLinha)(397+ mH, 21 + mV, 420+ mH, 21 + mV);  // reta pequena inferior esquerda
    (*fctLinha)(397+ mH, 203 + mV, 420+ mH, 203 + mV);  // reta pequena superior esquerda

    (*fctSemiCircle)(333+ mH, 112 + mV, 27, ESQUERDA);  // semi da esquerda

    (*fctLinha)(396 + mH, 125 + mV, 396 + mH, 100 + mV);  // cesta reta
    (*fctCircle)(392 + mH, 112 + mV, 4);  // círculo meio
    glFlush();
}

void drawBleachers(){
    for (int i = 0; i < countPonto - 1; i = i + 2){
        (*fctLinha)(pontos[i].x, pontos[i].y, pontos[i+1].x, pontos[i+1].y);
    }
}
