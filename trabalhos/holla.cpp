


#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


#define pi 3.1415
float h0 = 0;
float h1 = 0;
float h2 = 0;
float h3 = 0;
float h4 = 0;
float h5 = 0;
float h6 = 0;
float h7 = 0;
float h8 = 0;
float h9 = 0;
float h10 = 0;
float h11 = 0;
float h12 = 0;

float speed = 1.5;

int k=0;


void up(int value);

void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);


glPushMatrix();  
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2i(0, h0 + 0);
        glVertex2i(0, h0 + 20);
        glVertex2i(20, h0 + 20);
        glVertex2i(20, h0 + 0);
    glEnd();
glPopMatrix();
   
glPushMatrix();
    glBegin(GL_QUADS);
        glColor3f(2.0, 0.0, 1.0);
        glVertex2i(20, h1 + 0);
        glVertex2i(20, h1 + 20);
        glVertex2i(40, h1 + 20);
        glVertex2i(40, h1 + 0);
    glEnd();
glPopMatrix();

 glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(40, h2 + 0);
        glVertex2i(40, h2 + 20);
        glVertex2i(60, h2 + 20);
        glVertex2i(60, h2 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();    
    glBegin(GL_QUADS);
       glColor3f(1.0, 0.0, 0.0);
        glVertex2i(60, h3 + 0);
        glVertex2i(60, h3 + 20);
        glVertex2i(80, h3 + 20);
        glVertex2i(80, h3 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 1.0);
         glVertex2i(80, h4 + 0);
        glVertex2i(80,  h4 + 20);
        glVertex2i(100, h4 + 20);
        glVertex2i(100, h4 + 0);
    glEnd();
glPopMatrix();


glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2i(100, h5 + 0);
        glVertex2i(100, h5 + 20);
        glVertex2i(120, h5 + 20);
        glVertex2i(120, h5 + 0);
    glEnd();
glPopMatrix();
   
 glPushMatrix();
    glBegin(GL_QUADS);    
       glColor3f(2.0, 0.0, 1.0);
        glVertex2i(120, h6 + 0);
        glVertex2i(120, h6 + 20);
        glVertex2i(140, h6 + 20);
        glVertex2i(140, h6 + 0);
    glEnd();
glPopMatrix();

 glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(140, h7 + 0);
        glVertex2i(140, h7 + 20);
        glVertex2i(160, h7 + 20);
        glVertex2i(160, h7 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();    
    glBegin(GL_QUADS);
       glColor3f(1.0, 0.0, 0.0);
        glVertex2i(160, h8 + 0);
        glVertex2i(160, h8 + 20);
        glVertex2i(180, h8 + 20);
        glVertex2i(180, h8 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 1.0);
         glVertex2i(180, h9 + 0);
        glVertex2i(180, h9 + 20);
        glVertex2i(200, h9 + 20);
        glVertex2i(200, h9 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();  
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2i(200, h10 + 0);
        glVertex2i(200, h10 + 20);
        glVertex2i(220, h10 + 20);
        glVertex2i(220, h10 + 0);
    glEnd();
glPopMatrix();

   
glPushMatrix();
    glBegin(GL_QUADS);
        glColor3f(2.0, 0.0, 1.0);
        glVertex2i(220, h11 + 0);
        glVertex2i(220, h11 + 20);
        glVertex2i(240, h11 + 20);
        glVertex2i(240, h11 + 0);
    glEnd();
glPopMatrix();


glPushMatrix();    
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(240, h12 + 0);
        glVertex2i(240, h12 + 20);
        glVertex2i(260, h12 + 20);
        glVertex2i(260, h12 + 0);
    glEnd();
glPopMatrix();

 glFlush();
glutSwapBuffers();

}

// Inicializa parâmetros de rendering
void init (void)
{
// Define a cor de fundo da janela de visualização como preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void changeWindowSize(GLsizei w, GLsizei h)
{
           // Evita a divisao por zero
    if(h == 0) h = 1;

           // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

           // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)
        gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
    else
        gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}


void up(int value)
{  

    h0 = (sin((k+1)* pi/180)*90) +90;
    h1 = (sin((k+10)* pi/180)*90) +90;
    h2 = (sin((k+20)* pi/180)*90) +90;
    h3 = (sin((k+30)* pi/180)*90) +90;
    h4 = (sin((k+40)* pi/180)*90) +90;
    h5 = (sin((k+50)* pi/180)*90) +90;
    h6 = (sin((k+60)* pi/180)*90) +90;
    h7 = (sin((k+70)* pi/180)*90) +90;
    h8 = (sin((k+80)* pi/180)*90) +90;
    h9 = (sin((k+90)* pi/180)*90) +90;  
    h10 = (sin((k+100)* pi/180)*90) +90;
    h11 = (sin((k+110)* pi/180)*90) +90;
    h12 = (sin((k+120)* pi/180)*90) +90;             
                       
      
    k++;    
    
    glutPostRedisplay();
    glutTimerFunc(10,up, 1);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Holla");
    glutDisplayFunc(draw);
    glutReshapeFunc(changeWindowSize);
  
    glutTimerFunc(10, up, 1);
    init();
    glutMainLoop();
return 0;           
}