#ifndef TELAS_H
#define TELAS_H

#define m 5
#define W 600
#define H 600
#define w (W - 4 * m) / 2
#define h (H - 4 * m) / 2

#define incZ 0.5
#define minZ -1
#define maxZ (50-2) / incZ

void desenharTelaXY();

void desenharTelaYZ();

void desenharTelaXZ();

void desenharPerspectiva(int);

#endif
