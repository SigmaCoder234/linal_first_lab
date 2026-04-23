#include "LU.h"
#include "../matrix/matrix.h"
#include <stdexcept>
#include <cmath>

// LU разложение
void lu_decomposition(const Matrix &A, Matrix &L, Matrix &U) {
    int dim = A.size();

    L = Matrix(dim);
    U = Matrix(dim);

    for (int i = 0; i < dim; i++) {
        L[i][i] = 1.0;
    }

    for (int i = 0; i < dim; i++) {

        // Вычисляем строку матрицы U
        for (int j = i; j < dim; j++) {
            double sum = 0;

            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }

            U[i][j] = A[i][j] - sum;
        }

        // Проверка диагонального элемента
        if (std::abs(U[i][i]) < 1e-18) {
            throw std::runtime_error("Zero on diagonal");
        }

        // Вычисляем столбец матрицы L
        for (int j = i + 1; j < dim; j++) {
            double sum = 0;

            for (int k = 0; k < i; k++) {
                sum += L[j][k] * U[k][i];
            }

            L[j][i] = (A[j][i] - sum)/U[i][i];
        }
    }
}

// прямое разложение Ly = b
Vector forward_sub(const Matrix &L, const Vector &b) {
    int dim = L.size();
    Vector y(dim);

    for (int i = 0; i < dim; i++) {
        double sum = 0;

        for (int k = 0; k < i; k++) {
            sum += L[i][k] * y[k];
        }

        y[i] = (b[i] - sum)/L[i][i];
    }

    return y;
}

// обратное разложение Ux = y
Vector backward_sub(const Matrix &U, const Vector &y) {
    int dim = U.size();
    Vector x(dim);

    for (int i = dim - 1; i >= 0; i--) {
        double sum = 0;

        for (int k = i + 1; k < dim; k++) {
            sum += U[i][k] * x[k];
        }

        if (std::abs(U[i][i]) < 1e-18) {
            throw std::runtime_error("Zero on diagonal in U matrix");
        }

        x[i] = (y[i] - sum)/U[i][i];
    }

    return x;
}

// Решение LU разложения LUx = b
Vector solve_lu(const Matrix& L, const Matrix& U, const Vector& b) {
    Vector y = forward_sub(L, b);
    return backward_sub(U, y);
}