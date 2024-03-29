#include "windows.h"

#include <GL/freeglut.h>
#include <stdio.h>

#include "telas.h"

double degree = 0;
double max = 360;

void rotate()
{
    if (degree == max)
        degree = 0;
    else
        degree += 1;

    glutPostRedisplay();
}

void lighting()
{
    float position[4] = {0.5f, 0.4f, 0.5f, 0.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    float global_ambient[4] = {0.2f, 0.2f, 0.2f, 0.1f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

int init()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);

    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* SCREEN 1 */

    glPushMatrix();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
        glVertex3d(1, 1, 0);
        glVertex3d(800, 1, 0);
    glEnd();

    glPopMatrix();
    glPushMatrix();

    desenharTelaXZ();

    /* SCREEN 2 */

    glPopMatrix();
    glPushMatrix();

    desenharTelaXY();

    /* SCREEN 3 */

    glPopMatrix();
    glPushMatrix();

    desenharTelaYZ();

    /* SCREEN 4 */
    
    glPopMatrix();
    glPushMatrix();

    desenharPerspectiva(degree);

    rotate();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cena 3D");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
