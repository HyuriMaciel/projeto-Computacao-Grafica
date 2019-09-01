#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include <QOpenGLTexture>
#include<stdlib.h>
#include <fstream>

#define WIRE 0
#define FILL 1

#define PISO 0
#define CRUZ 1
#define TETO 2
#define PAREDE 3


#define MARMOREALTAR 4
#define MARMOREPRETO 5
#define MARMOREBRANCO 6
#define MADEIRABANCO 7
#define METAL 8
#define MADEIRAPORTA 9
#define TAPETE 10
#define PORTA 11
#define SOLO 12
#define SINO 13
#define VIDRO 14
#define CHAO 15

#define VIA1 16
#define VIA2 17
#define VIA3 18
#define VIA4 19
#define VIA5 20
#define VIA6 21
#define VIA7 22
#define VIA8 23
#define VIA9 24
#define VIA10 25
#define VIA11 26
#define VIA12 27
#define VIA13 28
#define VIA14 29
#define PORTA1 30
#define PISOI  31
#define PISOEN 32
#define PAREDEF 33
#define MADERIALTAR1 34
#define PISO2 35
#define PISO3 36
#define FERROGRADE 37
#define PORTA2 38
#define JESUS 39
#define PORTAO1 40
#define PORTAO2 41

#define SENHORA 42
#define CALICE 43

// Camera
GLdouble phi = M_PI / 2, theta = 0, radius = 450;

GLfloat fAspect;

double inc = 5 * M_PI / 180;

int style = 0;

GLdouble doorAngle = 0;     // Angulo da porta
bool openingDoor = false;    // flag para abrir a porta

// Quantidade de textura
GLuint texture_handle[80];

GLuint texture_id[80];

// Carrega as texturas
void loadTexture(GLuint texture, const char* filename)
{
    sf::Image img;
    img.loadFromFile(filename);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA,
                img.getSize().x, img.getSize().y,
                0,
                GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()
                );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// converte escala RGB
void rgb(float r, float g, float b){
    glColor3f(r/255, g/255, b/255);
}

// desenha um tringulo
void drawTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat z) {
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1,y1,z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x2,y2,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x3,y3,z);
    glEnd();
}

// Desenha um bloco
void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat c1, GLfloat c2, GLfloat c3) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(c1, c2, c3);
    glRotatef(180, 1.0, 0.0, 0.0);
    //glutSolidCube(1);
    glBegin(GL_QUADS);
    // Frente
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    // Trás
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    // Direita
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    // Esquerda
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    // Cima
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    // Baixo
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glPopMatrix();
}

// Desenha porta
void drawDoor(GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat c1, GLfloat c2, GLfloat c3, GLint ang){

    if(ang == 1){
        glPushMatrix();
        glRotatef(doorAngle, 0, 1, 0);
        glTranslatef(-1.5, 0, 0);
        glScalef(3, 3, 0.10);
        drawRect(x,y,z,sx,sy,sz, c1, c2, c3);
        glPopMatrix();

    }
    else{
        glPushMatrix();
        glRotatef(-doorAngle, 0, 1, 0);
        glTranslatef(-1.5, 0, 0);
        glScalef(3, 3, 0.10);
        drawRect(x,y,z,sx,sy,sz, c1, c2, c3);
        glPopMatrix();

    }

}

// Janelas
void drawWindown(){


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-12, 75, 151.5, 15, 35, 2.5 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-4.0, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(-20.0, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(-12, 93.0, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-12, 57.0, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(-12, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(-12, 75, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-12, (75+7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-12, (75-7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(12, 75, 151.5, 15, 35, 2.5 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(4.0, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(20.0, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(12, 93.0, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(12, 57.0, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(12, 75, 151.5, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(12, 75, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(12, (75+7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(12, (75-7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);


    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-45, 75, 151.2, 15, 35, 2.5 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-37, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(-53, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(-45, 93.0, 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-45, 57.0, 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(-45, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(-45, 75, 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-45, (75+7.5), 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-45, (75-7.5), 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(45, 75, 151.2, 15, 35, 2.5 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(37, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect(53, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(45, 93.0, 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(45, 57.0, 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(45, 75, 151.2, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(45, 75, 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(45, (75+7.5), 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(45, (75-7.5), 151.2, 16, 1, 3 ,1.0,  1.0,  1.0);


    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-85, 25, 151, 15, 35, 2.5 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect((-85 -8), 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect((-85+8), 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(-85, (25+18), 151, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-85, (25-18), 151, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(-85, 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(-85, 25, 151, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-85, (25+7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(-85, (25-7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(85, 25, 151, 15, 35, 2.5 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect((85 -8), 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);
    drawRect((85+8), 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(85, (25+18), 151, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(85, (25-18), 151, 16, 1, 3 ,1.0,  1.0,  1.0);

    drawRect(85, 25, 151, 1, 36, 3 ,1.0,  1.0,  1.0);

    drawRect(85, 25, 151, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(85, (25+7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);
    drawRect(85, (25-7.5), 151.5, 16, 1, 3 ,1.0,  1.0,  1.0);


    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-99.85, 75, 50, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-99.85, 75, (50 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  (50+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18), 50, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18), 50, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(-99.85, 75, 50, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75, 50, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+7.5), 50, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-7.5), 50, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-99.85, 75, 80, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-99.85, 75, (80 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  (80+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18), 80, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18),80, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(-99.85, 75, 80, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75, 80, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+7.5), 80, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-7.5), 80, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-99.85, 75, 20, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-99.85, 75, ( 20 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  (20+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18),  20, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18), 20, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(-99.85, 75, 20, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  20, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+7.5), 20, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-7.5),  20, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-99.85, 75, -10, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-99.85, 75, (  -10 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  (  -10+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18),   -10, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18),  -10, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(-99.85, 75,   -10, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,   -10, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+7.5),   -10, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-7.5),  -10, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-99.85, 75, -40, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-99.85, 75, (-40 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,  (-40+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18),-40, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18),-40, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(-99.85, 75,-40, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, 75,-40, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+7.5),-40, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-7.5),-40, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(99.85, 75, 50, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(99.85, 75, (50 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  (50+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+18), 50, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-18), 50, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(99.85, 75, 50, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75, 50, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+7.5), 50, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-7.5), 50, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(99.85, 75, 80, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(99.85, 75, (80 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  (80+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+18), 80, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-18),80, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(99.85, 75, 80, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75, 80, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+7.5), 80, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-7.5), 80, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(99.85, 75, 20, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(99.85, 75, ( 20 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  (20+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(-99.85, (75+18),  20, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(-99.85, (75-18), 20, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(99.85, 75, 20, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  20, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+7.5), 20, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-7.5),  20, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(99.85, 75, -10, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(99.85, 75, (  -10 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  (  -10+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+18),   -10, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-18),  -10, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(99.85, 75,   -10, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,   -10, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+7.5),   -10, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-7.5),  -10, 2, 1, 16,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(99.85, 75, -40, 1, 35, 15 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(99.85, 75, (-40 - 8), 1, 35, 2 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,  (-40+8), 1, 35, 2 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+18),-40, 1, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-18),-40, 1, 1, 16 ,1.0,  1.0,  1.0);

    drawRect(99.85, 75,-40, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, 75,-40, 2, 36, 1 ,1.0,  1.0,  1.0);

    drawRect(99.85, (75+7.5),-40, 2, 1, 16 ,1.0,  1.0,  1.0);
    drawRect(99.85, (75-7.5),-40, 2, 1, 16,1.0,  1.0,  1.0);




    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

//grade
void drawGrid(){

    glBindTexture(GL_TEXTURE_2D, texture_handle[FERROGRADE]);

    drawRect(-125, 10.0, -77, 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-125, 10.0, (-77+38.5), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-125, 10.0, (-77 - 38.5), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);

    drawRect(-125, 10.0, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(-125, 7, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(-125, 13, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);

    drawRect(-125, 10.0,( 96.5 + 18 ), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-125, 10.0, (96.5 - 30), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-125, 10.0, (96.5 +48.25+18.25), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);

    drawRect(-125, 10.0,106, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(-125, 7, 106, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(-125, 13, 106, 0.8, 0.5, 171, 1 ,0.98 ,0.98);

    drawRect(125, 10.0, -77, 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(125, 10.0, (-77+38.5), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(125, 10.0, (-77 - 38.5), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);

    drawRect(125, 10.0, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(125, 7, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(125, 13, -67, 0.8, 0.5, 171, 1 ,0.98 ,0.98);

    drawRect(125, 10.0,( 96.5 + 18 ), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(125, 10.0, (96.5 - 30), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(125, 10.0, (96.5 +48.25+18.25), 0.3, 10.0, 1.0, 1 ,0.98 ,0.98);

    drawRect(125, 10.0,106, 0.8, 0.5, 171, 1 ,0.98 ,0.98);
    drawRect(125, 7, 106, 0.8, 1, 171, 1 ,0.98 ,0.98);
    drawRect(125, 13, 106, 0.8, 1, 171, 1 ,0.98 ,0.98);


    drawRect(-75, 10, 195, 1, 10.0, 1, 1 ,0.98 ,0.98);
    drawRect(-75, 10, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);
    drawRect(-75, 7, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);
    drawRect(-75, 13, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);

    drawRect(75, 10, 195, 1, 10.0, 1, 1 ,0.98 ,0.98);
    drawRect(75, 10, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);
    drawRect(75, 7, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);
    drawRect(75, 13, 195, 98, 0.8, 0.8, 1 ,0.98 ,0.98);



}

void drawQuadr(){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA1]);
    drawRect(-99.65, 30, 50, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA2]);
    drawRect(-99.65, 30, 30, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA3]);
    drawRect(-99.65, 30, 10, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA4]);
    drawRect(-99.65, 30, -10, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA5]);
    drawRect(-99.65, 30, -30, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA6]);
    drawRect(-99.65, 30,-50, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA7]);
    drawRect(-99.65, 30,-70, 0.2,15,10 ,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA8]);
    drawRect(99.65, 30, 50, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA9]);
   drawRect(99.65, 30, 30, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA10]);
     drawRect(99.65, 30, 10, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA11]);
   drawRect(99.65, 30, -10, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA12]);
    drawRect(99.65, 30, -30, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA13]);
     drawRect(99.65, 30,-50, 0.2,15,10 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA14]);
     drawRect(99.65, 30,-70, 0.2,15,10 ,1, 1, 1);


//    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO2]);
//    drawRect(0, 0, 0, 22, 0.3, 40,1,1,1); // piso igreja
//    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO3]);
//    drawRect(0, -6.3, 0, 42, 0.3, 80,1,1,1); // piso três 3
}

void drawObj(){


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[TAPETE]);
    drawRect(0, 0.5, 50, 30, 0.3, 190, 0.86,0.07,0.23); //tapete

    /*banco*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, 0 , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, 3.5 ,60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, 4, 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, 4, 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, 0, 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, 0, 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, 0, 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, 0, 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 2
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0+20) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5+20),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4+20), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4+20), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0+20), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0+20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0+20), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0+20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 3

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0+40) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5+40),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4+40), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4+40), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0+40), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0+40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0+40), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0+40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 4

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0+60) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5+60),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4+60), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4+60), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0+60), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0+60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0+60), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0+60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 7
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0+80) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5+80),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4+80), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4+80), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0+80), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0+80), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0+80), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0+80), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);


    // banco 5
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0-20) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5-20),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4-20), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4-20), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0-20), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0-20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0-20), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0-20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 6
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0-40) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5-40),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4-40), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4-40), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0-40), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0-40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0-40), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0-40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);
    // banco 7
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(60, 6, (0-60) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(60, 12, (3.5-60),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((60 + 28), 10, (4-60), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((60 - 28), 10, (4-60), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(89, 4, (0-60), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(89, 1, (0-60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(31, 4, (0-60), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(31, 1, (0-60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);



    /*banco*/


    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, 0 , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, 3.5 ,60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, 4, 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, 4, 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, 0, 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, 0, 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, 0, 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, 0, 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 2
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0+20) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5+20),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4+20), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4+20), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0+20), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0+20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0+20), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0+20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 3

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0+40) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5+40),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4+40), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4+40), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0+40), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0+40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0+40), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0+40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 4

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0+60) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5+60),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4+60), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4+60), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0+60), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0+60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0+60), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0+60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 7
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0+80) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5+80),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4+80), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4+80), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0+80), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0+80), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0+80), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0+80), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);


    // banco 5
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0-20) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5-20),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4-20), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4-20), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0-20), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0-20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0-20), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0-20), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    // banco 6
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0-40) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5-40),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4-40), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4-40), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0-40), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0-40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0-40), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0-40), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);
    // banco 7
    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-60, 6, (0-60) , 60, 0.5 , 9, 0.55, 0.34, 0.26); // acento banco
    drawRect(-60, 12, (3.5-60),60, 4.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect((-60 + 28), 10, (4-60), 3, 8, 1, 0.59, 0.29, 0); // aste esconto banco
    drawRect((-60 - 28), 10, (4-60), 3, 8, 1, 0.59, 0.29, 0);  // aste esconto banco

    drawRect(-89, 4, (0-60), 1.5, 5, 7, 0.59, 0.29, 0); // pe banco direito
    drawRect(-89, 1, (0-60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);

    drawRect(-31, 4, (0-60), 1.5, 6, 7, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-31, 1, (0-60), 1.5, 1.0, 8.5, 0.55, 0.34, 0.26);


}

void drawSino(){

//    drawRect(0, 90, 151.8, 2, 50, 1 ,1,  1,  1); //cruz torre
//    drawRect(0, 105, 151.8, 20, 2, 1 ,1,  1,  1);


    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-12, 135, 151.25, 2, 20, 2 ,1,  1, 1);
    drawRect(12, 135, 151.25, 2, 20, 2 ,1,  1, 1);
    drawRect(0, (135 - 10), 151.25, 25, 1, 1 ,1,  1, 1);
    drawRect(0,(135 + 10), 151.25, 25, 1, 1 ,1,  1, 1);

    glBindTexture(GL_TEXTURE_2D, texture_handle[SINO]);
    // glDisable(GL_BLEND);
    drawRect(0, 135, 151.65, 25, 20, 0.3 ,1,  1, 1); //sino
     drawRect(0, 135, 151, 25, 20, 0.3 ,1,  1, 1);

}

void drawAltarMove(){


    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREPRETO]);
    drawRect(0, 20, -100, 30, 0.5, 15, 0.28, 0.24, 0.55); // Mesa altar tampo
    drawRect(0, 10, -100, 25, 20, 14, 0.28, 0.24, 0.55); // Mesa altar base

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
    drawRect(-10, 10, -92, 1, 19.5, 1, 1, 1, 1); // Mesa altar coluna esquerda
    drawRect(10, 10, -92, 1, 19.5, 1, 1, 1, 1); // Mesa altar coluna direita

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]); // pedestal
    drawRect(-48, 10, -80, 8, 20 , 4, 0.96, 0.64, 0.38); // base coluna
    drawRect(-48, 19, -80, 9, 0.5 , 4.5, 0.96, 0.87, 0.7); // tampo borda


    glBindTexture(GL_TEXTURE_2D, texture_handle[MADERIALTAR1]); // move cruz altar meio
    drawRect(0, 50, -148, 50, 100, 2, 0.96, 0.64, 0.38);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[JESUS]); // cruz altar
    drawRect(0, 60, -146.8, 25,40, 0.5,  0.96, 0.64, 0.38);
// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//     //drawRect(-80.0, 50.0, -90.0, 39.85, 100, 0.3,1 ,1, 0.88); //parede altar esquerda
 glBindTexture(GL_TEXTURE_2D, texture_handle[SENHORA]); // cruz altar
  drawRect(-80, 50, -89.0, 30, 20,  0.3, 1 ,1, 0.88);

  //glBindTexture(GL_TEXTURE_2D, texture_handle[CALICE]); // cruz altar
 //  drawRect(0, 23, -100, 2, 4, 0.2, 0.2 ,1, 0.88);
}

// Função callback chamada para gerenciar eventos do mouse
void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            openingDoor = !openingDoor;
    glutPostRedisplay();
}

void drawCylinder(GLfloat x, GLfloat y, GLfloat z, GLdouble radius, GLdouble height) {
    GLUquadricObj *obj = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glScalef(radius, radius, height);

    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricTexture(obj, true);
    gluCylinder(obj, 1, 1, 1, 6, 2);
    glPopMatrix();
}

// Função callback chamada para fazer o desenho
void desenha(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawWindown();
    drawQuadr();
    drawObj();
    drawGrid();
    drawAltarMove();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
    drawRect(0, 0.3, 0, 200,0.5, 300,2,1,1); // piso dois 1


    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO2]);
    drawRect(0, -3.15, 0, 200, 6.0, 300,1,1,1); // piso dois 2

    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO3]);
    drawRect(0, -5.5, 20, 250, 0.5, 350,1,1,2); // piso dois 3

    // escada entrada
    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
    drawRect(0, -6.0, 155, 50, 1.0, 25.0,1,2,2);
    drawRect(0, -5.0, 155, 50, 1.0, 21.0,1,2,2);
    drawRect(0, -4.0, 155, 50, 1.0, 17.0,1,2,2);
    drawRect(0, -3.0, 155, 50, 1.0, 13.0,1,2,2);
    drawRect(0, -2.0, 155, 50, 1.0, 8.0,1,2,2);

    glBindTexture(GL_TEXTURE_2D, texture_handle[TETO]);
     drawRect(0, 100, 0, 200,0.5, 300,0.69,0.69,0.69);
   // drawRect(0, 100, -0.9, 22, 0.3, 40, 0.69,0.69,0.69);// Teto
    drawSino();
    //paredes
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(0, 50.00, -149.85, 200, 100, 0.3, 1, 1, 0);//Parede fundo
    drawRect(-99.85, 50.00, -0.60, 0.3, 100, 300 ,1, 1, 0);//parede esquerda lateral 1
    drawRect(99.85, 50.00, -0.60, 0.3, 100, 300 ,1, 1, 0);//parede direita lateral 1
    drawRect(0.0, 0.0, -155, 250, 10.0, 0.3, 1, 1, 0);// muro trass

    // mureta
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-125, 0.0, 20.0, 0.3, 10.0, 350, 1, 1, 0);// muro lateral esquerdo
    drawRect(125, 0.0, 20.0, 0.3, 10.0, 350, 1, 1, 0);// muro lateral esquerdo
    drawRect(-75, 0.0, 195, 100, 10.0, 0.3, 1, 1, 0);// muro frente esquerda
    drawRect(75, 0.0, 195, 100, 10.0, 0.3, 1, 1, 0);// muro frente direto

    drawRect(-125, 10.0, 20.0, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra meio
    drawRect(-125, 15.5, 20.0, 1.0, 1.0, 3.0, 0.96, 0.77, 0.19);
    drawRect(-125, 10.0, -154, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra fundo
    drawRect(-125, 15.5, -154, 1.0, 1.0, 3.0,0.96, 0.77, 0.19);
    drawRect(-125, 10.0, 193, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra frente
    drawRect(-125, 15.5, 193, 1.0, 1.0, 3.0, 0.96, 0.77, 0.19);


    drawRect(125, 10.0, 20.0, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra meio
    drawRect(125, 15.5, 20.0, 1.0, 1.0, 3.0, 0.96, 0.77, 0.19);
    drawRect(125, 10.0, -154, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra fundo
    drawRect(125, 15.5, -154, 1.0, 1.0, 3.0,0.96, 0.77, 0.19);
    drawRect(125, 10.0, 193, 0.3, 10.0, 2.0, 1 ,0.98 ,0.98); //pilastra frente
    drawRect(125, 15.5, 193, 1.0, 1.0, 3.0, 0.96, 0.77, 0.19);


    drawRect(-124, 10.0, 195, 2.0, 10.0, 0.3, 1 ,0.98 ,0.98); // pilastra esquerda
    drawRect(-124, 15.5, 195, 3.0, 1.0, 0.3, 0.96, 0.77, 0.19);
    drawRect(-26, 10.0, 195, 2.0, 10.0, 0.3, 1 ,0.98 ,0.98); // pilastra direita
    drawRect(-26, 15.5, 195, 3.0, 1.0, 0.3, 0.96, 0.77, 0.19);


    drawRect(124, 10.0, 195, 2.0, 10.0, 0.3, 1 ,0.98 ,0.98); // pilastra esquerda
    drawRect(124, 15.5, 195, 3.0, 1.0, 0.3, 0.96, 0.77, 0.19);
    drawRect(26, 10.0, 195, 2.0, 10.0, 0.3, 1 ,0.98 ,0.98); // pilastra direita
    drawRect(26, 15.5, 195, 3.0, 1.0, 0.3, 0.96, 0.77, 0.19);




    // ar-condicionado
   // glBindTexture(GL_TEXTURE_2D, texture_handle[AR]);
  //  drawRect(-8.90, 12.50, -1, 0.5, 2, 4.0 ,1, 1, 1);
    //drawRect(8.90, 12.50, -1, 0.5, 2, 4.0 ,1, 1, 1);


 /*--------------------------------ALTAR--------------------------------------------------------------------*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-80.0, 50.0, -90.0, 39.85, 100, 0.3,1 ,1, 0.88); //parede altar esquerda
    drawRect(-55, 40, -90.0, 10.0, 80,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(-51.0, 50.0, -100.0, 0.30, 100, 17.0,1 ,1, 0.88); // parede lateral esquerda
    drawRect(65.0, 50.0, -90.0, 10, 100, 0.3,1 ,1, 0.88); //parede altar direita
    drawRect(92.0, 50.0, -90.0, 15, 100, 0.3,1 ,1, 0.88);
   drawRect(80, 70.0, -90.0, 30,60 , 0.3, 1 ,1, 0.88);
   drawRect(55, 40, -90.0, 10.0, 80, 0.3,  0.85, 0.43, 0.57); // coluna rosa
   drawRect(50.0, 50.0, -120.0, 0.30, 100, 60.0,1 ,1, 0.88); // parede lateral direita

    drawRect(0, 90.0, -90.0, 120, 20, 0.3, 1 ,1, 0.88);   //parede altar cima
    drawRect(0, 75, -90.0, 100, 10.0, 0.3,  0.85, 0.43, 0.57); //coluna cima rosa

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);
    drawRect(0, 1.0, -120.0, 199.85, 2.0, 60.0, 0.96, 0.96, 0.96); // chão altar

    /*parede entrada*/
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-90.0, 50.0, 100, 20, 100, 0.3,1 ,1, 0.88); //parede entrada esquerda 1
    drawRect(-75.0, 50.0, 100, 10, 100,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(90.0, 50.0, 100, 20, 100, 0.3,1 ,1, 0.88); //parede entrada esquerda 1
    drawRect(75.0, 50.0, 100, 10, 100,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(0.0, 90.0, 100, 140, 20,0.3,  1 ,1, 0.88); //
    drawRect(0.0, 80.0, 100, 140, 5,0.3,  0.85, 0.43, 0.57); // coluna rosa
    /*MEZANINO*/
    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
    drawRect(0, 50, 125, 199.7, 0.3, 50.0 ,1,1,1); //teto mezanino entrada cima
    drawRect(0, 50, 80 , 140, 0.3, 40 ,1,1,1);
    drawRect(-84, 50, 50 , 30, 0.3, 100 ,1,0,0);// teto esquerdo
    drawRect(84, 50, 50 , 30, 0.3, 100 ,1,0,0);// teto direito


    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(84, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(98, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);

    drawRect(84, 53.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(84, 56.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(84, 59.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(84, 61.85 ,0.75 ,30, 0.5 ,0.5, 0.86 ,0.86, 0.86);

    drawRect(-84, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-98, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);

    drawRect(-84, 53.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(-84, 56.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(-84, 59.0 ,0.75 , 30, 0.5 ,0.5 , 0.86 ,0.86, 0.86);
    drawRect(-84, 61.85 ,0.75 ,30, 0.5 ,0.5, 0.86 ,0.86, 0.86);

    drawRect(-69, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-69, 56.0 ,25 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-69, 56.0 ,45.0 , 1.0, 12.0 ,1 , 0.86 ,0.86, 0.86);

    drawRect(-69, 53.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(-69, 56.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(-69, 59.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(-69, 61.85 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);

    drawRect(69, 56.0 ,0.75 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(69, 56.0 ,25 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-69, 56.0   ,45.0 , 1.0, 12.0 ,1 , 0.86 ,0.86, 0.86);

    drawRect(69, 53.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(69, 56.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(69, 59.0 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);
    drawRect(69, 61.85 ,29.5 , 0.5, 0.5 ,56 , 0.86 ,0.86, 0.86);


    drawRect(0.0, 56.0 ,59.0 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(69, 56.0 ,59.0 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-69, 56.0 ,59.0 , 1.0, 12.0 ,1.0 , 0.86 ,0.86, 0.86);
    drawRect(-34.5, 56.0 ,59.0 , 1.0, 12.0 ,2.0 , 0.86 ,0.86, 0.86);
    drawRect(34.5, 56.0 ,59.0 , 1.0, 12.0 ,2.0 , 0.86 ,0.86, 0.86);

    drawRect(0.0, 53.0 ,59.0 , 139.5, 0.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(0.0, 56.0 ,59.0 , 139.5, 0.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(0.0, 59.0 ,59.0 , 139.5, 0.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(0.0, 61.85 ,59.0 , 139.5, 0.5 ,0.3 , 0.86 ,0.86, 0.86);


    /*fachada*/
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);

    drawRect(-30.0, 25, 151.25, 10, 50.0, 0.5, 1, 0.84, 0 );//parede fachada porta esquerda
    drawRect(30.0, 25, 151.25, 10, 50.0, 0.5, 1, 0.84, 0 );//parede fachada porta direta

    drawRect(0, 40, 151.25, 50, 20, 0.3,1,  0.84,  0);//parede fachada em  cima da parta centro

    drawRect(0, 50, 151.25, 70, 2.0, 0.3 ,1, 1,  1);//parede fachada bloco acima da porta 1
    drawRect(0, 52, 151.25, 50, 2.0, 0.3 ,1, 1, 1);//parede fachada bloco acima da porta 2


     drawRect(0, 100, 151.25, 50, 96.0, 0.3 ,1,  0.84,  0); // torre meio
     glBindTexture(GL_TEXTURE_2D, texture_handle[PISO2]);
     drawRect(0, 90, 151.8, 2, 50, 1 ,1,  1,  1); //cruz torre
     drawRect(0, 105, 151.8, 20, 2, 1 ,1,  1,  1);

    drawRect(0, 149,151.25, 54, 2, 0.3 ,1,  1,  1); //parede fachada bloco  acima da torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO2]);
    drawTriangle(0, 172, -27, 150, 27, 150,151.25); // TRIANGULO

    drawRect(0, 180, 151.25, 2, 15, 1 ,1,  1,  1); //cruz triangulo
    drawRect(0, 184, 151.25, 10, 2, 1 ,1,  1,  1);

     glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);

    drawRect(-45.0, 50.0, 151, 40, 100, 0.6, 1, 1, 0); // parede fachada bloco direito profundidade 2
    drawRect(45.0, 50.0, 151, 40, 100, 0.6, 1, 1, 0);// parede fachada bloco esquerdo profundidade 2

    drawRect(0, 101, 151, 135, 2, 0.3, 1, 1, 1);// bloco 1 profundidade 2
    drawRect(0, 103, 151, 130, 2, 0.3, 1, 1, 1);// bloco 2 profundidade 2

    drawRect(-65, 50, 150.50, 70, 100, 0.5, 1, 0.84, 0);// parede profundidade 3
    drawRect(65, 50, 150.50, 70, 100, 0.5, 1, 0.84, 0); // parede profundidade 3

    /*Porta*/


    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, texture_handle[PORTA1]);
    glTranslatef(-26, 0, 151.25);
    drawDoor(5,5.1,0,9,9.5,0.5, 2,2,2,1);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_handle[PORTA2]);
    glPushMatrix();
    glTranslatef(30, 0, 151.25);
    drawDoor(-5,5.1,0,8,9.5,0.5, 2,2,2,2);
    glPopMatrix();

    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, texture_handle[ PORTAO1]);
    glTranslatef(-26, 0, 195);
    drawDoor(5, 3, 0,8.5,9,0.5, 2,2,2,1);
    glPopMatrix();

    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, texture_handle[ PORTAO2]);
    glTranslatef(29, 0, 195);
    drawDoor(-5, 3, 0,8.5,9,0.5, 2,2,2,2);
    glPopMatrix();



    glutSwapBuffers();

}

void visao(void) {
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(radius*sin(theta)*sin(phi),radius*cos(phi),radius*cos(theta)*sin(phi), 0, 0, 0, 0, 1, 0);
}

// Função usada para especificar o volume de visualização
void visualizacaoParams(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, fAspect, 0.5, 500);
    visao();
}

void reshapeFunc(GLsizei w, GLsizei h) {
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat) w / (GLfloat) h;
    visualizacaoParams();
}

// Callback para gerenciar eventos do teclado para teclas especiais (F1, PgDn, entre outras)
void specialFunc(int key, int x, int y) {
    glLoadIdentity();

    switch (key) {
    case GLUT_KEY_LEFT :
        theta += inc;
        break;
    case GLUT_KEY_RIGHT :
        theta -= inc;
        break;
    case GLUT_KEY_UP :
        if(phi + inc <= M_PI) phi += inc;
        break;
    case GLUT_KEY_DOWN :
        if(phi - inc >= 0) phi -= inc;
        break;
    case GLUT_KEY_PAGE_UP :
        if(radius - 1 > 2) radius -= 1;
        break;
    case GLUT_KEY_PAGE_DOWN :
        radius += 1;
        break;
    case GLUT_KEY_F1 :
        if(style == WIRE) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            style = FILL;
        } else if(style == FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            style = WIRE;
        }
        break;
    }

    phi = phi - ((int) (phi / (2 * M_PI)));
    gluLookAt(radius * sin(theta) * sin(phi), radius * cos(phi), radius * cos(theta) * sin(phi), 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
}

static void timer(int value){
    if (openingDoor){
        if (doorAngle < 90)
            doorAngle += 5;
    } else if (doorAngle > 0)
        doorAngle -= 5;

    glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}

void inicializa (void) {

    GLfloat luzAmbiente[4] = {0.3, 0.3, 0.3, 1.0};
    GLfloat luzDifusa[4]={0.4, 0.4, 0.4, 1.0};
    GLfloat posicaoLuz[4]={40, 20.0, 30.0, 1.0};
    // sombreamento  dos objetos
    glShadeModel(GL_SMOOTH);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define a posição e as componentes de cor da fonte de luz GL_LIGHT0.
    //os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering


    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(80, texture_handle);

    loadTexture(texture_handle[0], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/pisoprincipal.png");
    loadTexture(texture_handle[1], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wood.jpg");
    loadTexture(texture_handle[2], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/telha02.jpg");
    loadTexture(texture_handle[3], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wall.jpg");
    loadTexture(texture_handle[4], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/pisoaltar.png");
    loadTexture(texture_handle[5], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/marmoremesa.jpg");
    loadTexture(texture_handle[6], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/marmorebranco.png");
    loadTexture(texture_handle[7], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/madeirabanco.png");
    loadTexture(texture_handle[8], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/metal.jpg");
    loadTexture(texture_handle[9], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeiraporta.jpg");
    loadTexture(texture_handle[10], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/tapete.png");
    loadTexture(texture_handle[11], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/p.jpg");
    loadTexture(texture_handle[12], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/solo.jpg");
    loadTexture(texture_handle[13], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/sinoo.png");
    loadTexture(texture_handle[14], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/vidroJ.jpg");
    loadTexture(texture_handle[15], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/chao.jpg");
    loadTexture(texture_handle[16], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via1.jpg");
    loadTexture(texture_handle[17], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via2.jpg");
    loadTexture(texture_handle[18], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via3.jpg");
    loadTexture(texture_handle[19], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via4.jpg");
    loadTexture(texture_handle[20], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via5.jpg");
    loadTexture(texture_handle[21], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via6.jpg");
    loadTexture(texture_handle[22], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via7.jpg");
    loadTexture(texture_handle[23], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via8.jpg");
    loadTexture(texture_handle[24], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via9.jpg");
    loadTexture(texture_handle[25], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via10.jpg");
    loadTexture(texture_handle[26], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via11.jpg");
    loadTexture(texture_handle[27], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via12.jpg");
    loadTexture(texture_handle[28], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via13.jpg");
    loadTexture(texture_handle[29], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/via14.jpg");
    loadTexture(texture_handle[30], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/porta3.jpg");
    loadTexture(texture_handle[31], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/pisoIgraja.jpg");
    loadTexture(texture_handle[32], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/pisoentrada.jpg");
    loadTexture(texture_handle[33], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/paredemudo.png");
    loadTexture(texture_handle[34], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/madeiraAltar1.jpg");
    loadTexture(texture_handle[35], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/concreto.png");
    loadTexture(texture_handle[36], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/piso3.png");
    loadTexture(texture_handle[37], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/ferrograde.jpg");
    loadTexture(texture_handle[38], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/porta1.jpg");
    loadTexture(texture_handle[39], "/home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/jesus.png");
    loadTexture(texture_handle[40], "//home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/portao1.png");
     loadTexture(texture_handle[41], "//home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/portao2.png");
     loadTexture(texture_handle[42], "//home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/santaceia.jpg");
      loadTexture(texture_handle[43], "//home/hyuri/Área de Trabalho/projetoCG-master/IgrejaRioLargo/img/calice.png");



    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(350,300);
    glutCreateWindow("Igreja Matriz Rio Largo");
    glutDisplayFunc(desenha);
    glutReshapeFunc(reshapeFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);
    inicializa();
    timer(0);
    glutMainLoop();
}

