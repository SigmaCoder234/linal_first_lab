#pragma once
#include "../matrix/matrix.h"

Vector gauss_with_pivot(Matrix A, Vector b);
Vector gauss_without_pivot(Matrix A, Vector b);