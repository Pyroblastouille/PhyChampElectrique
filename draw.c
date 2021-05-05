#ifndef DRAW_C
#define DRAW_C
#include "draw.h"

void gfx_draw_circle(SDL_Renderer* render, int x, int y, int r){
    // (R- 1/2)² <= (x-xc)²+(y-yc)² < (R+1/2)²

    

    // (R- 1/2)² <= x²+y² < (R+1/2)²

    // regle 1 : C : (0,0)
    //regle 2 : On est donc [90°;45°] <=> 2eme octant

}

void gfx_draw_line(SDL_Renderer* render,int x0,int y0,int x1,int y1){
    float dy = y1-y0;
    float dx = x1-x0;
    int a = 0,e = 0,y = 0;

    if(dy >= 0){
        if(dy <= dx){
            for(int x = x0; x < x1; x++){
                SDL_RenderDrawPoint(render,  x, y);
                e+=a;
                if( e >= dx){
                    y++;
                    e-= 2*dx;
                }
            }
        }else if((0<=dx) && (dx < dy)){
            a = 2*dx;
        }
    }
}


#endif