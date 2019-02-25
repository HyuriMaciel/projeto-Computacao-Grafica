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


void drawPyramid(GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz) {
  glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glBegin(GL_TRIANGLES);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(0, 1, 0);
      glTexCoord2f(1.0f, 0.0f); glVertex3i(-1, -1, 1);
      glTexCoord2f(0.0f, 1.0f); glVertex3i(1, -1, 1);

      glTexCoord2f(0.0f, 0.0f); glVertex3i(0, 1, 0);
      glTexCoord2f(1.0f, 0.0f); glVertex3i(1, -1, 1);
      glTexCoord2f(0.0f, 1.0f); glVertex3i(1, -1, -1);

      glTexCoord2f(0.0f, 0.0f); glVertex3i(0, 1, 0);
      glTexCoord2f(1.0f, 0.0f); glVertex3i(1, -1, -1);
      glTexCoord2f(0.0f, 1.0f); glVertex3i(-1, -1, -1);

      glTexCoord2f(0.0f, 0.0f); glVertex3i(0, 1, 0);
      glTexCoord2f(1.0f, 0.0f); glVertex3i(-1, -1, -1);
      glTexCoord2f(0.0f, 1.0f); glVertex3i(-1, -1, 1);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(1.0f, 0.0f); glVertex3i(-1, -1, 1);
      glTexCoord2f(1.0f, 1.0f); glVertex3i(1, -1, 1);
      glTexCoord2f(0.0f, 1.0f); glVertex3i(1, -1, -1);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(-1, -1, -1);
    glEnd();
  glPopMatrix();
}

void drawPyramidLine(GLfloat x, GLfloat y, GLfloat z, int n, double spacing) {
  for (int i = 0; i < n / 2 + 1; i += 1){
    drawPyramid(x - i * spacing, y, z, 0.1, 0.5, 0.1);
    drawPyramid(x + i * spacing, y, z, 0.1, 0.5, 0.1);
  }
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

void drawCylinderWithCut(GLfloat x, GLfloat y, GLfloat z, GLdouble radius, GLdouble height, GLfloat cut) {
  GLUquadricObj *obj = gluNewQuadric();
  GLdouble eqn[4] = {0.0, 1.0, 0.0, cut};

  glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glScalef(radius, radius, height);

    glClipPlane (GL_CLIP_PLANE0, eqn);
    glEnable (GL_CLIP_PLANE0);

    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricTexture(obj, true);
    gluCylinder(obj, 1, 1, 1, 30, 2);

    glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}

void drawColumnLine(float x, float y, float z, int n, float spacing) {
  float start = spacing/2;
  float end = start + (n)/2 * spacing;

  for (float i = start; i < end; i+= spacing){
    drawCylinder(x - i * spacing, y, z, 0.2, 3);
    drawCylinder(x + i * spacing, y, z, 0.2, 3);
  }
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


    drawCylinderWithCut(0, 0, 0, 3, 0.3, 0.2);

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

