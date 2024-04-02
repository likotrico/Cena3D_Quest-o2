#include "windows.h"

#include <GL/freeglut.h>
#include <stdio.h>

#include "telas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int prints = 0;

void printScreen(const char *filename)
{
    /** @brief Alocação dos pixeis */
    unsigned char *pixels = (unsigned char *)malloc(3 * VP_SIZE * VP_SIZE);

    // Lê o frame buffer
    glReadPixels(VP_4, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Inverte na vertical
    for (int y = 0; y < VP_SIZE / 2; y++)
        for (int x = 0; x < VP_SIZE * 3; x++)
        {
            int i = y * VP_SIZE * 3 + x;
            int j = (VP_SIZE - y - 1) * VP_SIZE * 3 + x;

            unsigned char temp = pixels[i];
            pixels[i] = pixels[j];
            pixels[j] = temp;
        }

    char f[50];
    sprintf(f, "%s-%d.png", filename, prints);
    prints++;

    // Escreve no arquivo usando a biblioteca stb do usuário nothings no GitHub
    stbi_write_png(f, VP_SIZE, VP_SIZE, 3, pixels, VP_SIZE * 3);

    free(pixels);
}

int degree = 0;

void update()
{
    degree += 1;
    degree %= 360;

    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == '-' && zoom < MAX_Z)
        zoom++;

    if ((key == '=' || key == '+') && zoom > MIN_Z)
        zoom--;

    if (key == 13) // ENTER
        printScreen("tiro-de-tela");
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

    float kd_block[4] = {0.85f, 0.65f, 0.13f, 1.0f}; // DEFINE A COR
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFÍCIE
    float ns_block = 90.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);
    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* TELA 1 */

    glPushMatrix();
    desenharTelaXZ();
    glPopMatrix();

    /* TELA 2 */

    glPushMatrix();
    desenharTelaXY();
    glPopMatrix();

    /* TELA 3 */

    glPushMatrix();
    desenharTelaYZ();
    glPopMatrix();

    /* TELA 4 */

    glPushMatrix();
    desenharPerspectiva(degree);
    glPopMatrix();

    /* ANIMAÇÃO */

    update();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(WIN_SIZE, WIN_SIZE);
    glutCreateWindow("Cena 3D");

    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyPressed);

    glutMainLoop();

    return 0;
}
