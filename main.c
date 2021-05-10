

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "main.h"
#include "vector.h"
#include "charge.h"
#include "draw.h"
#include "utils.h"
#include <time.h>

SDL_Window *win = NULL;
SDL_Renderer *screenRender = NULL;

SDL_Event event;

int main()
{
    charge_t charges[2];
    charges[0].pos = vec_createVectorXY(50,50);
    charges[0].q = 1;
    charges[1].pos= vec_createVectorXY(600,350);
    charges[1].q = -1;

    //Déclaration de la fenêtre SDL
    srand(0);
    int running = 1;
    win = SDL_CreateWindow("Champ Electriques", 700, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    screenRender = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(screenRender);
    //met la couleur de l'arrière plan à noir
    SDL_SetRenderDrawColor(screenRender, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(screenRender, NULL);


    SDL_SetRenderDrawColor(screenRender, 255, 255,255, SDL_ALPHA_TRANSPARENT);

    draw_charges(screenRender,charges,2,0,0,200,200);

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
    SDL_Quit();
    return 0;
}
