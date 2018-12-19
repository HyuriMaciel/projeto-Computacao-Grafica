

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float h0 = 0;
float h1 = 0;
float h2 = 0;
float speed = 1.5;

void timerUp(int value);
void timerDown(int value);

// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

// Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

// Desenha um quadrado preenchido com a cor corrente
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2i(0, h0 + 50);
        glVertex2i(0, h0 + 0);
        glVertex2i(80, h0 + 0);
        glVertex2i(80, h0 + 50);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(80, h1 + 50);
        glVertex2i(80, h1 + 0);
        glVertex2i(160, h1 + 0);
        glVertex2i(160, h1 + 50);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(160, h2 + 50);
        glVertex2i(160, h2 + 0);
        glVertex2i(240, h2 + 0);
        glVertex2i(240, h2 + 50);
    glEnd();

    glFlush();
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


void down(int value)
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
}

void up(int value)
{
    

    if(h0 < 50){
        h0 += speed;
    } 
    else {
        h0 = 50;
        if(h1 < 50){
            h1 += speed;
        } 
        else {
            h1 = 50;
            if(h2 < 50){
                h2 += speed;
            }
             else {
                h2 = 50;

                glutTimerFunc(33,down, 1);
            }
             
        }

    }

    
    glutPostRedisplay();
    glutTimerFunc(33,up, 1);
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
    glutTimerFunc(33, up, 1);
    init();
    glutMainLoop();
return 0;           
}