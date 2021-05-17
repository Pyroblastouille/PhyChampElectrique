

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
    charges[0].pos = vec_createVectorXY(50,50);
    charges[0].q = 5e-8;
    charges[1].pos= vec_createVectorXY(600,350);
    charges[1].q = -12e-6;
    charges[2].pos= vec_createVectorXY(500,350);
    charges[2].q = 12e-6;

    //Déclaration de la fenêtre SDL
    srand(0);
    int running = 1;
    win = SDL_CreateWindow("Champ Electriques", 700, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    screenRender = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    double rotate = 0;
    double rotateIncrement = PI/120;
    int x = 50,y = 50;
    int control = 0;
    
    while (running)
    {
        SDL_RenderClear(screenRender);
        //met la couleur de l'arrière plan à noir
        SDL_SetRenderDrawColor(screenRender, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderFillRect(screenRender, NULL);

        //Fais des trucs
        Uint32 mouseState =   SDL_GetMouseState(&x,&y);
        charges[control].pos = vec_createVectorXY(x,y);
        int r = 255,g=255,b=255;
        if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){    
            g = 0;

        }
        if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
            b = 0;
        }
        if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE))
        {
            r = 0;
        }
        
        SDL_SetRenderDrawColor(screenRender, r,g,b, SDL_ALPHA_TRANSPARENT);

        draw_charges(screenRender,charges,num_charges,0,0,200,200,rotate);
        
        for (int i = 0; i < LINES_NUMBER; i++) {
            double x = charges[0].pos.x + (CHARGE_RADIUS + spacing) * cos((2*PI)/LINES_NUMBER * i);
            double y = charges[0].pos.y + (CHARGE_RADIUS + spacing) * sin((2*PI)/LINES_NUMBER * i);
            Vector pos0 = {.x= x, .y = y};
            draw_field_line(screenRender, charges, num_charges, DELTA_HOP, pos0, 0, WIN_WIDTH, 0, WIN_HEIGHT);
        }

        SDL_RenderPresent(screenRender);

        rotate += rotateIncrement;

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
                    case SDLK_0:
                    control = 0 % num_charges;
                    break;
                    case SDLK_1:
                    control = 1 % num_charges;
                    break;
                    case SDLK_2:
                    control = 2 % num_charges;
                    break;
                    case SDLK_3:
                    control = 3 % num_charges;
                    break;
                    case SDLK_4:
                    control = 4 % num_charges;
                    break;
                    case SDLK_5:
                    control = 5 % num_charges;
                    break;
                    case SDLK_6:
                    control = 6 % num_charges;
                    break;
                    case SDLK_7:
                    control = 7 % num_charges;
                    break;
                    case SDLK_8:
                    control = 8 % num_charges;
                    break;
                    case SDLK_9:
                    control = 9 % num_charges;
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
