#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898
#define SPEEDBALL 0.02

GLfloat circle_points = 360.;
GLfloat posX = 0.0, posY= 0.0;
GLint time1 = 0, time2 = 0;

void createBall(){

	glPushMatrix();
		glColor3f(0.0, 200.0, 200.0);
		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex2f(posX, posY);
		glEnd();
	glPopMatrix();

}

void displaySoccer(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1., 1., 1.0);

    // Círculo central
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circle_points; i++) {
		GLfloat angle = 2*PI*i/circle_points;
		glVertex2f(cos(angle)*0.4, sin(angle)*0.4);
	}
	glEnd();

    // Formato do campo
	glBegin(GL_LINE_LOOP);
		glVertex2f(-2.66, -2.);
		glVertex2f(-2.66, 2.);
		glVertex2f(2.66, 2.);
		glVertex2f(2.66, -2.);
	glEnd();

	// grande área esquerda
	glBegin(GL_LINE_STRIP);
		glVertex2f(-2.66, -0.89);
		glVertex2f(-2.66 + 0.73, -0.89);
		glVertex2f(-2.66 + 0.73, 0.89);
		glVertex2f(-2.66, 0.89);
	glEnd();

	// grande área direita
	glBegin(GL_LINE_STRIP);
		glVertex2f(2.66, -0.89);
		glVertex2f(2.66 - 0.73, -0.89);
		glVertex2f(2.66 - 0.73, 0.89);
		glVertex2f(2.66, 0.89);
	glEnd();

	// goal Direita
	glBegin(GL_LINE_STRIP);
		glVertex2f(2.66, -0.162);
		glVertex2f(2.66 + 0.1084, -0.162);
		glVertex2f(2.66 + 0.1084, 0.162);
		glVertex2f(2.66, 0.162);
	glEnd();

	// goal esquerdo
	glBegin(GL_LINE_STRIP);
		glVertex2f(-2.66, -0.162);
		glVertex2f(-2.66 - 0.1084, -0.162);
		glVertex2f(-2.66 - 0.1084, 0.162);
		glVertex2f(-2.66, 0.162);
	glEnd();


	// Pequena área esquerda
	glBegin(GL_LINE_STRIP);
		glVertex2f(-2.66, -0.162 - 0.24);
		glVertex2f(-2.66 + 0.24, -0.162 - 0.24);
		glVertex2f(-2.66 + 0.24, 0.162 + 0.24);
		glVertex2f(-2.66, 0.162+ 0.24);
	glEnd();

	// Pequena área direita
	glBegin(GL_LINE_STRIP);
		glVertex2f(2.66, -0.162 - 0.24);
		glVertex2f(2.66 - 0.24, -0.162 - 0.24);
		glVertex2f(2.66 - 0.24, 0.162 + 0.24);
		glVertex2f(2.66, 0.162+ 0.24);
	glEnd();

	//Arco grande área direita
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circle_points; i++) {
			GLfloat angle = 2*PI*i/circle_points;
			if(cos(angle)*0.4 - 2.66 + 0.48 >= -2.66 + 0.73){
				glVertex2f(cos(angle)*0.4 - 2.66 + 0.48, sin(angle)*0.4);
			}
		}
	glEnd();

	//Arco grande área esquerda
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circle_points; i++) {
			GLfloat angle = 2*PI*i/circle_points;
			if(cos(angle)*0.4 + 2.66 - 0.48 <= 2.66 - 0.73){
				glVertex2f(cos(angle)*0.4 + 2.66 - 0.48, sin(angle)*0.4);
			}
		}
	glEnd();

	// Mediana do campo
	glBegin(GL_LINES);
		glVertex2f(0.0, -2.0);
		glVertex2f(0.0, 2.0);
	glEnd();

    //Ponto Central
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	glEnd();

    //Ponto Esquerda
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex2f(-2.66 + 0.48,0.0);
	glEnd();
    //Ponto Direita
	glBegin(GL_POINTS);
		glVertex2f(2.66 - 0.48,0.0);
	glEnd();

	createBall();
    glutSwapBuffers();
}

void restartBall(){
	posX = 0.0;
	posY = 0.0;
}

void corner(){
	if(posX<-2.66 && posY>0){
		posX = -2.66;
		posY = 2.;
	} else if(posX<-2.66 && posY<0){
		posX = -2.66;
		posY = -2.;
	} else if(posX>2.66 && posY>0){
		posX = 2.66;
		posY = 2.;
	} else if(posX>2.66 && posY<0){
		posX = 2.66;
		posY = -2.;
	}
}

void lateral(){
	if(posY>2) posY = 2;
	else posY = -2;
}

void placar(){
	if(posX <= -2.66 && posY <= 0.5 && posY >= -0.5) {
		time1++;
		printf("TIME 1: %d ----- TIME 2: %d\n", time1, time2);
	} else if(posX >= 2.66 && posY <= 0.5 && posY >= -0.5) {

		time2++;
		printf("TIME 1: %d ----- TIME 2: %d\n", time1, time2);
	}

}

void init(){
	glClearColor(0.124, 0.252, 0.0, 1.0);
}


void reshape(int w, int h){

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //Posição da Câmera

}

void Timer(int value){
	if(posX <= -2.66 && posY <= 0.5 && posY >= -0.5) {
		if(posX <= -2.79) {
			restartBall();
		}else{
			posX -= 0.025;
		}
	} else 	if(posX >= 2.66 && posY <= 0.5 && posY >= -0.5) {
		if(posX >= 2.79) {
			restartBall();
		}else{
			posX += 0.025;
		}
	}else if(posY>2){
		if(posY >= 2.1){
			lateral();
		}else {
			posY+= 0.025;
		}
	}else if(posY<-2){
		if(posY <= -2.1){
			lateral();
		}else {
			posY-= 0.025;
		}
	}else if(posX < -2.66 || posX > 2.66) corner();


	glutPostRedisplay();
	glutTimerFunc(300,Timer, 0);

}


void keyboard(unsigned char key, int x, int y){

    switch (key){

    	case 'w':
    		posY += SPEEDBALL;
    		//placar();
    		glutPostRedisplay();
    		break;

    	case 'x':
    		posY -= SPEEDBALL;
    		glutPostRedisplay();
    		placar();
    		break;

    	case 'd':
    		posX += SPEEDBALL;
    		glutPostRedisplay();
    		placar();
    		break;

    	case 'a':
    		posX -= SPEEDBALL;
			glutPostRedisplay();
    		placar();
    		break;

    	case 'q':
    		posX -= SPEEDBALL;
    		posY += SPEEDBALL;
			glutPostRedisplay();
    		placar();
    		break;

    	case 'e':
    		posX += SPEEDBALL;
    		posY += SPEEDBALL;
			glutPostRedisplay();
    		placar();
    		break;

    	case 'c':
    		posX += SPEEDBALL;
    		posY -= SPEEDBALL;
			glutPostRedisplay();
    		//placar();
    		break;

    	case 'z':
    		posX -= SPEEDBALL;
    		posY -= SPEEDBALL;
			glutPostRedisplay();
    		//placar();
    		break;
        default:
            break;
    }
}


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Soccer!");

    init();

    glutDisplayFunc(displaySoccer);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(300, Timer, 0);
    glutMainLoop();
    return 0;
}