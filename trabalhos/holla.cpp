

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float h0 = 0;
float h1 = 0;
float h2 = 0;
float h3 = 0;
float h4 = 0;

float speed = 1.5;
int sen   = 0 ;
int sen1  = 0 ;
int sen2  = 0 ;
int sen3  = 0 ;
int sen4  = 0 ;

void up(int value);
// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

// Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

 glPushMatrix();
    glTranslatef (0.0, sen, 0.0);
// Desenha um quadrado preenchido com a cor corrente
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2i(80, h4 + 0);
        glVertex2i(80, h4 + 20);
        glVertex2i(100,h4 + 20);
        glVertex2i(100, h4 + 0);
    glEnd();
glPopMatrix();
   
 glPushMatrix();   
    glTranslatef (0.0, sen1, 0.0);
    glBegin(GL_QUADS);
       glColor3f(0.0, 0.0, 1.0);
        glVertex2i(60, h3 + 0);
        glVertex2i(60, h3 + 20);
        glVertex2i(80, h3 + 20);
        glVertex2i(80, h3 + 0);
    glEnd();
glPopMatrix();

 glPushMatrix();
    glTranslatef (0.0, sen2, 0.0);
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(40, h2 + 0);
        glVertex2i(40, h2 + 20);
        glVertex2i(60, h2 + 20);
        glVertex2i(60, h2 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();
    glTranslatef (0.0, sen3, 0.0);
    glBegin(GL_QUADS);
       glColor3f(1.0, 0.0, 0.0);
        glVertex2i(20, h1 + 0);
        glVertex2i(20, h1 + 20);
        glVertex2i(40, h1 + 20);
        glVertex2i(40, h1 + 0);
    glEnd();
glPopMatrix();

glPushMatrix();

    glTranslatef (0.0, sen4, 0.0);
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 1.0);
         glVertex2i(0, h0 + 0);
        glVertex2i(0, h0 + 20);
        glVertex2i(20, h0 + 20);
        glVertex2i(20, h0 + 0);
    glEnd();
glPopMatrix();


 glFlush();
glutSwapBuffers();

}

// Inicializa parâmetros de rendering
void init (void)
{
// Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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


/*void down(int value)
{
    

    if(h0 > 0 && h1 > 0 && h2 > 0){

        h0 -= speed;
        h1 -= speed;
        h2 -= speed;
    } 
    else {

        h0 = 0;
        h1 = 0;
        h2 = 0;

        //glutTimerFunc(33,timerUp, 1);
    }

  
    glutPostRedisplay();
    glutTimerFunc(33,down, 1);
}*/

void up(int value)
{  

   h0 = speed;
   h1 = speed + 1;
   h2 = speed + 2;
   h3 = speed + 3;
   h4 = speed + 4;

                         
      

    
    glutPostRedisplay();
    glutTimerFunc(33,up, 1);
}


// Fun��o callback chamada para gerenciar eventos de teclado
void GerenciaTeclado(unsigned char key, int x1, int y1){
    switch(key)
    {
    case 'o':


            if(sen < 30 && sen1 < 30 && sen2 < 30 && sen3 < 30 && sen4 < 30){
                 sen = (sen + 5) % 180;
                 sen1 = (sen1 + 6) % 180;
                 sen2 = (sen2 + 7) % 180;
                 sen3 = (sen3 + 8) % 180;
                 sen4 = (sen4 + 9) % 180;                
                                                
            }
           // if(sen = 0 && sen1  && sen2 >=0 && sen3 >= 0 && sen4 >= 0){
           //       sen = (sen + 9) % 180;
           //       sen1 = (sen1 - 8) % 180;
           //       sen2 = (sen2 - 7) % 180;
           //       sen3 = (sen3 - 6) % 180;
           //       sen4 = (sen4 - 5) % 180;                
                                                
           //  }


           
            
                
        
           
            glutPostRedisplay();

         break;

    case 'p':
        // y -= 5;
        break;

    }
    glutPostRedisplay();

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
     glutKeyboardFunc(GerenciaTeclado);

    //glutTimerFunc(33, up, 1);
    init();
    glutMainLoop();
return 0;           
}