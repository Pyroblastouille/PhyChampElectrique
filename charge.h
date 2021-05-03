#ifndef CHARGE_H
#define CHARGE_H
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>



typedef struct {
    Vector pos;
    double q;
} charge_t;
int compute_e(charge_t c, Vector p, double eps, Vector *e);



#endif