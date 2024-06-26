#ifndef TELAS_H
#define TELAS_H

#define WIN_SIZE 600
#define VP_MARGIN 0
#define VP_SIZE (WIN_SIZE - 4 * VP_MARGIN) / 2

#define VP_4 VP_MARGIN * 3 + VP_SIZE, VP_MARGIN, VP_SIZE, VP_SIZE

#define INC_Z .125
#define MIN_Z -10
#define MAX_Z 25

extern int zoom;

void desenharTelaXY();

void desenharTelaYZ();

void desenharTelaXZ();

void desenharPerspectiva(int);

#endif
