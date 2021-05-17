#define WIN_WIDTH 100
#define WIN_HEIGHT 100

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "vector.h"
#include "charge.h"
#include "draw.h"
#include <time.h>
#include <float.h>

SDL_Window *win = NULL;
SDL_Renderer *screenRender = NULL;

SDL_Event event;

int main()
{

    //Déclaration de la fenêtre SDL
    srand(0);
    int running = 1;
    win = SDL_CreateWindow("Champ Electriques", 700, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    screenRender = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(screenRender);
    //met la couleur de l'arrière plan à noir
    SDL_SetRenderDrawColor(screenRender, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(screenRender, NULL);


    SDL_SetRenderDrawColor(screenRender, 255, 255, 255, SDL_ALPHA_TRANSPARENT);

    //Fais des trucs
    charge_t charges[1];

    Vector tmpVec = {.x = 500, .y = 500};
    charge_t tmpCharge = {.q = 0.0000001, .pos = tmpVec};
    charges[0] = tmpCharge;

    Vector tmpVec2 = {.x = 525, .y = 475};
    Vector result = {.x = 0, .y = 0};
    compute_total_normalized_e(charges, 1, tmpVec2, 1, &result);
    vec_print(result, "Result : ");

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
