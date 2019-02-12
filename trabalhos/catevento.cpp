#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

static int shoulder = 0, sen = 0;

void init(void){
  glClearColor (0.0,0,0,0);
}


void display(void){

  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  /* origem posicionada */
  glTranslatef (-1.0, 0.0, 0.0);
  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

  /* origem posicionada no centro*/ 
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  //haste do catavento
  glLineWidth(5.0f);
  glBegin(GL_LINES);
        glColor3f(139, 60, 19);
        glVertex2i(1, 0);
        glVertex2i(1, -5);
      glEnd();
  glPopMatrix();
 
   
  /* origem posicionada  */
  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) sen, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);

  glPushMatrix();
  glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f(-1, 0);
        glVertex2f(0, 2);
        glVertex2f(-2, 2);

        glColor3f(1.0f, 0.0f, 0.0f); // vermelho 
        glVertex2f(-1, 0);
        glVertex2f(-2, -2);
        glVertex2f(0, -2);

        glColor3f(0.0f, 1.0f, 0.0f); // verde
        glVertex2f(-1, 0);
        glVertex2f(-3, 1);
        glVertex2f(-3, -1);        

        glColor3f(0.0f, 1.0f, 0.0f); // verde
        glVertex2f(-1, 0);
        glVertex2f(1, 1);
        glVertex2f(1, -1);
        
  glEnd();
    

  glPopMatrix();

  /*volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

void reshape (int w, int h){

  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'a':
    sen = (sen + 5) % 360;
    glutPostRedisplay();
    break;
  case 'd':
    sen = (sen- 5) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

void MouseClick (int button, int state, int x, int y) 
{ 
    switch (button) 
    { 
        case GLUT_LEFT_BUTTON:  sen = (sen + 5) % 360;
                                 glutPostRedisplay();

                               break; 
        case GLUT_RIGHT_BUTTON: sen = (sen- 5) % 360;
                                glutPostRedisplay(); 
                               break; 
         
    } 
    
} 

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
   glutMouseFunc(MouseClick); 
  glutMainLoop();
  return 0;
}
