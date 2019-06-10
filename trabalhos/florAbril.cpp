#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

static int shoulder = 0, sen = 0;


static  float r =  1.0f,  g = 0.0f, b = 0.0f;
static  float r1 = 0.0f, g1 = 1.0f, b1 = 0.0f;
static  float r2 = 0.0f, g2 = 0.0f, b2 = 1.0f;
static  float r3 = 1.0f, g3 = 1.0f, b3 = 1.0f;
static  float rAux, bAux, gAux;
;


void init(void){
  glClearColor (0.0,0,0,0);
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

void D(){

  rAux = r; gAux = g; bAux = b;
  r = r3 ; g = g3; b = b3;
  r1 = rAux; g1 = gAux; b1 = bAux;
  
                                


}

void MouseClick (int button, int state, int x, int y) 
{ 


  if (button == GLUT_LEFT_BUTTON){
    D();
    glutPostRedisplay();


  } 

  if(button == GLUT_RIGHT_BUTTON){
        sen = (sen - 5) % 360;
        glutPostRedisplay(); 

   } 


 
    // switch (button) 
    // { 
    //     case GLUT_LEFT_BUTTON:  
    //                             D();
    //                             glutPostRedisplay();

    //                            break; 
    //     case GLUT_RIGHT_BUTTON: sen = (sen - 5) % 360;
    //                             glutPostRedisplay(); 
    //                            break; 
         
    //} 
    
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
        glColor3f(r, g, b); // vermelho
        glVertex2f(-1, 0);
        glVertex2f(0, 2);
        glVertex2f(-2, 2);

        glColor3f(r1, g1, b1); // verde
        glVertex2f(-1, 0);
        glVertex2f(1, 1);
        glVertex2f(1, -1);
        
        glColor3f(r2, g2,b2); // azul
        glVertex2f(-1, 0);
        glVertex2f(-2, -2);
        glVertex2f(0, -2);

        glColor3f(r3, g3, b3); //branco
        glVertex2f(-1, 0);
        glVertex2f(-3, 1);
        glVertex2f(-3, -1);        

       
  glEnd();
    

  glPopMatrix();

  /*volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
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
