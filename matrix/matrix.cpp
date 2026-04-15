#include <random>
#include <vector>

#include "matrix.h"

static std::mt19937 generator(1337);

Matrix create_matrix(int dim) {
    Matrix A(dim, std::vector<double>(dim));
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    for (auto& row : A){
        for (auto& elem : row) {
            elem = dis(generator);
        }
    }

    return A;
}

Matrix create_gilbert_matrix(int dim) {
    Matrix gilbert(dim, std::vector<double>(dim));

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            gilbert[i][j] = 1.0 / (i + j + 1);

    return gilbert;
}

Vector create_vector(int len) {
    Vector b(len);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (auto& elem : b) {
        elem = dis(generator);
    }

    return b;
}

Vector matrix_by_vector(const Matrix& A, const Vector& b) {
    size_t len = A.size();
    Vector result(len);

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            result[i] = result[i] + (A[i][j] * b[j]);
        }
    }

    return result;
}