#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static int year = 0;
static int day = 0; 
static int yearL = 0;
static int yearl1 = 0;


void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);

   //glLoadIdentity();

   glPushMatrix();
      glRotatef((GLfloat) year, 0.0, 1.0,0.0);
      glRotatef((GLfloat) day, 0.0,0.0,1.0);
      glutWireSphere(1.0,20,16); // Desenha sol
   glPopMatrix();
      
   glPushMatrix();

      glRotatef((GLfloat) year, 0.0, 1.0,0.0);
      glTranslatef(2.0, 0.0, 0.0); // translada a partir do novo sistema de coordenadas
      glRotatef((GLfloat) day, 0.0, 1.0,0.0);
      glutWireSphere(0.2,10,8); // Desenha planeta 1

   
      glPushMatrix();
         glRotatef((GLfloat) year, 0.0, 1.0, 0.0); // rotaciona no x
         glTranslatef(0.5, 0.0, 0.0); // translada a partir do novo sistema de coordenadas
         glRotatef((GLfloat) day, 0.0, 1.0,0.0);
         glutWireSphere(0.1,8,5); // lua 1 planeta
      glPopMatrix();

      glPushMatrix();
         glRotatef((GLfloat) year, 1.0, 0.0,0.0); // rotaciona no xy
         glTranslatef(0.5, 0.2, 0.0); // translada a partir do novo sistema de coordenadas
         glRotatef((GLfloat) day, 0.0, 1.0,0.0);
         glutWireSphere(0.1,8,5); // lua 2 planeta
      glPopMatrix();

   glPopMatrix();

   glPushMatrix();

      glRotatef((GLfloat) yearL, 0.0, 1.0,0.0);
      glTranslatef(-1.4, 0.0, 0.0); // translada a partir do novo sistema de coordenadas
      glRotatef((GLfloat) day, 0.0, 1.0,0.0);
      glutWireSphere(0.2,10,8); // Desenha planeta 2

   glPopMatrix();

 /* glPushMatrix();
      glRotatef((GLfloat) yearL, 0.0, 2.0, 0.0);
      glTranslatef(2.5, 0.0, 0.0); // translada a partir do novo sistema de coordenadas
      glRotatef((GLfloat) day, 0.0, 1.0,0.0);
      glutWireSphere(0.1,8,5); // lua 1 planeta
   glPopMatrix();*/

   /*glPushMatrix();
      glRotatef((GLfloat) yearl1, 0.0, 1.0,0.0);
      glTranslatef(2.0, 0.7, 0.0); // translada a partir do novo sistema de coordenadas
      glRotatef((GLfloat) day, 0.0, 1.0,0.0);
      glutWireSphere(0.1,8,5); // lua 2 planeta
   glPopMatrix();*/
   
   glutSwapBuffers(); // Pois estamos adotando o GLUT_DOUBLE   

}

void reshape (int w, int h)
{
   
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

   gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0,20.0);
   gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0); // posição do camera
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
       case 'y':
         year = (year + 5) % 360;
         yearL = (yearL - 5) % 360;
          //l1 = (l1 - 5) % 360;
         glutPostRedisplay();
         break;     
      case 'Y':
         year = (year - 5) % 360;
         yearL = (yearL + 5) % 360;
         yearl1 = (yearl1 + 5) % 360;
         glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Rotação planetas");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}