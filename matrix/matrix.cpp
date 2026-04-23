#include <random>

#include "matrix.h"

static std::mt19937 generator(1337);

Matrix create_matrix(int dim) {
    Matrix A(dim);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++) {
            A[i][j] = dis(generator);
        }
    }

    return A;
}

Matrix create_gilbert_matrix(int dim) {
    Matrix gilbert(dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            gilbert[i][j] = 1.0 / (i + j + 1);

    return gilbert;
}

Vector create_vector(int len) {
    Vector b(len);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (int i = 0; i < len; i++) {
        b[i] = dis(generator);
    }

    return b;
}

Vector matrix_by_vector(const Matrix& A, const Vector& b) {
    int dim = A.size();
    Vector result(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            result[i] = result[i] + (A[i][j] * b[j]);
        }
    }

    return result;
}