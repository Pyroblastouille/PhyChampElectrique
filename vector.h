
#ifndef Vector_h_
#define Vector_h_


#define PI 3.14159265358979323846264338327950288419716939937510 /* pi */
#define DEG_TO_RAD (PI / 180.0)
#define RAD_TO_DEG (180.0 / PI)

/**
 * @brief Défini un vecteur
 * 
 */
typedef struct _vec
{
    double x, y;
} Vector;

/**
 * @brief Calcul la direction d'un vecteur en radians
 * 
 * @param a le vecteur dont on connaitra la direction
 * @return double 
 */
double vec_directionRad(Vector a);

/**
 * @brief Calcul la direction d'un vecteur en degrés
 * 
 * @param a le vecteur dont on connaitra la direction
 * @return double 
 */
double vec_directionDeg(Vector a);
/**
 * @brief Crée un vecteur avec une longueur et un angle en radians
 * 
 * @param direction angle en radians
 * @param length la longueur du vecteur
 * @return Vector 
 */
Vector vec_createVectorLengthRad(double direction, double length);
/**
 * @brief Crée un vecteur avec une longueur et un angle en degrés
 * 
 * @param direction angle en degrés
 * @param length la longueur du vecteur
 * @return Vector 
 */
Vector vec_createVectorLengthDeg(double direction, double length);
/**
 * @brief Crée un vecteur avec ses deux valeurs
 * 
 * @param x valeur pour le x du vecteur
 * @param y valeur pour le y du vecteur
 * @return Vector 
 */
Vector vec_createVectorXY(double x, double y);
/**
 * @brief Multiplie un vecteur par un nombre à virgule
 * 
 * @param v 
 * @param alpha 
 * @return Vector 
 */
Vector vec_mult(Vector v, double alpha);
/**
 * @brief Divise un vecteur par un nombre à virgule
 * 
 * @param v 
 * @param alpha 
 * @return Vector 
 */
Vector vec_divide(Vector v, double alpha);
/**
 * @brief Additionne deux vecteurs entre eux
 * 
 * @param a 
 * @param b 
 * @return Vector 
 */
Vector vec_add(Vector a, Vector b);
/**
 * @brief Soustrait deux vecteurs entre eux
 * 
 * @param a 
 * @param b 
 * @return Vector 
 */
Vector vec_sub(Vector a, Vector b);
/**
 * @brief Calcul la magnitude du vecteur
 * 
 * @param v 
 * @return double 
 */
double vec_length(Vector v);
/**
 * @brief Calcul un vecteur de magnitude 1 correspondant à v
 * 
 * @param v 
 * @return Vector 
 */
Vector vec_normalize(Vector v);
/**
 * @brief Multiplie un vecteur par un autre vecteur
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double vec_scalar_product(Vector a, Vector b);
/**
 * @brief Prend un vecteur et le met au carré
 * 
 * @param v 
 * @return double 
 */
double vec_norm_sqr(Vector v);
/**
 * @brief Calcul la magnitude d'un vecteur
 * 
 * @param v 
 * @return double 
 */
double vec_norm(Vector v);

/**
 * @brief Ecrit la représentation d'un vecteur dans la console
 * 
 * @param v 
 * @param preamble Une chaine de caractère représentant ce qui va être écrit avant le vecteur
 */
void vec_print(Vector v,char* preamble);
#endif