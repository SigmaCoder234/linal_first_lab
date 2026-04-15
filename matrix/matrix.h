#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Matrix create_matrix(int dim);
Matrix create_gilbert_matrix(int dim);
Vector create_vector(int len);

Vector matrix_by_vector(const Matrix& A, const Vector& b);