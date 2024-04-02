#include "windows.h"

#include <GL/freeglut.h>
#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "telas.h"

int degree = 0;

/**
 * @brief Incrementa o ângulo de rotação e atualiza a tela
 */
void update()
{
    degree += 1;
    degree %= 360;

    glutPostRedisplay();
}

/**
 * @brief Exporta uma captura da janela no formato PNG
 *
 * @param arquivo Nome do arquivo
 */
void printScreen(const char *arquivo)
{
    /** @brief Alocação dos pixeis */
    unsigned char *pixels = (unsigned char *)malloc(3 * W * H);

    // Lê o frame buffer
    glReadPixels(0, 0, W, H, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Inverte na vertical
    for (int y = 0; y < H / 2; y++)
        for (int x = 0; x < W * 3; x++)
        {
            int i = y * W * 3 + x;
            int j = (H - y - 1) * W * 3 + x;

            unsigned char temp = pixels[i];
            pixels[i] = pixels[j];
            pixels[j] = temp;
        }

    // Escreve no arquivo usando a biblioteca stb do usuário nothings no GitHub
    stbi_write_png(arquivo, W, H, 3, pixels, W * 3);

    free(pixels);
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == '-' && zoom < maxZ)
        zoom++;

    if ((key == '=' || key == '+') && zoom > minZ)
        zoom--;

    if (key == 13)
        printScreen("screenshot.png");
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
    float ks_block[4] = {0.9f, 0.9f, 0.9f, 1.0f};    // DEFINE O QUAL CONCENTRADO FICA A LUZ NA SUPERFICIE
    float ns_block = 65.0f;

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
    glutInitWindowSize(W, H);
    glutCreateWindow("Cena 3D");

    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyPressed);

    glutMainLoop();

    return 0;
}
