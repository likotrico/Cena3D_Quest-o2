#include "windows.h"

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "telas.h"

int zoom = 0;

void desenharTelaXY()
{
    gluLookAt(0, 0, .5, 0, 0, 0, 0, 1, 0);

    glViewport(m, m * 3 + h, w, h);

    glutSolidTeapot(1);
}

void desenharTelaYZ()
{
    gluLookAt(.5, 0, 0, 0, 0, 0, 0, 1, 0);

    glViewport(m * 3 + h, m * 3 + h, w, h);

    glutSolidTeapot(1);
}

void desenharTelaXZ()
{
    gluLookAt(0, .5, 0, 0, 0, 0, 0, 0, -1);

    glViewport(m, m, w, h);

    glutSolidTeapot(1);
}

void desenharPerspectiva(int degree)
{
    double d = 2.25 + zoom * incZ;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1, 0.1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(d, d, d, 0, 0, 0, 0, 1, 0);

    glViewport(m * 3 + h, m, w, h);

    glRotated(degree, 0, 1, 0);
    glutSolidTeapot(.7);
}
