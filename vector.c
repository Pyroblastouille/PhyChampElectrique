#ifndef VECTOR_C
#define VECTOR_C

#include <math.h>
#include <stdio.h>
#include "vector.h"

/**
 * @brief Calcul la direction d'un vecteur en radians
 * 
 * @param a le vecteur dont on connaitra la direction
 * @return double 
 */
double vec_directionRad(Vector a)
{
    double direction = 0;
    direction = atan2(a.y, a.x);
    return direction;
}

/**
 * @brief Calcul la direction d'un vecteur en degrés
 * 
 * @param a le vecteur dont on connaitra la direction
 * @return double 
 */
double vec_directionDeg(Vector a)
{
    return vec_directionRad(a) * RAD_TO_DEG;
}
/**
 * @brief Crée un vecteur avec une longueur et un angle en radians
 * 
 * @param direction angle en radians
 * @param length la longueur du vecteur
 * @return Vector 
 */
Vector vec_createVectorLengthRad(double direction, double length)
{
    Vector v = {.x = cos(direction) * length, .y = sin(direction) * length};
    return v;
}
/**
 * @brief Crée un vecteur avec une longueur et un angle en degrés
 * 
 * @param direction angle en degrés
 * @param length la longueur du vecteur
 * @return Vector 
 */
Vector vec_createVectorLengthDeg(double direction, double length)
{
    Vector v = {.x = cos(direction * DEG_TO_RAD) * length, .y = sin(direction * DEG_TO_RAD) * length};
    return v;
}
/**
 * @brief Crée un vecteur avec ses deux valeurs
 * 
 * @param x valeur pour le x du vecteur
 * @param y valeur pour le y du vecteur
 * @return Vector 
 */
Vector vec_createVectorXY(double x, double y)
{
    Vector v = {.x = x, .y = y};
    return v;
}
/**
 * @brief Multiplie un vecteur par un nombre à virgule
 * 
 * @param v 
 * @param alpha 
 * @return Vector 
 */
Vector vec_mult(Vector v, double alpha)
{
    return vec_createVectorXY(v.x * alpha, v.y * alpha);
}
/**
 * @brief Divise un vecteur par un nombre à virgule
 * 
 * @param v 
 * @param alpha 
 * @return Vector 
 */
Vector vec_divide(Vector v, double alpha)
{
    return vec_createVectorXY(v.x / alpha, v.y / alpha);
}
/**
 * @brief Additionne deux vecteurs entre eux
 * 
 * @param a 
 * @param b 
 * @return Vector 
 */
Vector vec_add(Vector a, Vector b)
{
    return vec_createVectorXY(a.x + b.x, a.y + b.y);
}
/**
 * @brief Soustrait deux vecteurs entre eux
 * 
 * @param a 
 * @param b 
 * @return Vector 
 */
Vector vec_sub(Vector a, Vector b)
{
    return vec_createVectorXY(a.x - b.x, a.y - b.y);
}
/**
 * @brief Calcul la magnitude du vecteur
 * 
 * @param v 
 * @return double 
 */
double vec_length(Vector v){
    return (sqrt(v.x*v.x+v.y*v.y));
}
/**
 * @brief Calcul un vecteur de magnitude 1 correspondant à v
 * 
 * @param v 
 * @return Vector 
 */
Vector vec_normalize(Vector v)
{
    Vector b;
    b = vec_divide(v, vec_length(v));
    return b;
}
/**
 * @brief Multiplie un vecteur par un autre vecteur
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double vec_scalar_product(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}
/**
 * @brief Prend un vecteur et le met au carré
 * 
 * @param v 
 * @return double 
 */
double vec_norm_sqr(Vector v){
    return vec_scalar_product(v,v);
}
/**
 * @brief Calcul la magnitude d'un vecteur
 * 
 * @param v 
 * @return double 
 */
double vec_norm(Vector v){
    return sqrt(vec_norm_sqr(v));
}

/**
 * @brief Ecrit la représentation d'un vecteur dans la console
 * 
 * @param v 
 * @param preamble Une chaine de caractère représentant ce qui va être écrit avant le vecteur
 */
void vec_print(Vector v,char* preamble)
{
    if(preamble == NULL){
        preamble = "v";
    }
    printf("%s = (%f, %f)\n",preamble, v.x, v.y);
}
#endif
