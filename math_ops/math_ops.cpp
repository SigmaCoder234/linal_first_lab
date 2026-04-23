#include <cmath>
#include <stddef.h>
#include "math_ops.h"
#include "../matrix/matrix.h"

// норма вектора
double vector_norm(const Vector &y) {
    double norm = 0;

    for (size_t i = 0; i < y.size(); i++) {
        norm += y[i] * y[i];
    }

    return std::sqrt(norm);
}

// вычитание векторов
Vector vector_sub(const Vector &a, const Vector &b) {
    size_t len = a.size();
    Vector res(len);

    for (size_t i = 0; i < len; i++) {
        res[i] = a[i] - b[i];
    }

    return res;
}

// относительная погрешность
double rel_error(const Vector &x_exact, const Vector &x_approx) {
    double res = vector_norm(vector_sub(x_exact, x_approx)) / vector_norm(x_exact);

    return res;
}

// норма невязки
double calc_res(const Matrix &A, const Vector &x_approx, const Vector &b) {
    return vector_norm(vector_sub(matrix_by_vector(A, x_approx), b));
}