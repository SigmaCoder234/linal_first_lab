#include "hand_work.h"

#include <cstdio>
#include <iostream>

void matrix_print(Matrix A) {
    for (int i = 0; i < A.size(); i++) {
        std::cout << "|  ";
        for (int j = 0; j < A.size(); j++) {
            std::cout << A[i][j] << "  |  ";
        }
        std::cout << "\n";
    }
}

void vector_print(Vector b) {
    std::cout << "|  ";
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << "  |  ";
    }
}

// функция для безопасного ввода int начений
int safe_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1) {
            break;
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
    return value;
}

// Функция для безопасного ввода bool значений (y/n или 1/0)
bool safe_bool_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1 && (value == 0 || value == 1)) {
            break;
        }

        else {
            printf("Invalid input. Please enter 1 (Yes) or 0 (No): ");
        }
    }
    return value == 1;
}

Matrix fill_matrix(int dim) {
    Matrix A(dim, std::vector<double>(dim));

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << "A[" << i << "][" << j << "] = ";
            A[i][j] = safe_input();
        }
    }

    return A;
}

Vector fill_vector(int len) {
    Vector b(len);

    for (int i = 0; i < len; i++) {
        std::cout << "b[" << i << "] = ";
        b[i] = safe_input();
    }

    return b;
}