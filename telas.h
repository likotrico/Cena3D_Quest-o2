#ifndef TELAS_H
#define TELAS_H

#define m 0
#define W 640
#define H 640
#define w (W - 4 * m) / 2
#define h (H - 4 * m) / 2

#define incZ .25
#define minZ -4
#define maxZ 11

extern int zoom;

void desenharTelaXY();

void desenharTelaYZ();

void desenharTelaXZ();

void desenharPerspectiva(int);

#endif
