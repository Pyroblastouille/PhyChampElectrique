#ifndef CHARGE_C
#define CHARGE_C
#include "charge.h"
#include "draw.h"
#include "vector.h"
#include <math.h>

bool compute_e(charge_t c, Vector p, double eps, Vector *e){
    double k = 8.988* pow(10, 9);

    Vector diff = vec_sub(p, c.pos);
    double r = vec_norm(diff);

    if(r < eps){
        return false;
    }

    double E = k * c.q / pow(r,2);

    *e = vec_mult(vec_mult(diff, 1/r), E);

    return true;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, Vector p, double eps, Vector *e){

    for (int i = 0; i < num_charges; i++) {
        Vector tmp;

        bool computation_status = compute_e(charges[i], p, eps, &tmp);
        if(!computation_status){
            return false;
        }

        *e = vec_add(*e, tmp);
    }
    
    *e = vec_mult(*e, 1/vec_norm(*e));

    return true;
}

#endif