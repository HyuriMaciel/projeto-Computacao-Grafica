#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
 
void init(void)
{
      //Seta a janela (background) na cor Verde
      glClearColor(0.0,0.0,0.0,0.0);
      //Parâmetros de projeção BI-Dimensional
      glMatrixMode(GL_PROJECTION);
      //glMatrixMode(GL_MODELVIEW);
      gluOrtho2D(0.0,800.0,400.0,0.0);
}
 

void primitivas(void)
{
      //Limpa a Tela e habilita os valores glClearColor
      glClear(GL_COLOR_BUFFER_BIT);
 
      //seta a cor da linha
     
      glPointSize(5.0f);

      glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(400, 200);

      glEnd(); 
 
      glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(20, 20);
        glVertex2i(70, 25);
        glVertex2i(120, 30);
        glVertex2i(10, 80);
        glVertex2i(60,90);
       
      glEnd();

      glLineWidth(3.0f);
      glBegin(GL_LINES);
      	glColor3f(1.0f, 0.0f, 0.0f);
      	glVertex2i(150, 30);
      	glVertex2i(300, 10);

      	glVertex2i(250, 90);
      	glVertex2i(300, 30);

      	glVertex2i(150, 100);
      	glVertex2i(300, 120);

      glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glLineWidth(3.0f);  // aumenta a espessura das linhas
    glBegin(GL_LINE_STRIP);
        glVertex2i(400,20);
        glVertex2i(350,70);
        glVertex2i(450, 120);
        glVertex2i(550, 100);
        glVertex2i(600, 70);
        glVertex2i(500, 20);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glLineWidth(3.0f);  // aumenta a espessura das linhas
    glBegin(GL_LINE_LOOP);
        glVertex2f(720,10);
        glVertex2f(700,50);
        glVertex2f(740, 80);
        glVertex2f( 760, 60);
        glVertex2f(790, 45);
        glVertex2f( 760, 5);
    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glLineWidth(3.0f);  // aumenta a espessura das linhas
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f(100, 150);
        glVertex2f( 50, 220);
        glVertex2f(150, 200);

        glColor3f(0.0f, 1.0f, 0.0f); // verde
        glVertex2f( 170, 130);
        glVertex2f(170, 200);
        glVertex2f( 250, 175);
        
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // verde
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(250, 300);
        glVertex2f(300,200);
        glVertex2f(330, 320);
        glVertex2f(420, 220);
        glVertex2f(480, 280);
       
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f(20,250);
        glVertex2f( 20,300);
        glVertex2f( 120, 300);
        glVertex2f(120, 250);
        glColor3f(0.0f, 1.0f, 0.0f); // verde
        glVertex2f(130, 320);
        glVertex2f(250, 320);
        glVertex2f(100, 370);
        glVertex2f( 300, 370);
    glEnd();


    // glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    // glBegin(GL_POLYGON);
    // glVertex2f(-6,-5);
    //     glVertex2f(-3, 0);
    //     glVertex2f(-6, 5);
    //     glVertex2f( 6, 5);
    //     glVertex2f( 3, 0);
    //     glVertex2f( 6,-5);
    // glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glBegin(GL_QUAD_STRIP);
        glVertex2f(600,250);
        glVertex2f(620,300);
        glVertex2f(540, 290);
        glVertex2f(580, 350);
        glVertex2f(500, 370);
        glVertex2f(330, 390);
        
    glEnd();

 
 	  glFlush();
 
}



int main (int argc, char** argv) {
       
       //estabelece a contato com o sistema de janelas
       glutInit (&argc, argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

       glutCreateWindow("OpenGL é Massa");
 
       glutInitWindowSize(1400,800);
 
       init();
       glutDisplayFunc(primitivas);
       //glCallList(0);

       glutMainLoop();
}