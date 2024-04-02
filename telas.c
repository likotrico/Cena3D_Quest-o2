#include "windows.h"

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

#include "telas.h"

int zoom = 0;

void desenharTelaXY()
{
    gluLookAt(0, 0, .5, 0, 0, 0, 0, 1, 0);

    glViewport(VP_MARGIN, VP_MARGIN * 3 + VP_SIZE, VP_SIZE, VP_SIZE);

    glutSolidTeapot(1);
}

void desenharTelaYZ()
{
    gluLookAt(.5, 0, 0, 0, 0, 0, 0, 1, 0);

    glViewport(VP_MARGIN * 3 + VP_SIZE, VP_MARGIN * 3 + VP_SIZE, VP_SIZE, VP_SIZE);

    glutSolidTeapot(1);
}

void desenharTelaXZ()
{
    gluLookAt(0, .5, 0, 0, 0, 0, 0, 0, -1);

    glViewport(VP_MARGIN, VP_MARGIN, VP_SIZE, VP_SIZE);

    glutSolidTeapot(1);
}

void desenharPerspectiva(int degree)
{
    double d = 2.25 + zoom * INC_Z;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1, 0.1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(d, d, d, 0, 0, 0, 0, 1, 0);

    glViewport(VP_4);

    glTranslatef(0, 0, 0);
    glRotated(degree, 0, 1, 0);
    glutSolidTeapot(.7);
}
