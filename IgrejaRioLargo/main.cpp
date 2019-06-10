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

#define CALICE 30

#define PISOI  31
#define PISOEN 32
#define PAREDEF 33

#define MADERIALTAR1 34
#define PISO2 35
#define PISO3 36
#define FERROGRADE 37
#define AR 38
#define JESUS 39


// Camera
GLdouble phi = M_PI / 2, theta = 0, radius = 85;

GLfloat fAspect;

double inc = 5 * M_PI / 180;

int style = 0;    // Wireframe or solid

GLdouble doorAngle = 0;     // Angulo da porta
bool openingDoor = false;    // flag para abrir a porta

// Quantidade de textura
GLuint texture_handle[50];

GLuint texture_id[50];

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
void drawDoor(){
    glPushMatrix();
    glRotatef(doorAngle, 0, 1, 0);
    glTranslatef(-1.5, 0, 0);
    glScalef(3, 3, 0.10);
    drawRect(0,1,0,2,3,1, 0.8, 0.52, 0.25);
    glPopMatrix();
}

//parede direita
void paredeD(){

}

// Janelas
void drawWindown(){


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);

    drawRect(-2.5, 17.8, 19.7, 2.6, 7.0, 1.3 ,116/255, 185/255, 255/255); //janela esquerda torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-2.5, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-3.9, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-1.2, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-2.5, 17.8, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-2.5, 21.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-2.5, 19.5, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-2.5, 14.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-2.5, 16.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);


    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect(2.5, 17.8, 19.7, 2.6, 7.0, 1.3 ,116/255, 185/255, 255/255); // janela direita torre
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(2.5, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(3.9, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(1.2, 17.8, 19.7, 0.3, 7.0, 1.5 ,1.0,  1.0,  1.0);
    drawRect(2.5, 17.8, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(2.5, 21.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(2.5, 19.5, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(2.5, 14.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);
    drawRect(2.5, 16.2, 19.7, 2.6, 0.3, 1.5 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D, texture_handle[VIDRO]);
    drawRect(-6.3, 17.7, 19.40, 2.6, 6.5, 1 ,116/255, 185/255, 255/255); //janela esquerda profundidade 2
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-6.3, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-7.6, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-5.0, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-6.3, 17.7, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-6.3, 20.8, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-6.3, 14.5, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-6.3, 16.0, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(-6.3, 19.2, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( 6.3, 17.7, 19.40, 2.6, 6.5, 1 ,116/255, 185/255, 255/255); // janela direita profundidade 2
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(6.3, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(7.6, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(5.0, 17.7, 19.7, 0.2, 6.5, 1.5 ,1.0,  1.0,  1.0);
    drawRect(6.3, 17.7, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(6.3, 20.8, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(6.3, 14.5, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(6.3, 16.0, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);
    drawRect(6.3, 19.2, 19.7, 2.6, 0.2, 1.5 ,1.0,  1.0,  1.0);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( -7, 7.80, 19.40, 2.6, 6.5, 1,116/255, 185/255, 255/255);//janela esquerda profundidade 3
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect( -7, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( -8.3, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( -5.6, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( -7, 7.80, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( -7, 4.5, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( -7, 11, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( -7, 9.5, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( -7, 6.3, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( 7, 7.80, 19.40, 2.6, 6.5, 1 ,116/255, 185/255, 255/255); // janela direita profundidade 3
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect( 7, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( 8.3, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( 5.6, 7.80, 19.40, 0.2, 6.5, 1.5,1, 1, 1);
    drawRect( 7, 7.80, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( 7, 4.5, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( 7, 11, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( 7, 9.5, 19.40, 2.6, 0.2, 1.5,1, 1, 1);
    drawRect( 7, 6.3, 19.40, 2.6, 0.2, 1.5,1, 1, 1);

    // Janelas lateral esquerda
    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( -10.90, 17.80, 15, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-10.90, 17.80, 15, 1.5, 7,   0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 16.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 13.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 15, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(-10.90, 16.00, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 14.20, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 21.30, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 19.60, 15, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( -10.90, 17.80, 9, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-10.90, 17.80, 9, 1.5, 7,   0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 10.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 7.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 9, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(-10.90, 16.00, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 14.20, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 21.30, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 19.60, 9, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( -10.90, 17.80, 3, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-10.90, 17.80, 3, 1.5, 7,   0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 4.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 1.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, 3, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(-10.90, 16.00, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 14.20, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 21.30, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 19.60, 3, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( -10.90, 17.80, -3, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(-10.90, 17.80, -3, 1.5, 7,   0.2,1, 1, 1);
    drawRect(-10.90, 17.80, -1.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, -4.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(-10.90, 17.80, -3, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(-10.90, 16.00, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 14.20, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 21.30, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(-10.90, 19.60, -3, 1.8, 0.2, 2.7,1, 1, 1);

    // Janelas lateral direita
    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect( 10.90, 17.80, 15, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(10.90, 17.80, 15, 1.5, 7,   0.2,1, 1, 1);
    drawRect(10.90, 17.80, 16.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 13.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 15, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(10.90, 16.00, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 14.20, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 21.30, 15, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 19.60, 15, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect(10.90, 17.80, 9, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(10.90, 17.80, 9, 1.5, 7,   0.2,1, 1, 1);
    drawRect(10.90, 17.80, 10.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 7.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 9, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(10.90, 16.00, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 14.20, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 21.30, 9, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 19.60, 9, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect(10.90, 17.80, 3, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(10.90, 17.80, 3, 1.5, 7,   0.2,1, 1, 1);
    drawRect(10.90, 17.80, 4.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 1.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, 3, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(10.90, 16.00, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 14.20, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 21.30, 3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 19.60, 3, 1.8, 0.2, 2.7,1, 1, 1);

    glBindTexture(GL_TEXTURE_2D,texture_handle[VIDRO]);
    drawRect(10.90, 17.80, -3, 1, 7 , 2.6 ,116/255, 185/255, 255/255);
    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(10.90, 17.80, -3, 1.5, 7,   0.2,1, 1, 1);
    drawRect(10.90, 17.80, -1.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, -4.5, 1.5, 7, 0.2,1, 1, 1);
    drawRect(10.90, 17.80, -3, 1.8, 0.2, 2.5,1, 1, 1);
    drawRect(10.90, 16.00, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 14.20, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 21.30, -3, 1.8, 0.2, 2.7,1, 1, 1);
    drawRect(10.90, 19.60, -3, 1.8, 0.2, 2.7,1, 1, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

//grade
void drawGrid(){

    glBindTexture(GL_TEXTURE_2D, texture_handle[FERROGRADE]);

    drawRect(-20.9, -1.3, 20, 0.3, 0.3, 38, 1 ,0.98 ,0.98);
    drawRect(-20.9, -0.3, 20, 0.3, 0.3, 38, 1 ,0.98 ,0.98);

    drawRect(-20.9, -1.0, 38 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 37 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 36 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 35 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 34 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 33 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 32 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 31 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 30 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 29 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 28 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 27 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 26 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 25 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 24 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 23 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 22 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 21 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 20 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 19 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 18 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 17 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 16 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 15 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 14 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 13 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 12 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 11 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 10 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 9 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 8 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 7 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 6 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 5 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 4 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 3 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 2 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, 1 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);




    drawRect(-20.9, -1.3, -20, 0.3, 0.3, 38, 1 ,0.98 ,0.98);
    drawRect(-20.9, -0.3, -20, 0.3, 0.3, 38, 1 ,0.98 ,0.98);

    drawRect(-20.9, -1.0, -38 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -37 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -36 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -35 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -34 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -33 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -32 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -31 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -30 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -29 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -28 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -27 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -26 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -25 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -24 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -23 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -22 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -21 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -20 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -19 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -18 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -17 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -16 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -15 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -14 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -13 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -12 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -11 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -10 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -9 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -8 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -7 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -6 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -5 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -4 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -3 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -2 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -1 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);


    drawRect(-20.9, -1.0, -39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);


    //glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(20.9, -1.3, 20, 0.3, 0.3, 40, 1 ,0.98 ,0.98);
    drawRect(20.9, -0.3, 20, 0.3, 0.3, 40, 1 ,0.98 ,0.98);

    drawRect(20.9, -1.0, 38 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 37 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 36 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 35 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 34 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 33 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 32 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 31 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 30 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 29 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 28 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 27 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 26 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 25 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 24 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 23 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 22 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 21 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 20 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 19 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 18 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 17 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 16 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 15 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 14 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 13 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 12 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 11 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 10 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 9 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 8 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 7 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 6 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 5 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 4 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 3 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 2 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, 1 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);


    drawRect(20.9, -1.0, 0.0, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);


    drawRect(20.9, -1.3, -20, 0.3, 0.3, 40, 1 ,0.98 ,0.98);
    drawRect(20.9, -0.3, -20, 0.3, 0.3, 40, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -38 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -37 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -36 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -35 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -34 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -33 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -32 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -31 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -30 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -29 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -28 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -27 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -26 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -25 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -24 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -23 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -22 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -21 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -20 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -19 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -18 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -17 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -16 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -15 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -14 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -13 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -12 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -11 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -10 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -9 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -8 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -7 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -6 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -5 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -4 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -3 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -2 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -1 , 0.3, 3.0, 0.3, 1 ,0.98 ,0.98);

    //grade frente esquerda
    drawRect(-12.5, -1.3, 40.0, 16.0, 0.3, 0.3, 1 ,0.98 ,0.98);
    drawRect(-12.5, 0.0, 40.0, 16.0, 0.3, 0.3, 1 ,0.98 ,0.98);

    drawRect(-6.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-7.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-8.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-9.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-10.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-11.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-12.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-12.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-13.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-14.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-15.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-16.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-17.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-18.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(-19.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);

    //grade frente direito
    drawRect(12.5, -1.3, 40.0, 16.0, 0.3, 0.3, 1 ,0.98 ,0.98);
    drawRect(12.5, 0.0, 40.0, 16.0, 0.3, 0.3, 1 ,0.98 ,0.98);

    drawRect(6.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(7.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(8.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(9.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(10.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(11.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(12.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(12.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(13.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(14.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(15.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(16.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(17.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(18.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);
    drawRect(19.5, -1.0, 40, 0.1, 3.0, 0.3, 1 ,0.98 ,0.98);



}

void drawAltar(){

    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);



}

void drawQuadr(){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA1]);
    drawRect(-10.50, 9.00, 11.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA2]);
    drawRect(-10.50, 9.00, 8.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA3]);
    drawRect(-10.50, 9.00, 5.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA4]);
    drawRect(-10.50, 9.00, 2.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA5]);
    drawRect(-10.50, 9.00, -1.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA6]);
    drawRect(-10.50, 9.00, -4.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA7]);
    drawRect(-10.50, 9.00, -7.0, 0.3, 3, 2 ,1, 1, 1);


    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA1]);
    drawRect(10.50, 9.00, 11.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA2]);
    drawRect(10.50, 9.00, 8.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA3]);
    drawRect(10.50, 9.00, 5.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA4]);
    drawRect(10.50, 9.00, 2.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA5]);
    drawRect(10.50, 9.00, -1.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA6]);
    drawRect(10.50, 9.00, -4.0, 0.3, 3, 2 ,1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture_handle[VIA7]);
    drawRect(10.50, 9.00, -7.0, 0.3, 3, 2 ,1, 1, 1);


    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO2]);
    drawRect(0, 0, 0, 22, 0.3, 40,1,1,1); // piso igreja
    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO3]);
    drawRect(0, -6.3, 0, 42, 0.3, 80,1,1,1); // piso três 3
}

void drawObj(){


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[TAPETE]);
    drawRect(0, 0.15, 2, 5.0, 0.3, 22, 0.86,0.07,0.23); //tapete

    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]); // cruz torre
    drawRect(0, 38, 19.75, 0.5, 4, 0.3, 1, 1, 1);
    drawRect(0, 39, 19.75, 3 , 0.3, 0.3, 1, 1, 1);


    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]); // cruz torre
    drawRect(0, 20.5, 20, 0.6, 10, 0.5 ,1,  1,  1); // cruz torre
    drawRect(0, 24, 20, 4, 0.5, 0.5 ,1,  1,  1); // cruz torre






    /*banco*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-6, 3, 0 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(-6, 5.0, 1.0 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(-4.0, 4.0, 1.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(-8.0, 4.0, 1.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(-3.5, 1.8, 0, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(-3.5, 0.5, 0, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(-8.5, 1.8, 0, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-8.5, 0.5, 0, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    // banco 2

    drawRect(-6, 3, 5 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(-6, 5.0, 6.0 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(-4.0, 4.0, 6.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(-8.0, 4.0, 6.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(-3.5, 1.8, 5, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(-3.5, 0.5, 5, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(-8.5, 1.8, 5, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-8.5, 0.5, 5, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    // banco 3

    drawRect(-6, 3, 10 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(-6, 5.0, 11 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(-4.0, 4.0, 11.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(-8.0, 4.0, 11.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(-3.5, 1.8, 10, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(-3.5, 0.5, 10, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(-8.5, 1.8, 10, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(-8.5, 0.5, 10, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);



    /*banco*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(6, 3, 0 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(6, 5.0, 1.0 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(4.0, 4.0, 1.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(8.0, 4.0, 1.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(3.5, 1.8, 0, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(3.5, 0.5, 0, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(8.5, 1.8, 0, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(8.5, 0.5, 0, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    // banco 2

    drawRect(6, 3, 5 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(6, 5.0, 6.0 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(4.0, 4.0, 6.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(8.0, 4.0, 6.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(3.5, 1.8, 5, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(3.5, 0.5, 5, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(8.5, 1.8, 5, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(8.5, 0.5, 5, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    // banco 3

    drawRect(6, 3, 10 , 6, 0.5 , 2.5, 0.55, 0.34, 0.26); // acento banco
    drawRect(6, 5.0, 11 ,6, 2.0 , 0.3, 0.55, 0.34, 0.26); // encosto banco

    drawRect(4.0, 4.0, 11.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco
    drawRect(8.0, 4.0, 11.0, 0.5, 1.5, 0.3, 0.59, 0.29, 0); // aste esconto banco

    drawRect(3.5, 1.8, 10, 0.5, 2.5, 2.0, 0.59, 0.29, 0); // pe banco direito
    drawRect(3.5, 0.5, 10, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);

    drawRect(8.5, 1.8, 10, 0.5, 2.5, 2.0, 0.59, 0.29, 0);// pe banco esquerdo
    drawRect(8.5, 0.5, 10, 0.5, 1.0, 2.5, 0.55, 0.34, 0.26);



}

void drawSino(){
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-2.7, 30, 19.7, 1, 4, 1 ,1,  1, 1);
    drawRect(2.7, 30, 19.7, 1, 4, 1 ,1,  1, 1);
    drawRect(0, 32, 19.7, 6.5, 0.3, 1 ,1,  1, 1);
    drawRect(0, 28, 19.7, 6.5, 0.3, 1 ,1,  1, 1);

    glBindTexture(GL_TEXTURE_2D, texture_handle[SINO]);
    // glDisable(GL_BLEND);
    drawRect(0, 30, 20, 5, 4, 0.3 ,1,  1, 1); //sino
    drawRect(0, 30, 19.7, 5, 4, 0.3 ,1,  1, 1);

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
    drawAltar();
    drawObj();
    drawSino();
    drawGrid();
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);
    drawRect(0, -3.15, 0, 22, 6.0, 40,1,1,1); // piso dois 2

    // escada entrada
    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
    drawRect(0, -6.0, 25, 10, 1.0, 10.0,1,1,1);
    drawRect(0, -5.0, 24, 10, 1.0, 8.0,1,1,1);
    drawRect(0, -4.0, 23, 10, 1.0, 6.0,1,1,1);
    drawRect(0, -3.0, 22, 10, 1.0, 4.0,1,1,1);
    drawRect(0, -2.0, 21, 10, 1.0, 2.0,1,1,1);

    glBindTexture(GL_TEXTURE_2D, texture_handle[TETO]);
    drawRect(0, 22.35, -0.9, 22, 0.3, 40, 0.69,0.69,0.69);// Teto

    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(0, 11.00, -19.85, 22, 22.20, 0.3, 1, 1, 0);//Parede fundo
    drawRect(-10.90, 11.00, -0.60, 0.3, 22.20, 39.35 ,1, 1, 0);//parede esquerda lateral 1
    // COMENTAR====================================================================
    drawRect(10.90, 11.00, -0.60, 0.3, 22.20, 39.35 ,1, 1, 0);//parede esquerda lateral 1

    // mureta
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-20.9, -4.3, 0, 0.3, 4.0, 80.5, 1, 1, 0);// muro lateral esquerdo

    drawRect(-20.9, -1.0, 39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-20.9, 0.5, 39.5, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);

    drawRect(-20.9, 0.8, 39.5, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);
    drawRect(-20.9, 0.5, 0, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);

    drawRect(-20.9, 0.8, 0, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);
    drawRect(-20.9, -1.0, -39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(-20.9, 0.5, -39.5, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);


    drawRect(20.9, -4.3, 0, 0.3, 4.0, 80.5, 1, 1, 0);// muro lateral direito
    drawRect(20.9, -1.0, 39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(20.9, 0.5, 39.5, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);
    drawRect(20.9, 0.8, 39.5, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);

    drawRect(20.9, -1.0, 0.0, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(20.9, 0.5, 0, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);
    drawRect(20.9, 0.8, 0, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);

    drawRect(20.9, -1.0, -39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(20.9, -1.0, -39.5, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);
    drawRect(20.9, 0.5, -39.5, 0.8, 0.3, 1.8, 0.96, 0.77, 0.19);

    drawRect(-20.9, -1.0, 0.0, 0.3, 3.0, 1.0, 1 ,0.98 ,0.98);

    drawRect(-12.5, -4.3, 40.0, 16.0, 4.0, 0.3, 1, 1, 0);// muro frente esquerda
    drawRect(-5.0, -1.0, 40, 1.0, 3.0, 1, 1 ,0.98 ,0.98);
    drawRect(-5, 0.5, 40, 1.8, 0.3, 1.6, 0.96, 0.77, 0.19);
    drawRect(-5, 0.8, 40, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);

    drawRect(-20.0, -1.0, 40, 1.0, 3.0, 1, 1 ,0.98 ,0.98);

    drawRect(12.5, -4.3, 40.0, 16.0, 4.0, 1, 1, 1, 0);// muro frente direito
    drawRect(5.0, -1.0, 40, 1.0, 3.0, 1, 1 ,0.98 ,0.98);

    drawRect(5, 0.5, 40, 1.8, 0.3, 1.6, 0.96, 0.77, 0.19);
    drawRect(5, 0.8, 40, 0.5, 0.3, 0.7, 1 ,0.98 ,0.98);

    drawRect(20.0, -1.0, 40, 1.0, 3.0, 1, 1 ,0.98 ,0.98);

    drawRect(0, -4.3, -40.0, 42, 4.0, 0.3, 1, 1, 0);// muro trass


    // ar-condicionado
    glBindTexture(GL_TEXTURE_2D, texture_handle[AR]);
    drawRect(-8.90, 12.50, -1, 0.5, 2, 4.0 ,1, 1, 1);
    drawRect(8.90, 12.50, -1, 0.5, 2, 4.0 ,1, 1, 1);


    /*--------------------------------ALTAR--------------------------------------------------------------------*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-9.20, 11.0, -10.0, 2.70, 22.20, 0.3,1 ,1, 0.88); //parede altar esquerda
    drawRect(-7.5, 8.5, -10.0, 1.0, 16.5,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(9.20, 11.0, -10.0, 2.70, 22.20, 0.3,1 ,1, 0.88); //parede altar direita
    drawRect(7.5, 8.5, -10.0, 1.0, 16.5,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(0, 19.60, -10.0, 16.60, 5.20, 0.3, 1 ,1, 0.88);   //parede altar cima

    drawRect(0, 16.50, -10.0, 15.5, 1.0, 0.3,  0.85, 0.43, 0.57); //coluna cima rosa

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);
    drawRect(0, 0.5, -15.0, 22.0, 0.60, 9.75, 0.96, 0.96, 0.96); // chão altar

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREPRETO]);
    drawRect(0, 6, -15.0, 6, 0.30, 4, 0.28, 0.24, 0.55); // Mesa altar tampo
    drawRect(0, 3.0, -15.0, 5.5, 6.0, 3.5, 0.28, 0.24, 0.55); // Mesa altar base

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
    drawRect(-2.5, 3.0, -13.0, 0.25, 6.0, 0.3, 1, 1, 1); // Mesa altar coluna esquerda
    drawRect(2.5, 3.0, -13.0, 0.25, 6.0, 0.3, 1, 1, 1); // Mesa altar coluna direita

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]); // pedestal
    drawRect(-4.0, 3.0, -7.5, 2.5, 6.0 , 1.0, 0.96, 0.64, 0.38); // base coluna
    drawRect(-4.0, 5.3, -7.5, 3.0, 0.3 , 1.3, 0.96, 0.87, 0.7); // tampo borda


    glBindTexture(GL_TEXTURE_2D, texture_handle[MADERIALTAR1]); // move cruz altar meio
    drawRect(0, 10.60, -19.70, 6, 19.40, 0.3, 0.96, 0.64, 0.38);

    drawRect(-4, 5.30, -19.70, 2, 9.0, 0.3, 0.96, 0.64, 0.38);
    drawTriangle(-5, 9.7, -3, 9.7, -4, 12 ,-19.5);
    drawRect(4, 5.30, -19.70, 2, 9.0, 0.3, 0.96, 0.64, 0.38);
    drawTriangle(5, 9.7, 3, 9.7, 4, 12 ,-19.5);

    drawRect(-9.70, 10.60, -19.0, 2, 19.40, 1.0, 0.96, 0.64, 0.38); // coluna quina altar esquerda
    drawRect(9.70, 10.60, -19.0, 2, 19.40, 1.0, 0.96, 0.64, 0.38);  // coluna quina altar direita

    glBindTexture(GL_TEXTURE_2D, texture_handle[JESUS]); // cruz altar
    drawRect(0, 11.60, -19.50, 5, 8, 0.3,  0.96, 0.64, 0.38);



    /*--------------------------------parede entrada--------------------------------------------------------------------*/
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(-10.0, 6.0, 13.70, 1.5, 12.0, 0.3,1 ,1, 0.88); //parede entrada esquerda 1
    drawRect(-9.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(-5.0, 6.0, 13.70, 1.0, 12.0, 0.3,1 ,1, 0.88); //parede entrada esquerda 2
    drawRect(-6.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(-4.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(4.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(10.0, 6.0, 13.70, 1.5, 12.0, 0.3,1 ,1, 0.88); //parede entada direita 1
    drawRect(9.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(6.0, 6.0, 13.70, 1.0, 12.0,0.3,  0.85, 0.43, 0.57); // coluna rosa
    drawRect(5.0, 6.0, 13.70, 1.00, 12.0, 0.3,1 ,1, 0.88); //parede entada direita 1
    drawRect(0, 13.0, 13.70, 22.0, 2.0, 0.3, 1 ,1, 0.88);   //parede entrada cima

    glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
    drawRect(0, 14, 16.3, 22.0, 0.3, 5.5 ,1,1,1); //teto mezanino entrada cima

    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
    drawRect(0, 16.5, 14.0 , 11.0, 0.5, 0.3 ,0.86 ,0.86, 0.86);  //grade mezanino centro

    drawRect(-1.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(-2.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(-3.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(-4.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(-5.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(0.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(1.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(2.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(3.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(4.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);
    drawRect(5.0, 15.20 , 14.0 , 0.3, 2.5 ,0.3 , 0.86 ,0.86, 0.86);

    glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
    drawRect(-8.5, 14.0, 8.0 , 5.0, 0.3 ,14 , 1, 1, 1); // teto esquerdo mezanino
    drawRect(8.5, 14.0, 8.0 , 5.0, 0.3 ,14.0 , 1, 1, 1); // teto direito mezanino

    glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);

    drawRect(-6.0, 16.5 , 7.5 , 0.5, 0.3 ,13.5 , 1, 1, 1); // grade cima mezanino esquerdo
    drawRect(-8.5, 16.5, 1.0 ,5.0 , 0.3 ,0.5 , 1, 1, 1);  // grade lateral esquerda mezanino

    drawRect(6.0, 16.5 , 7.5 , 0.5, 0.3 ,13.5 , 1, 1, 1); // grade cima mezanino direito
    drawRect(8.5, 16.5, 1.0 ,5.0 , 0.3 ,0.5 , 1, 1, 1);  // grade lateral direito mezanino

    drawRect(-8.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(-9.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(-10.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(-7.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(-6.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);

    drawRect(-6.0 ,15.20 , 6.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 5.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 4.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 3.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 2.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 1.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 7.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 8.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 9.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 10.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 11.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 12.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(-6.0 ,15.20 , 13.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);


    drawRect(8.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(9.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(10.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(7.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);
    drawRect(6.5 ,15.20 , 1.0 , 0.3, 2.5 ,0.3 , 1, 1, 1);

    drawRect(6.0 ,15.20 , 6.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 5.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 4.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 3.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 2.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 1.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 7.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 8.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 9.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 10.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 11.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 12.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);
    drawRect(6.0 ,15.20 , 13.5 , 0.3, 2.5 ,0.3 ,0.86 ,0.86, 0.86);

    /*--------------------------------fachada--------------------------------------------------------------------*/
    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);

    drawRect(-4.0, 5.0, 19.85, 2, 10.0, 0.3, 1, 0.84, 0 );//parede fachada porta esquerda
    drawRect(4.0, 5.0, 19.85, 2, 10.0, 0.3, 1, 0.84, 0); //parede fachada porta direita
    drawRect(0, 10.5, 19.85, 10, 3, 0.3,1,  0.84,  0);//parede fachada em  cima da parta centro

    drawRect(0, 12.15, 19.85, 9.50, 0.5, 0.3 ,1, 1,  1);//parede fachada bloco acima da porta 1
    drawRect(0, 12.6, 19.85, 9.0, 0.5, 0.3 ,1, 0.98, 0.98);//parede fachada bloco acima da porta 2

    drawRect(0, 22.85, 19.85, 8.75, 20.0, 0.3 ,1,  0.84,  0); //parede fachada torre meio

    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(0, 33.0, 19.85, 8.50, 0.5, 0.3 ,1,  1,  1); //parede fachada bloco  acima da torre
    drawTriangle(0, 36.0, -4, 33.15, 4, 33.15,19.75); // TRIANGULO

    glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDEF]);
    drawRect(7, 6.5, 19.40, 4, 13.0, 0.6, 1, 1, 0); // parede fachada bloco direito profundidade 2
    drawRect(-7.0, 6.5, 19.40, 4, 13.0, 0.6 , 1, 1, 0);// parede fachada bloco esquerdo profundidade 2

    drawRect(0, 13.30, 19.40, 18.50, 0.50, 0.3, 1, 1, 1);// parede fachada bloco a acima profundidade 2
    drawRect(0, 13.80, 19.40, 18.0, 0.50, 0.3, 1, 0.98, 0.98);// parede fachada bloco a acima profundidade 2

    drawRect(0, 18.20, 19.40, 17.50, 8.40, 0.3, 1, 1, 0);// parede fachada bloco cima profundidade 2 acima 2

    drawRect(0, 22.60, 19.40, 17.0, 0.5, 0.3, 1, 1, 1);// bloco fachada  profundidade 2 acima 2
    drawRect(0, 23.0, 19.40, 16.50, 0.5, 0.3, 1, 1, 1);// bloco fachada  profundidade 2 acima 3

    drawRect(0, 24.0, 19.40, 16.0, 1.5, 0.3, 1, 1, 0); // bloco fachada  profundidade 2 acima 4

    drawRect(0, 25.0, 19.40, 15.5, 0.5, 0.3, 1, 1, 1); // bloco fachada  profundidade 2 acima 4
    drawRect(0, 25.3, 19.40, 15.0, 0.5, 0.3, 1, 1, 1);

    drawRect(-9.60, 10.80, 19.25, 2.7, 21.70, 0.3, 1, 1, 0);// parede fachada bloco direito profundidade 3
    drawRect(9.60, 10.80, 19.25, 2.7, 21.70, 0.3, 1, 1, 0); // parede fachada bloco esquerdo profundidade 3

    drawRect(0, 22.0, 19.55, 22.00, 1.0, 0.3, 1, 1, 1);// parede fachada bloco esquerdo profundidade 4

    /*Porta*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[PORTA]);
    glPushMatrix();
    glTranslatef(1.5, 1.5, 19.85);
    drawDoor();

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

    glShadeModel(GL_SMOOTH);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
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

    glGenTextures(40, texture_handle);



    loadTexture(texture_handle[0], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/piso.jpg");
    loadTexture(texture_handle[1], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wood.jpg");
    loadTexture(texture_handle[2], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/telha02.jpg");
    loadTexture(texture_handle[3], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wall.jpg");
    loadTexture(texture_handle[4], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmorealtar.jpg");
    loadTexture(texture_handle[5], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmoremesa.jpg");
    loadTexture(texture_handle[6], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmorebranco.png");
    loadTexture(texture_handle[7], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeirabanco.jpg");
    loadTexture(texture_handle[8], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/metal.jpg");
    loadTexture(texture_handle[9], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeiraporta.jpg");
    loadTexture(texture_handle[10], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/tapete.png");
    loadTexture(texture_handle[11], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/p.jpg");
    loadTexture(texture_handle[12], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/solo.jpg");
    loadTexture(texture_handle[13], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/sinoo.png");
    loadTexture(texture_handle[14], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/vidroJ.jpg");
    loadTexture(texture_handle[15], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/chao.jpg");

    loadTexture(texture_handle[16], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via1.jpg");
    loadTexture(texture_handle[17], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via2.jpg");
    loadTexture(texture_handle[18], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via3.jpg");
    loadTexture(texture_handle[19], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via4.jpg");
    loadTexture(texture_handle[20], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via5.jpg");
    loadTexture(texture_handle[21], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via6.jpg");
    loadTexture(texture_handle[22], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via7.jpg");

    loadTexture(texture_handle[23], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via8.jpg");
    loadTexture(texture_handle[24], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via9.jpg");
    loadTexture(texture_handle[25], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via10.jpg");
    loadTexture(texture_handle[26], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via11.jpg");
    loadTexture(texture_handle[27], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via12.jpg");
    loadTexture(texture_handle[28], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via13.jpg");
    loadTexture(texture_handle[29], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/via14.jpg");
    loadTexture(texture_handle[30], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/calice.jpg");

    loadTexture(texture_handle[31], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/pisoIgraja.jpg");
    loadTexture(texture_handle[32], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/pisoentrada.jpg");
    loadTexture(texture_handle[33], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/parede.jpg");
    loadTexture(texture_handle[34], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeiraAltar1.jpg");
    loadTexture(texture_handle[35], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/piso2.png");
    loadTexture(texture_handle[36], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/piso3.png");
    loadTexture(texture_handle[37], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/ferrograde.jpg");
    loadTexture(texture_handle[38], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/ar.png");
    loadTexture(texture_handle[39], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/jesus.png");
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

// Programa Principal

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

