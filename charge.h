#ifndef CHARGE_H
#define CHARGE_H
#define MAX_STEP 100000
#include <stdbool.h>
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef struct
{
    double q;
    Vector pos;
} charge_t;

/**
 * @brief Compute the electrical field that charge c creates at the point p.
 *        Computed electrical field stored in *e.
 *
 * @param eps Minimum distance to the charge at which we will compute *e. 
 *
 * @returns True if *e was computed correctly, False if p was too close to c.
 */
bool compute_e(charge_t c, Vector p, double eps, Vector *e);

/**
 * @brief Compute the normalized sum of all the electrical fields created by *charges at a point p.
 *        Computed normalized electrical field stored in *e. 
 *
 * @param *charges Pointer on first element of charges array
 * @param num_charges Number of charges
 * @param eps Minimum distance to a charge at which we will compute *e. 
 *
 * @returns True if *e was computed correctly, False if p was too close to a charge.
 */
bool compute_total_normalized_e(charge_t *charges, int num_charges, Vector p,
double eps, Vector *e);

/**
 * @brief From a given point, draw a line following the combined electrical fields of all given charges.
 * 
 * @param x0 Left most bound
 * @param x1 Right most bound
 * @param y0 Top most bound
 * @param y1 Bottom most bound
 * 
 * @param *context Given SDL context on which to draw on
 * @param *charges Pointer on first element of charges array
 * @param num_charges Number of charges
 * @param dx Size of step (px)
 * @param pos0 Starting position
 *
 * @returns True if the line was drawn successfully, False if the field line is gone out of bounds or has exceeded the maximum amount of steps.
 */
bool draw_field_line(SDL_Renderer *context, charge_t *charges,
int num_charges, double dx, Vector pos0, double x0,
double x1, double y0, double y1);

/**
 * @brief Draw all the given charges into the SDL context. Positive charge will have a plus sign inside Negative will have a minus sign.
 * 
 * @param x0 Left most bound
 * @param x1 Right most bound
 * @param y0 Top most bound
 * @param y1 Bottom most bound
 * 
 * @param *context Given SDL context on which to draw on
 * @param *charges Pointer on first element of charges array
 * @param num_charges Number of charges
 * @param rotation Rotation of positive or negative sign inside of charge
 *
 * @returns True if the line was drawn successfully, False if the field line is gone out of bounds or has exceeded the maximum amount of steps.
 */
void draw_charges(SDL_Renderer *context, charge_t *charges,
int num_charges, double x0, double x1, double y0, double y1,double rotation);

#endif