#ifndef charge_h
#define charge_h
#include "vector.h"


typedef struct {
    Vector pos;
    double q;
} charge_t;

bool compute_e(charge_t c, Vector p, double eps, Vector *e);


void gfx_draw_line(SDL_Renderer* render,int x0,int y0,int x1,int y1){
    float dy = y1-y0;
    float dx = x1-x0;
    float m_dx = x0-x1;
    int a,e,y;

    if(dy >= 0){
        if(dy <= dx){
            for(int x = x0; x < x1; x++){
                e+=a
                if( e >= dx){
                    y++;
                    e-= 2*dx;
                }
            }
        }else if((0<=dx) && (dx < dy)){
            a = 2*dx;
        }
    }

    float a = dy/dx;
    int y = y0;
    float e = 0;
    for(int x = x0; x < x1; x+= dx){
        SDL_RenderDrawPoint(render,x,y);
        e+=a;
        while(e >= 0.5f){
            y++;
            e--;
        }
        while(e <= -0.5f){
            y--;
            e++;
        }
    }
}

#endif