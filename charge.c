#ifndef CHARGE_C
#define CHARGE_C
#include "charge.h"
#include "draw.h"
#include "main.h"
#include "vector.h"
#include <math.h>

#define MAX_HOP (5000)
// Draw all the charges
// A circle with minus sign for negative charges
// A circle with a plus sign for positive charges
void draw_charges(SDL_Renderer *context, charge_t *charges,int num_charges, double x0, double x1, double y0, double y1,double rotation){
    int lineSize = CHARGE_RADIUS*0.5;
    for (int i = 0; i < num_charges; i++)
    {
        if(!(charges[i].pos.x > x1 || charges[i].pos.x < x0 || charges[i].pos.y > y1 || charges[i].pos.y < y0)){
        gfx_draw_circle(context,charges[i].pos.x,charges[i].pos.y,CHARGE_RADIUS);
        if(charges[i].q != 0){

            int linex0 = charges[i].pos.x-lineSize*cos(rotation);
            int liney0  = charges[i].pos.y+lineSize*sin(rotation);

            int linex1 = charges[i].pos.x+lineSize*cos(rotation);
            int liney1 = charges[i].pos.y-lineSize*sin(rotation);
            
            gfx_draw_line(context,linex0,liney0,linex1,liney1);
        }
        if(charges[i].q > 0)
        {
            int linex0 = charges[i].pos.x-lineSize*cos(rotation+PI/2);
            int liney0  = charges[i].pos.y+lineSize*sin(rotation+PI/2);

            int linex1 = charges[i].pos.x+lineSize*cos(rotation+PI/2);
            int liney1 = charges[i].pos.y-lineSize*sin(rotation+PI/2);
            
            gfx_draw_line(context,linex0,liney0,linex1,liney1);
        }
        }
    }
}

bool draw_field_line(SDL_Renderer *context, charge_t *charges, int num_charges, double dx, Vector pos0, double x0, double x1, double y0, double y1){
    int currentStep = 0; //keep a step counter to avoid being stuck in a loop
    double eps = CHARGE_RADIUS;

    Vector currentPos = pos0;
    Vector direction = {.x= 0, .y = 0};
    //compute direction we should go in until we get too close to a charge
    while(compute_total_normalized_e(charges, num_charges, currentPos, eps, &direction)){
        //compute next position
        Vector step = vec_mult(direction, dx);
        Vector nextPos = vec_add(currentPos, step);

        //draw the line
        gfx_draw_line(context, currentPos.x, currentPos.y, nextPos.x, nextPos.y);

        //change current position
        currentPos = nextPos;
        //if we are out of bounds or had too many steps
        if(currentPos.x > x1 || currentPos.x < x0 || currentPos.y > y1 || currentPos.y < y0 || currentStep > MAX_STEP){
            return false; //stop execution
        }
        currentStep++;
    }

    return true;
}

bool compute_e(charge_t c, Vector p, double eps, Vector *e){
    double k = 8.988* pow(10, 9);

    //compute distance to charge
    Vector diff = vec_sub(p, c.pos);
    double r = vec_norm(diff);
    //if we are too close, stop here
    if(r < eps){
        return false;
    }

    //E = k * q/r^2
    double E = k * c.q / pow(r,2);
    //e = E*c_pos*P/norm(c_pos*P)
    *e = vec_mult(vec_mult(diff, 1/r), E);

    return true;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, Vector p, double eps, Vector *e){
    //sum up every electrical field created by every charges
    for (int i = 0; i < num_charges; i++) {
        Vector tmp;

        bool computation_status = compute_e(charges[i], p, eps, &tmp);
        if(!computation_status){
            return false;
        }

        *e = vec_add(*e, tmp);
    }
    //normalize it to get the direction of the field only
    *e = vec_mult(*e, 1/vec_norm(*e));

    return true;
}

#endif