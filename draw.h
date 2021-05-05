#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h> 
#include <SDL2/SDL_render.h>

void gfx_draw_line(SDL_Renderer *render, int x0, int y0, int x1, int y1);


void gfx_draw_circle(SDL_Renderer* render, int x,int y,int r);

#endif