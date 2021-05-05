#define WIN_WIDTH 100
#define WIN_HEIGHT 100

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "vector.h"
#include "charge.h"
#include "draw.h"
#include <time.h>

SDL_Window *win = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Rect *screenRect = NULL;
SDL_Renderer *screenRender = NULL;

SDL_Event event;

int main()
{

    //Déclaration de la fenêtre SDL
    srand(0);
    int running = 1;
    win = SDL_CreateWindow("Champ Electriques", 700, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    screenSurface = SDL_GetWindowSurface(win);
    screenRender = SDL_GetRenderer(win);
    SDL_GetClipRect(screenSurface, screenRect);

    SDL_RenderClear(screenRender);
    //met la couleur de l'arrière plan à noir
    SDL_SetRenderDrawColor(screenRender, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(screenRender, NULL);


    SDL_SetRenderDrawColor(screenRender, 255, 255,255, SDL_ALPHA_TRANSPARENT);

    //Fais des trucs
    gfx_draw_line(screenRender, 50, 50, 75, 50);
    gfx_draw_line(screenRender, 50, 50, 72, 62);
    gfx_draw_line(screenRender, 50, 50, 62, 72);
    gfx_draw_line(screenRender, 50, 50, 50, 75);
    gfx_draw_line(screenRender, 50, 50, 38, 72);
    gfx_draw_line(screenRender, 50, 50, 28, 62);
    gfx_draw_line(screenRender, 50, 50, 25, 50);
    gfx_draw_line(screenRender, 50, 50, 28, 38);
    gfx_draw_line(screenRender, 50, 50, 37, 28);
    gfx_draw_line(screenRender, 50, 50, 50, 25);
    gfx_draw_line(screenRender, 50, 50, 62, 28);
    gfx_draw_line(screenRender, 50, 50, 72, 37);
    
    gfx_draw_circle(screenRender,50,50,25);

    SDL_RenderPresent(screenRender);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = 0;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    SDL_FreeSurface(screenSurface);
    SDL_Quit();
    return 0;
}
