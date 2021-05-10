#ifndef CHARGE_C
#define CHARGE_C
#include "charge.h"
#include "draw.h"
#include "utils.h"
#include "main.h"

// Draw all the charges
// A circle with minus sign for negative charges
// A circle with a plus sign for positive charges
void draw_charges(SDL_Renderer *context, charge_t *charges,int num_charges, double x0, double x1, double y0, double y1){
    for (int i = 0; i < num_charges; i++)
    {
        gfx_draw_circle(context,charges[i].pos.x,charges[i].pos.y,CHARGE_RADIUS);
        if(charges[i].q != 0){
        gfx_draw_line(context,charges[i].pos.x-CHARGE_RADIUS,charges[i].pos.y,charges[i].pos.x+CHARGE_RADIUS,charges[i].pos.y);

        }
        if(charges[i].q > 0)
        {
            gfx_draw_line(context,charges[i].pos.x,charges[i].pos.y-CHARGE_RADIUS,charges[i].pos.x,charges[i].pos.y+CHARGE_RADIUS);
        }
    }
}
#include "vector.h"
#include <math.h>

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