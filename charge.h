#ifndef CHARGE_H
#define CHARGE_H
#include <stdbool.h>
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef struct
{
    double q;
    Vector pos;
} charge_t;

//E = k * q/r^2

//c_pos = particules qui créent le champ éléctrique
//P = point random

// Compute E*c_pos*P/norm(c_pos*P)
// Return false if norm(c_pos*P) < eps
bool compute_e(charge_t c, Vector p, double eps, Vector *e);

// Compute the normalized sum of Ei*qiP/norm(qiP)
// Return false if for some qiP, norm(qiP) < eps
bool compute_total_normalized_e(charge_t *charges, int num_charges, Vector p,
double eps, Vector *e);

// Compute and then draw all the points belonging to a field line,
// starting from pos0.
// Returns false if pos0 is not a valid position
// (for example if pos0 is too close to a charge).
static bool draw_field_line(SDL_Renderer *ctxt, charge_t *charges,
int num_charges, double dx, Vector pos0, double x0,
double x1, double y0, double y1);

// Draw all the charges
// A circle with minus sign for negative charges
// A circle with a plus sign for positive charges
void draw_charges(SDL_Renderer *context, charge_t *charges,
int num_charges, double x0, double x1, double y0, double y1);


#endif