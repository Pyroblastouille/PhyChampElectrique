#ifndef DRAW_C
#define DRAW_C
#include "draw.h"

/// Dessine un cercle sur le renderer
// int xc = centre du cercle sur l'axe x
// int yc = centre du cercle sur l'axe y
// int r  = rayon du cercle
void gfx_draw_circle(SDL_Renderer *render, int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = r - 1;
    while (y >= x)
    {
        // Dessine tous les octants
        SDL_RenderDrawPoint(render, xc + x, yc + y); //2eme octant
        SDL_RenderDrawPoint(render, xc + y, yc + x); //1er octant
        SDL_RenderDrawPoint(render, xc + x, yc - y);
        SDL_RenderDrawPoint(render, xc + y, yc - x);
        SDL_RenderDrawPoint(render, xc - x, yc + y);
        SDL_RenderDrawPoint(render, xc - y, yc + x);
        SDL_RenderDrawPoint(render, xc - x, yc - y);
        SDL_RenderDrawPoint(render, xc - y, yc - x);

        //Met à jour les valeurs pour l'itération suivante
        if (2 * x <= d)
        {
            x += 1;
            d -= 2 * x + 1;
        }
        else if (d < 2 * (r - y))
        {
            y -= 1;
            d += 2 * y - 1;
        }
        else
        {
            x += 1;
            y -= 1;
            d += 2 * (y - x - 1);
        }
    }
}

void gfx_draw_line(SDL_Renderer *render, int x0, int y0, int x1, int y1)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int m_dx = x0 - x1;
    if (dy >= 0)//Octants supérieurs
    {
        if (dy <= dx) //octant 1
        {
            int a = 2 * dy;
            int e = 0;
            int y = y0;
            for (int x = x0; x < x1; x++)
            {
                SDL_RenderDrawPoint(render,x, y);
                e += a;
                if (e >= dx)
                {
                    y += 1;
                    e -= 2 * dx;
                }
            }
        }
        else if ((0 <= dx) && (dx < dy)) // 2ème octant
        {
            int a = 2 * dx;
            int e = 0;
            int x = x0;
            for (int y = y0; y < y1; y++)
            {
                SDL_RenderDrawPoint(render,x, y);
                e += a;
                if (e >= dy)
                {
                    x += 1;
                    e -= 2 * dy;
                }
            }
        }
        else if (dy >= m_dx) // 3ème octant
        {
            int a = 2 * dx;
            int e = 0;

            int m_dy = y0 - y1;

            int x = x0;
            for (int y = y0; y < y1; y++)
            {
                SDL_RenderDrawPoint(render,x, y);

                e += a;

                if (e <= m_dy)
                {
                    x -= 1;
                    e += 2 * dy;
                }
            }
        }
        else // 4ème octant
        {
            gfx_draw_line(render,x1, y1, x0, y0);
        }
    }
    else
    {
        if (m_dx <= dy) // 8ème octant
        { 
            int a = 2 * dy;
            int e = 0;

            int y = y0;
            for (int x = x0; x < x1; x++)
            {
                SDL_RenderDrawPoint(render,x, y);

                e += a;

                if (e <= m_dx)
                {
                    y -= 1;
                    e += 2 * dx;
                }
            }
        }
        else // Tous les autres octants
        {
            gfx_draw_line(render,x1, y1, x0, y0);
        }
    }
}

#endif