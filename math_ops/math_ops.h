#pragma once
#include "../matrix/matrix.h"

double vector_norm(const Vector& y);

Vector vector_sub(const Vector& a, const Vector& b);

double rel_error(const Vector& x_exact, const Vector& x_approx);

double calc_res(const Matrix& A, const Vector& x_approx, const Vector& b);