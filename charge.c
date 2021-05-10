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


#endif