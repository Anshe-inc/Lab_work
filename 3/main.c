#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    size_t size;
    double *elems;
} vec;

vec * create_vec(size_t size) {
    vec *res = calloc(1, sizeof(vec));
    res->elems = calloc(size, sizeof(double));
    res->size = size;
    return res;
}
/*vec* read_vec(size_t size) {
    vec * res = malloc(sizeof(vec));
    res->elems = malloc(sizeof(double) * size);
    res->size = size;
    for (size_t i = 0; i < size; ++i) {
        scanf("%f", &res->elems[i]);
    }

    return res;
}*/

double dist(vec* a, vec* b) {
    double res = 0;
    for (size_t i = 0; i < a->size; ++i) {
        res += (a->elems[i] - b->elems[i]) * (a->elems[i] - b->elems[i]);
    }
    res = sqrt(res);

    return res;
}

double fi1(double x1, double x2, double A) {
    return x1*x1 + x2*x2 + A;
}

double fi2(double x1, double x2, double B) {
    return x1*x2 + B;
}

void equalize(vec* a, vec* b) {
    for (size_t i = 0; i < a->size; ++i) {
        a->elems[i] = b->elems[i];
    }
}

int main() {
    double A = 0.181;
    double B = 0.1;
    double eps = 0.001;

    vec * x = create_vec(2);
    vec * f = create_vec(2);


    //scanf("%lf%lf", x->elems, x->elems + 1);
    x->elems[0] = A;
    x->elems[1] = B;
    
    while (1) {
        //printf("x1 = %f, x2 = %f\n", x->elems[0], x->elems[1]);
        f->elems[0] = fi1(x->elems[0], x->elems[1], A);
        f->elems[1] = fi2(x->elems[0], x->elems[1], B);

        if (isnan(f->elems[0]) || isinf(f->elems[0]) ||
            isnan(f->elems[1]) || isinf(f->elems[1])) {
            printf("No roots");
            return 0;
        }
        if ((dist(f, x) < eps/2)) {
            break;
        }
        //printf("eps = %f\n", dist(f, x));

        equalize(x, f);

    }

    printf("x1 = %0.3f, x2 = %0.3f\n", x->elems[0], x->elems[1]);

    return 0;
}