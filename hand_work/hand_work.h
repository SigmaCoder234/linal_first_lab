#pragma once
#include "../matrix/matrix.h"

void matrix_print(Matrix A);
void vector_print(Vector b);

int safe_input();
bool safe_bool_input();

Matrix fill_matrix(int dim);
Vector fill_vector(int len);