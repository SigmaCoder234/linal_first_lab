#pragma once
#include "../matrix/matrix.h"

void lu_decomposition(const Matrix& A, Matrix& L, Matrix& U);

Vector forward_sub(const Matrix& L, const Vector& b);
Vector backward_sub(const Matrix& U, const Vector& y);

Vector solve_lu(const Matrix& L,const Matrix& U, const Vector& b);