#ifndef _particle_h_
#define _particle_h_
#include "vector.h"
#include "SDL2/SDL.h"
#define G (0.0000000000667)

#define MIN_DIST 5
#define MAX_DIST 300

#define MIN_MASS 1
#define MAX_MASS 100

/**
 * @brief Donne un nombre entier aléatoire entre min et max
 * 
 * @param min l'entier minimum (inclusif)
 * @param max l'entier maximum (exclusif)
 * @return int 
 */
int randVal(int min,int max){
    if(min > max){
        int tmp = min;
        min = max;
        max = tmp;
    }
    int diff = max - min;
    int rnd = (rand()%diff)+min;
    return rnd;
}
/**
 * @brief Donne un nombre à virgule aléatoire entre min et max
 * 
 * @param min l'entier minimum (inclusif)
 * @param max l'entier maximum (exclusif)
 * @return double 
 */
double randValf(double min,double max){
    if(min > max){
        double tmp = min;
        min = max;
        max = tmp;
    }
    double diff = max - min;
    double rnd = (rand()/(double)RAND_MAX*diff)+min;
    return rnd;
}

/**
 * @brief Structure d'une particule
 * 
 */
typedef struct particle_s{
    Vector position;
    double mass;
} Particle;

/**
 * @brief Ecrit dans la console les variables d'une particule
 * 
 * @param p La particule à dessiner
 * @param i l'identifiant de la particule
 */
void Particle_Print(Particle p,int i){
    printf("Particle %02d %f p(%f,%f)\t%f kg\n",i,vec_length(p.position),p.position.x,p.position.y,p.mass);
}
/**
 * @brief Crée une particule avec des valeurs aléatoires
 * 
 * @return Particle 
 */
Particle Particle_Create(){
    Particle p;

    double angle = randValf(-PI,PI);
    double dist = randValf(MIN_DIST,MAX_DIST);

    p.position = vec_createVectorLengthRad(angle,dist);
    
    p.mass = randValf(MIN_MASS,MAX_MASS);
    return p;
}
/**
 * @brief Calcul la résultante des forces de la liste sur la particule donné
 * 
 * @param p La particule recevant les forces
 * @param particles La liste de toutes les particules
 * @param i L'indice de la particule recevant les forces
 * @param nbParticles Le nombre total des particules
 * @return Vector 
 */
Vector Particle_CalculResultante(Particle *p,Particle particles[],int i,int nbParticles){
    Vector resultante = vec_createVectorXY(0,0);
    for (int j = 0; j < nbParticles; j++)
    {
        if(i != j){
            // Fg = G*(mi * mj)/(||rij||³)*rij
            Particle pj = particles[j];
            Vector deltaPVec = vec_sub(pj.position,p->position);
            double deltaP = vec_length(deltaPVec);
            double valForce = G * (p->mass * pj.mass)/(pow(deltaP,3));
            Vector Fg = vec_mult(deltaPVec,valForce);
            resultante = vec_add(resultante,Fg);
        }
    }
    return resultante;
}

/**
 * @brief Calcul la vitesse nécessaire pour orbiter autour de la particule cible
 * 
 * @param p la particule qui va orbiter 
 * @param to Particule autour de laquelle p va orbiter
 * @return Vector 
 */
Vector Particle_CalculateSpeedOrbitFor(Particle* p,Particle* to){
    Vector rij = vec_sub(to->position,p->position);
    float r = vec_length(rij);
    if(r == 0){
        return vec_createVectorXY(0,0);
    }
    // Fg = G * (m1 * m2)/(r³) * rij
    Vector fG = vec_mult(rij,G * (p->mass * to->mass) / (r*r*r));
    
    // a = v²/r => v = sqrt(a*r)
    double v = sqrt(vec_length(fG) * r);
    double angle = atan2(rij.y,rij.x) + PI/2;
    return vec_createVectorLengthRad(angle,v);
}

/**
 * @brief Calcul la position de la particule p après le temps écoulé
 * 
 * @param p la particule qui va changer de position
 * @param particles la liste de toutes les particules
 * @param i l'indice de la particule actuelle
 * @param nbParticles Le total des particules
 * @param elapsed Le temps écoulé en secondes
 * @return Vector 
 */
Vector Particle_CalculPos(Particle *p,Particle *particles, int i,int nbParticles, double elapsed){
    //  [kg*m/s²]
    Vector force = Particle_CalculResultante(p,particles,i,nbParticles+1); 
    //  [m/s²]
    Vector accel = vec_divide(force,p->mass);
    //  [m/s]
    Vector speed = Particle_CalculateSpeedOrbitFor(p,&particles[nbParticles]);
    Vector deltaSpeed = vec_mult(accel,elapsed); 
    Vector totSpeed = vec_add(speed,deltaSpeed); 
    //  [m]
    Vector deltaPos = vec_mult(totSpeed,elapsed); 
    Vector newPos = vec_add(p->position,deltaPos);
    return newPos;
}


void DrawCircle(SDL_Renderer *renderer,Vector pos,int radius,Vector winCenter){
    int x = pos.x;
    int y = pos.y;
    int origin_x = winCenter.x;
    int origin_y = winCenter.y;
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    while (offsety >= offsetx)
    {

        SDL_RenderDrawLine(renderer, origin_x + x - offsety, origin_y + y + offsetx, origin_x + x + offsety, origin_y + y + offsetx);
        SDL_RenderDrawLine(renderer, origin_x + x - offsetx, origin_y + y + offsety, origin_x + x + offsetx, origin_y + y + offsety);
        SDL_RenderDrawLine(renderer, origin_x + x - offsetx, origin_y + y - offsety, origin_x + x + offsetx, origin_y + y - offsety);
        SDL_RenderDrawLine(renderer, origin_x + x - offsety, origin_y + y - offsetx, origin_x + x + offsety, origin_y + y - offsetx);

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

}

/**
 * @brief Dessine la particule sur le rendeur donné
 * 
 * @param winCenter La position du centre de la fenêtre
 * @param p la particule à dessiner
 * @param render le rendeur
 * @param drawSize la taille qu'aura la particule
 */
void Particle_Draw(Vector winCenter,Particle *p,SDL_Renderer* render,int drawSize){
    if(drawSize <= 1){
        SDL_RenderDrawPoint(render,winCenter.x+p->position.x,winCenter.y+p->position.y);
    }else{
        DrawCircle(render,p->position,drawSize,winCenter);
    }    
}
#endif