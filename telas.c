#include "windows.h"

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

#include "telas.h"

int zoom = 0;

void desenharTelaXY()
{
    gluLookAt(0.0, 0.0, 0.5,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glViewport(m, m * 3 + h, w, h);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(1);
}

void desenharTelaYZ()
{
    gluLookAt(0.5, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glViewport(m * 3 + h, m * 3 + h, w, h);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(1);
}

void desenharTelaXZ()
{
    gluLookAt(0.0, 0.5, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, -1.0);

    glViewport(m, m, w, h);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glutSolidTeapot(1);
}

void desenharPerspectiva(int degree)
{
    int dist = 2;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1, 0.01, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(dist, dist, dist, 0, 0, 0, 0, 1, 0);

    glViewport(m * 3 + h, m, w, h);

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glRotated(degree, 0, 1, 0);
    glutSolidTeapot(1);
}
