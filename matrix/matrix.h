#pragma once
#include "../second_lab/src/DynamicArray.h"

class Matrix {
private:
    DynamicArray<double> data;
    int dim;
public:
    Matrix(int size) : data(size * size), dim(size) {}

    // operators
    // Возвращает ссылку на началный элемент i-й строки
    double* operator[](int i) {
        // Возвращаем указатель на начало i-й строки
        return &data[i * dim]; 
    }
    
    // Константная версия
    const double* operator[](int i) const {
        return &data[i * dim];
    }

    int size() const { return dim; }

    void swap_rows(int i, int j) {
        if (i < 0 || i >= dim || j < 0 || j >= dim)
            throw std::out_of_range("Index out of range");
        
        for (int k = 0; k < dim; k++)
            std::swap(data[i * dim + k], data[j * dim + k]);
    }
        
};

using Vector = DynamicArray<double>;

Matrix create_matrix(int dim);
Matrix create_gilbert_matrix(int dim);
Vector create_vector(int len);

Vector matrix_by_vector(const Matrix& A, const Vector& b);