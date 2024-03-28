#include "windows.h"

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

void desenharTelaXY()
{
    gluLookAt(0.0, 0.0, 0.5,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glViewport(10, 405, 385, 385);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(0.7);
}

void desenharTelaYZ()
{
    gluLookAt(0.5, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glViewport(405, 405, 385, 385);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(0.7);
}

void desenharTelaXZ()
{
    gluLookAt(0.0, 0.5, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, -1.0);

    glViewport(10, 10, 385, 385);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(0.7);
}

void desenharPerspectiva(double degree)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 1, 1, .0, .0, .0, .0, 1, .0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0.01, 5);

    glViewport(405, 10, 385, 385);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glRotated(degree, 0, 1, 0);
    glutSolidTeapot(0.7);
}
