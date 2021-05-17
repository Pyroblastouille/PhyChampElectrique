#ifndef CHARGE_C
#define CHARGE_C
#include "charge.h"
#include "draw.h"
#include "utils.h"
#include "main.h"
#include "vector.h"
#include <math.h>

// Draw all the charges
// A circle with minus sign for negative charges
// A circle with a plus sign for positive charges
void draw_charges(SDL_Renderer *context, charge_t *charges,int num_charges, double x0, double x1, double y0, double y1,double rotation){
    int lineSize = CHARGE_RADIUS*0.5;
    for (int i = 0; i < num_charges; i++)
    {
        gfx_draw_circle(context,charges[i].pos.x,charges[i].pos.y,CHARGE_RADIUS);
        if(charges[i].q != 0){

            int x0 = charges[i].pos.x-lineSize*cos(rotation);
            int y0  = charges[i].pos.y+lineSize*sin(rotation);

            int x1 = charges[i].pos.x+lineSize*cos(rotation);
            int y1 = charges[i].pos.y-lineSize*sin(rotation);
            
            gfx_draw_line(context,x0,y0,x1,y1);
        }
        if(charges[i].q > 0)
        {
            int x0 = charges[i].pos.x-lineSize*cos(rotation+PI/2);
            int y0  = charges[i].pos.y+lineSize*sin(rotation+PI/2);

            int x1 = charges[i].pos.x+lineSize*cos(rotation+PI/2);
            int y1 = charges[i].pos.y-lineSize*sin(rotation+PI/2);
            
            gfx_draw_line(context,x0,y0,x1,y1);
        }
    }
}

// Compute and then draw all the points belonging to a field line,
// starting from pos0.
// Returns false if pos0 is not a valid position
// (for example if pos0 is too close to a charge).
bool draw_field_line(SDL_Renderer *context, charge_t *charges, int num_charges, double dx, Vector pos0, double x0, double x1, double y0, double y1){
    double eps = CHARGE_RADIUS;

    Vector currentPos = pos0;
    Vector direction = {.x= 0, .y = 0};
    while(compute_total_normalized_e(charges, num_charges, currentPos, eps, &direction)){

        Vector hop = vec_mult(direction, dx);
        Vector nextPos = vec_add(currentPos, hop);

        gfx_draw_line(context, currentPos.x, currentPos.y, nextPos.x, nextPos.y);

        currentPos = nextPos;

        if(currentPos.x > x1 || currentPos.x < x0 || currentPos.y > y1 || currentPos.y < y0){
            return false;
        }
    }
}

bool compute_e(charge_t c, Vector p, double eps, Vector *e){
    double k = 8.988* pow(10, 9);

    Vector diff = vec_sub(p, c.pos);
    double r = vec_norm(diff);

    if(r < eps){
        return false;
    }

    double E = k * c.q / pow(r,2);

    *e = vec_mult(vec_mult(diff, 1/r), E);

    return true;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, Vector p, double eps, Vector *e){

    for (int i = 0; i < num_charges; i++) {
        Vector tmp;

        bool computation_status = compute_e(charges[i], p, eps, &tmp);
        if(!computation_status){
            return false;
        }

        *e = vec_add(*e, tmp);
    }
    
    *e = vec_mult(*e, 1/vec_norm(*e));

    return true;
}

#endif