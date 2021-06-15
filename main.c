

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "main.h"
#include "vector.h"
#include "charge.h"
#include "draw.h"
#include "utils.h"
#include <time.h>
#include <float.h>

SDL_Window *win = NULL;
SDL_Renderer *screenRender = NULL;

SDL_Event event;

int main()
{   
    double spacing = 0.01;
    int num_charges = 3;
    charge_t charges[num_charges];
    charges[0].pos = vec_createVectorXY(CHARGE_RADIUS,WIN_HEIGHT/2);
    charges[0].q = 1;
    charges[1].pos= vec_createVectorXY(WIN_WIDTH/2,CHARGE_RADIUS);
    charges[1].q = -1;
    charges[2].pos= vec_createVectorXY(WIN_WIDTH-CHARGE_RADIUS,WIN_HEIGHT/2);
    charges[2].q = 1;

    //Déclaration de la fenêtre SDL
    srand(0);
    int running = 1;
    win = SDL_CreateWindow("Champ Electriques", 700, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    screenRender = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    double rotate = 0;
    double rotateIncrement = PI/4;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    while (running)
    {   

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() );

        SDL_RenderClear(screenRender);
        //met la couleur de l'arrière plan à noir
        SDL_SetRenderDrawColor(screenRender, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderFillRect(screenRender, NULL);


        SDL_SetRenderDrawColor(screenRender, 255, 255, 255, SDL_ALPHA_TRANSPARENT);

        //Fais des trucs
        draw_charges(screenRender,charges,num_charges,-WIN_WIDTH,WIN_WIDTH*2,-WIN_HEIGHT,WIN_HEIGHT*2,rotate);
        for(int j = 0; j < num_charges;j++)
        for (int i = 0; i < LINES_NUMBER; i++) {
            double x = charges[j].pos.x + (CHARGE_RADIUS + spacing) * cos((2*PI)/LINES_NUMBER * i);
            double y = charges[j].pos.y + (CHARGE_RADIUS + spacing) * sin((2*PI)/LINES_NUMBER * i);
            Vector pos0 = {.x= x, .y = y};
            draw_field_line(screenRender, charges, num_charges, DELTA_HOP, pos0, -WIN_WIDTH,WIN_WIDTH*2,-WIN_HEIGHT,WIN_HEIGHT*2);
        }
        

        SDL_RenderPresent(screenRender);

        rotate += rotateIncrement * deltaTime;
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
