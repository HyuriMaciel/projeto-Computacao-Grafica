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


// Camera
GLdouble phi = M_PI / 2, theta = 0, radius = 15;

GLfloat fAspect;

double inc = 5 * M_PI / 180;

int style = 0;    // Wireframe or solid

GLdouble doorAngle = 0;     // Door angle
bool openingDoor = false;    // Door opening flag

// Quantidade de textura
GLuint texture_handle[10];

GLuint texture_id[25];

//void loadTexture(GLuint texture, const char* filename)
//{
//    sf::Image img;

//    img.loadFromFile(filename);

//   glBindTexture(GL_TEXTURE_2D, texture);

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());



//}

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


void rgb(float r, float g, float b){
  //glColor3f(r/255, g/255, b/255);
}

void drawTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat z) {
  glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1,y1,z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x2,y2,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x3,y3,z);
  glEnd();
}

void drawTriangle_fan(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3,
                      GLfloat x4, GLfloat y4, GLfloat x5, GLfloat y5, GLfloat x6, GLfloat y6,
                       GLfloat x7, GLfloat y7, GLfloat x8, GLfloat y8) {
    glBegin(GL_TRIANGLE_FAN);
            glVertex2f( x1, y1); // primeiro ponto, comum a todos
            //glVertex2f(-4,-5);
            //glVertex2f(-6,-3);
            glVertex2f( x2, y2);
            glVertex2f( x3, y3);
            glVertex2f( x4, y4);
            glVertex2f( x5, y5);
            glVertex2f( x6, y6);
            glVertex2f( y8, y7);
            //glVertex2f( 6,-3);
            //glVertex2f( 4,-5);
        glEnd();
}

void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat c1, GLfloat c2, GLfloat c3) {
  glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(c1, c2, c3);
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



void drawDoor(){
  glPushMatrix();
    glRotatef(doorAngle, 0, 1, 0);
    glTranslatef(-1.5, 0, 0);
    glScalef(3, 3, 0.10);
    drawRect(0,0,0,1,1,1, 0.8, 0.52, 0.25);
  glPopMatrix();
}

// Função callback chamada para gerenciar eventos do mouse
void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN)
          openingDoor = !openingDoor;
    glutPostRedisplay();
}

// Função callback chamada para fazer o desenho
void desenha(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*---------------------Piso---------------------------------------*/

  glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
  drawRect(0, 0, 0, 11, 0.3, 24,1,1,1);

/*---------------------Teto---------------------------------------*/

  glBindTexture(GL_TEXTURE_2D, texture_handle[TETO]);
  drawRect(0, 11.35, -0.9, 11, 0.3, 24,0.69,0.69,0.69);
  glBindTexture(GL_TEXTURE_2D, texture_handle[PAREDE]);
  drawRect(0, 11.20, -0.9, 11, 0.3, 24,0.74,0.74,0.74);

/*---------------------Parede fundo---------------------------------------*/

 glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
  drawRect(0, 5.60, -11.85, 11, 11.20, 0.3, 1 ,0.98 ,0.98);

/*---------------------parede altar frente-------------------------*/
//parede altar 1
 glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(-4.2, 4, -7.85, 2, 8, 0.3,1 ,1, 0.88);

//parede altar 2
 glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(4.2,4, -7.85, 2, 8, 0.3,1 ,1, 0.88);

//parede altar 3
 glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(0, 9.60, -7.85, 10.7, 3.20, 0.3,1 ,1, 0.88);

 /*---------------------parede altar fundo-------------------------*/
  glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);
  drawRect(0, 4.60, -11.2, 3.8, 9.20, 0.3, 0.96, 0.64, 0.38);

/*--------------------------cruz altar------------------------------*/
   glBindTexture(GL_TEXTURE_2D, texture_handle[CRUZ]);
   drawRect(0, 6.0, -10.8,0.4, 4, 0.3, 0.42, 0.56, 0.14);
   drawRect(0, 7.0, -10.8, 2.5, 0.4, 0.3, 0.42, 0.56, 0.14);

/*-----------------------chão altar 1---------------------*/
   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);
   drawRect(0, 0.5, -9.85, 10.7, 0.60, 4.18,0.96, 0.96, 0.96);

/*-----------------------altar---------------------------*/

   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREPRETO]);
   drawRect(0, 3, -9.5, 3, 0.30, 2,0.28, 0.24, 0.55);

   drawRect(0, 1.8, -9.5, 2.5, 2.3, 1.5, 0.28, 0.24, 0.55);
   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(-1.25, 1.8, -9, 0.2, 2.3, 0.3, 1, 1, 1);
   drawRect(1.25, 1.8, -9, 0.2, 2.3, 0.3, 1, 1, 1);

  /*pedestal*/

   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREALTAR]);

   drawRect(-2.5, 1.3, -5.5, 2, 2.7 , 0.7, 0.96, 0.64, 0.38);

   drawRect(-2.5, 2.5, -5.5, 2.5, 0.2 , 1,0.96, 0.87, 0.7);

/*parede entrada 1*/

   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);

   drawRect(4.7, 3, 9, 1, 6, 0.3,1,1,1);
   drawRect(-4.7, 3, 9, 1, 6, 0.3,1,1,1);

   drawRect(3.2, 7, 9, 4, 2, 0.3,1,1,1);
   drawRect(-3.2, 7, 9, 4, 2, 0.3,1,1,1);

   drawRect(2.0, 4, 9, 1, 8, 0.3,1,1,1);
   drawRect(-2.0, 4, 9, 1, 8, 0.3,1,1,1);

   drawRect(0, 7.5, 9, 3, 1, 0.3,1,1,1);

   //teto
   glBindTexture(GL_TEXTURE_2D, texture_handle[PISO]);
   drawRect(0, 8, 10 , 10.7, 0.3, 2.15 ,1,1,1);

   //grade
   glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
   drawRect(0, 9, 8.95 , 7.40, 0.2, 0.2 ,0.86 ,0.86, 0.86);

   drawRect(3.4, 8.5 , 8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(2.4, 8.5 ,8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(1.4, 8.5 , 8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(0.4, 8.5 , 8.95 , 0.2, 0.85 ,0.2 ,0.86 ,0.86, 0.86);
   drawRect(-0.4, 8.5 ,8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(-1.4, 8.5 , 8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(-2.4, 8.5 ,8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);
   drawRect(-3.4, 8.5 , 8.95 , 0.2, 0.85 ,0.2 , 0.86 ,0.86, 0.86);

/*parede  esquerda lateral 1*/
   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(-5.35, 5.60, -0.60, 0.3, 11.20, 22.80 ,0.96, 0.77, 0.19);

/*parede  direita lateral 2*/

   drawRect(5.35, 5.60, -0.60, 0.3, 11.20, 22.80, 0.96, 0.77, 0.19);

//parede fachada 1 esquerda
   drawRect(-2, 2, 11.85, 1, 4, 0.3, 1, 0.84, 0 );

//parede fachada 1 direita
   drawRect(2, 2, 11.85, 1, 4, 0.3, 1, 0.84, 0);

//parede fachada 1 centro
   drawRect(0, 3.5, 11.85, 3, 1, 0.3,1,  0.84,  0);

//parede fachada bloco acima da porta 1
   drawRect(0, 4.20, 11.85, 4.40, 0.40, 0.3 ,1, 1,  1);

//parede fachada bloco acima da porta 2
   drawRect(0, 4.60, 11.85, 3.80, 0.40, 0.3 ,1, 0.98, 0.98);

//parede fachada bloco acima da porta 3
   drawRect(0, 5.0, 11.85, 3.20, 0.40, 0.3, 1,  1,  1);

   //parede fachada bloco 1 torre
   drawRect(0, 9.20, 11.85, 2.60, 8.0, 0.3,1,  0.84,  0);

   //parede fachada bloco torre
   drawRect(0, 9.20, 11.85, 2.60, 8.0, 0.3 ,1, 0.98, 0.98);

   //parede fachada bloco  acima da torre
   //glBindTexture(GL_TEXTURE_2D, texture_handle[WALL]);
   drawRect(0, 13.40, 11.85, 3.20, 0.40, 0.3 ,1,  1,  1);

   // triangulo torre
   drawTriangle(-1.60, 13.60, 1.60, 13.60, 0, 14.30, 11.85);
   // cruz torre
   glBindTexture(GL_TEXTURE_2D, texture_handle[METAL]);
   drawRect(0, 15, 11.85, 0.30, 2, 0.3, 1, 1, 1);
   drawRect(0, 15.5, 11.85, 1, 0.3, 0.3, 1, 1, 1);

/*-----------------------------------------------------------------*/
   // parede fachada bloco direito profundidade 2
   glBindTexture(GL_TEXTURE_2D, texture_handle[MARMOREBRANCO]);
   drawRect(3.5, 2.40, 11.40, 2, 4.80, 0.6, 1, 1, 0);

   // parede fachada bloco esquerdo profundidade 2
   drawRect(-3.5, 2.40, 11.40, 2, 4.80, 0.6 , 1, 1, 0);

   // parede fachada bloco acima esquerdo profundidade 2
   drawRect(0, 5.0, 11.55, 8.40, 0.40, 0.3, 1, 1, 1);

   // parede fachada bloco acima esquerdo profundidade 2
   drawRect(0, 5.40, 11.55, 7.80, 0.40, 0.3, 1, 0.98, 0.98);

   // parede fachada bloco direito profundidade 2 acima 2
   drawRect(0, 7.40, 11.55, 7.20, 3.60, 0.3, 1, 1, 0);

   // bloco fachada  profundidade 2 acima 2
   drawRect(0, 9.70, 11.55, 6.40, 1.0, 0.3, 1, 1, 0);

   // bloco fachada  profundidade 2 acima 3
   drawRect(0, 10.70, 11.55, 5.80, 1.0, 0.3, 1, 1, 0);

   // bloco fachada  profundidade 2 acima 4
   drawRect(0, 11.70, 11.55, 5.20, 1.0, 0.3, 1, 1, 0);

   // bloco fachada  profundidade 2 acima 4
   drawRect(0, 12.70, 11.55, 4.60, 1.0, 0.3, 1, 1, 0);

/*------------------------------------------------------------*/

   // parede fachada bloco direito profundidade 3
   drawRect(0, 8.0, 11.25, 9, 6.40, 0.3, 1, 1, 0);

   // parede fachada bloco direito profundidade 4
   drawRect(5.0, 5.60, 10.95, 1.0, 11.20, 0.3, 1, 1, 0);

   // parede fachada bloco esquerdo profundidade 4
   drawRect(-5.0, 5.60, 10.95, 1.0, 11.20, 0.3, 1, 1, 0);

   /*banco*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[MADEIRABANCO]);
    drawRect(-3, 1, 0 , 4, 0.2 , 1.2, 0.55, 0.34, 0.26);

    drawRect(-3, 1.9, 0.3 , 4, 0.8 , 0.2, 0.55, 0.34, 0.26);

    drawRect(-4.8, 0.4, 0, 0.2, 1, 0.9, 0.59, 0.29, 0);
    drawRect(-1.2, 0.4, 0, 0.2, 1, 0.9, 0.59, 0.29, 0);

    drawRect(-1.2, 1, 0.3, 0.15, 1, 0.2, 0.59, 0.29, 0);
    drawRect(-4.8, 1, 0.3, 0.15, 1, 0.2, 0.59, 0.29, 0);


   /*mezanino*/



    drawRect(-4.5, 8, 1.57 , 1.85, 0.3 ,14.56 , 1, 1, 1);
    drawRect(4.5, 8, 1.57 , 1.85, 0.3 ,14.56 , 1, 1, 1);

    drawRect(3.8, 9 , 1.57 , 0.2, 0.2 ,14.56 , 1, 1, 1);

    drawRect(3.8,8.5 , 7.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 6.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 5.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 4.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 3.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 2.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 1.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , 0.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 ,-0.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , -1.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , -2.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , -3.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , -4.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(3.8,8.5 , -5.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);

    drawRect(4.8, 9, -5.6 , 1.85, 0.2 ,0.2 , 1, 1, 1);

    drawRect(5.26 ,8.5 , -5.6 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(4.34 ,8.5 , -5.6 , 0.2, 0.85 ,0.2 , 1, 1, 1);

    drawRect(-3.8, 9 , 1.57 , 0.2, 0.2 ,14.56 , 1, 1, 1);

    drawRect(-3.8,8.5 , 7.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 6.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 5.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 4.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 3.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 2.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 1.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , 0.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 ,-0.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , -1.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , -2.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , -3.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , -4.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-3.8,8.5 , -5.56 , 0.2, 0.85 ,0.2 , 1, 1, 1);

    drawRect(-4.8, 9, -5.6 , 1.85, 0.2 ,0.2 , 1, 1, 1);

    drawRect(-5.26 ,8.5 , -5.6 , 0.2, 0.85 ,0.2 , 1, 1, 1);
    drawRect(-4.34 ,8.5 , -5.6 , 0.2, 0.85 ,0.2 , 1, 1, 1);

    /*Porta*/

    glBindTexture(GL_TEXTURE_2D, texture_handle[CRUZ]);
    glPushMatrix();
    glTranslatef(1.5, 1.5, 11.85);
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
  GLfloat posicaoLuz[4]={0.0, 20.0, 30.0, 1.0};

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

  glGenTextures(20, texture_handle);



   loadTexture(texture_handle[0], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/piso.jpg");
    loadTexture(texture_handle[1], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wood.jpg");
    loadTexture(texture_handle[2], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/telha02.jpg");
    loadTexture(texture_handle[3], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/wall.jpg");
    loadTexture(texture_handle[4], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmorealtar.jpg");
    loadTexture(texture_handle[5], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmoremesa.jpg");
    loadTexture(texture_handle[6], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/marmorebranco.jpg");
    loadTexture(texture_handle[7], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeirabanco.jpg");
    loadTexture(texture_handle[8], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/metal.jpg");
    loadTexture(texture_handle[9], "/home/hyuri/git/projetoCG/IgrejaRioLargo/img/madeiraporta.jpg.jpg");


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

