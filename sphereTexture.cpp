#include <iostream>
#include <stdlib.h>
#include "RgbImage.h"
#include <GL/glut.h>

using namespace std;

GLUquadricObj *sphere = NULL;

float yRotate = 0;
GLuint texture[1];

void init(char *filename) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	RgbImage theTexMap( filename);

	glGenTextures(1, &texture[0]);               // Create The Texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

    sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 0.5, 20.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -20.0f);
	glRotatef(yRotate, 0, 1, 0);
	glRotatef(-90, 1, 0, 0); //-90
	//glutSolidTeapot(5);
	gluSphere(sphere, 5.0, 20, 20);

	glutSwapBuffers();
}
void idleFunc (void)
{
    yRotate += 0.03;
    glutPostRedisplay();
}

char* filename = "world.bmp";

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	glutCreateWindow("World");
	
	init(filename);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutIdleFunc(idleFunc);

	glutMainLoop();
	return 0;
}

