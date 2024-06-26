#include "windows.h"

#include <GL/freeglut.h>
#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "telas.h"

int n_prt = 0;
int pause = 0;
int degree = 0;

void printScreen(const char *filename)
{
    /** @brief Alocação dos pixeis da captura de tela */
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
    sprintf(f, "%s-%d.png", filename, n_prt);
    n_prt++;

    // Escreve no arquivo usando a biblioteca stb do usuário nothings no GitHub
    stbi_write_png(f, VP_SIZE, VP_SIZE, 3, pixels, VP_SIZE * 3);

    free(pixels);
}

GLuint textureID;

void initTexture()
{
    int w = 512, h = 512, ch = 3;

    // Buffer da textura
    unsigned char *pixels = stbi_load("texture.jpg", &w, &h, &ch, STBI_rgb);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Wrapping
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Filtro de Ampliação e Minificação
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Carrega a textura do buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 555, 260, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);
}

void update()
{
    if (!pause)
    {
        degree += 1;
        degree %= 360;
    }

    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == '-' && zoom < MAX_Z)
        zoom++;

    if ((key == '=' || key == '+') && zoom > MIN_Z)
        zoom--;

    if (key == 13 || key == ' ')
        pause = !pause;
}

void skeyPressed(int key, int x, int y)
{
    if (key == GLUT_KEY_F12)
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

    /* MATERIAL */

    /** @brief Cor do Material */
    // float kd_block[4] = {.7, .7, .7, 1}; // Com textura
    float kd_block[4] = {.85, .65, .13, 1}; // Amarelo sem textura
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd_block);

    // /** @brief Cor do Brilho*/
    float ks_block[4] = {.95, .95, .95, 1};
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks_block);

    /** @brief Concentração do Brilho */
    float ns_block = 120.0f;

    glMaterialf(GL_FRONT, GL_SHININESS, ns_block);

    /* TEXTURA */

    // initTexture();

    /* ILUMINAÇÃO */

    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* TEXTURA */

    // glEnable(GL_TEXTURE_2D);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, textureID);

    /* VISÃO ORTOGONAL */

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
    glutSpecialFunc(skeyPressed);

    glutMainLoop();

    return 0;
}
