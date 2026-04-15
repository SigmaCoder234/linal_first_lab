#include <cmath>
#include <stdexcept>

#include "gauss.h"

Vector gauss_with_pivot(Matrix A, Vector b) {
    size_t len = A.size();

    // прямой ход
    for (size_t i = 0; i < len; i++) {
        size_t max_index = i;
        double max_val = std::abs(A[i][i]);

        for (size_t j = i + 1; j < len; j++) {
            if (std::abs(A[j][i]) > max_val) {
                max_val = std::abs(A[j][i]);
                max_index = j;
            }
        }

        std::swap(A[i], A[max_index]);
        std::swap(b[i], b[max_index]);


        if (std::abs(A[i][i]) < 1e-18) {
            throw std::runtime_error("Zero pivot encountered: Matrix is singular");
        }

        for (size_t k = i + 1; k < len; k++) {
            double ratio = A[k][i] / A[i][i];

            for (size_t j = i; j < len; j++) {
                A[k][j] -= ratio * A[i][j];
            }

            b[k] -= ratio * b[i];

        }
    }

    Vector x(len);

    for (int i = static_cast<int>(len) - 1; i >= 0; i--) {
        double sum = 0;

        for (size_t j = i + 1; j < len; j++) {
            sum += A[i][j] * x[j];
        }

        if (std::abs(A[i][i]) < 1e-18) {
            throw std::runtime_error("Zero on diagonal");
        }

        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}

Vector gauss_without_pivot(Matrix A, Vector b) {
    size_t len = A.size();

    // прямой ход
    for (size_t i = 0; i < len; i++) {
        if (std::abs(A[i][i]) < 1e-18) {
            throw std::runtime_error("Zero pivot encountered");
        }

        for (size_t k = i + 1; k < len; k++) {
            double ratio = A[k][i] / A[i][i];

            for (size_t j = i; j < len; j++) {
                A[k][j] -= ratio * A[i][j];
            }

            b[k] -= ratio * b[i];

        }
    }

    // ищем корни обратным ходом
    Vector x(len);

    for (int i = static_cast<int>(len) - 1; i >= 0; i--) {
        double sum = 0;

        for (size_t j = i + 1; j < len; j++) {
            sum += A[i][j] * x[j];
        }

        if (std::abs(A[i][i]) < 1e-18) {
            throw std::runtime_error("Zero on diagonal");
        }

        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}
