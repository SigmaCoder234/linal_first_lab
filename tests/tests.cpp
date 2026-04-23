#include <iostream>
#include <chrono>

#include "matrix/matrix.h"
#include "decompositions/gauss.h"
#include "decompositions/LU.h"
#include "math_ops/math_ops.h"
#include "tests/tests.h"

void first_test() {
    std::cout << "\n============= FIRST TEST =============\n";

    int size[] = {100, 200, 500, 1000};
    DynamicArray<int> sizes(size, 4);

    for (int n : sizes) {
        Matrix A = create_matrix(n);
        Vector b = create_vector(n);

        // гаусово разложение с опорным элементом
        auto start = std::chrono::high_resolution_clock::now();
        gauss_with_pivot(A, b);
        auto end = std::chrono::high_resolution_clock::now();
        double time_with_pivot = std::chrono::duration<double>(end - start).count();

        // гаусово разложение без опорного элемента
        start = std::chrono::high_resolution_clock::now();
        gauss_without_pivot(A, b);
        end = std::chrono::high_resolution_clock::now();
        double time_without_pivot = std::chrono::duration<double>(end - start).count();

        // разложение матрицы LU
        Matrix L(n);
        Matrix U(n);
        start = std::chrono::high_resolution_clock::now();
        lu_decomposition(A, L, U);
        end = std::chrono::high_resolution_clock::now();
        double time_LU_decompos  = std::chrono::duration<double>(end - start).count();

        // решение системы с помощью LU разложения
        start = std::chrono::high_resolution_clock::now();
        solve_lu(L, U, b);
        end = std::chrono::high_resolution_clock::now();
        double time_LU_solve  = std::chrono::duration<double>(end - start).count();

        double lu_total = time_LU_decompos + time_LU_solve;

        std::cout << "n = " << n << "\n";
        std::cout << "Gauss with pivot: " << time_with_pivot << "\n";
        std::cout << "Gauss without pivot: " << time_without_pivot << "\n";
        std::cout << "LU decomp: " << time_LU_decompos << "\n";
        std::cout << "LU solve: " << time_LU_solve << "\n";
        std::cout << "LU total: " << lu_total << "\n";
        std::cout << "--------------------------\n";
    }
}

void second_test() {
    std::cout << "\n============= SECOND TEST =============\n";

    int n = 500;
    int size[] = {1, 10, 100};
    DynamicArray<int> sizes(size, 3);

    Matrix A = create_matrix(n);
    for (int k : sizes) {
        DynamicArray<Vector> b_vectors(k);

        for (int i = 0; i < k; i++) {
            b_vectors[i] = create_vector(n);
        }

        // gauss with pivot test
        auto start = std::chrono::high_resolution_clock::now();

        for (auto &b : b_vectors) {
            gauss_with_pivot(A, b);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double time_with_pivot  = std::chrono::duration<double>(end - start).count();

        // LU test
        start = std::chrono::high_resolution_clock::now();

        Matrix L(n), U(n);

        lu_decomposition(A, L, U);

        for (auto &b : b_vectors) {
            solve_lu(L, U, b);
        }

        end = std::chrono::high_resolution_clock::now();
        double time_LU  = std::chrono::duration<double>(end - start).count();

        std::cout << "k = " << k << "\n";
        std::cout << "Gauss with pivot: " << time_with_pivot << "\n";
        std::cout << "LU total: " << time_LU << "\n";
        std::cout << "--------------------------\n";
    }
}

void third_test() {
    std::cout << "\n============= THIRD TEST =============\n";

    int size[] = {5, 10, 15};
    DynamicArray<int> sizes(size, 3);

    for (int n : sizes) {
        Matrix G = create_gilbert_matrix(n);
        Vector x_exact(n);
        for (int i = 0; i < n; i++) {
            x_exact[i] = 1.0;
        }

        Vector b = matrix_by_vector(G, x_exact);

        // решение системы каждым разложением
        Vector x_gauss(n);
        Vector x_with_pivot(n);
        Vector x_lu(n);

        // гаусово разложение без опорного элемента
        bool gauss = true;
        try {
            x_gauss = gauss_without_pivot(G, b);
        }

        catch (...) {
            gauss = false;
        }

        // гаусово разложение с опорным элементом
        bool with_pivot = true;
        try {
            x_with_pivot = gauss_with_pivot(G, b);
        }

        catch (...) {
            with_pivot = false;
        }

        // LU разложение
        bool lu = true;
        Matrix L(n), U(n);
        try {
            lu_decomposition(G, L, U);
            x_lu = solve_lu(L, U, b);
        }

        catch (...) {
            lu = false;
        }

        // вывод
        std::cout << "n = " << n << "\n";
        if (gauss) {
            std::cout << "Gauss error: " << rel_error(x_gauss, x_exact) << "\n";
            std::cout << "Gauss residual: " << calc_res(G, x_gauss, b) << "\n";
        } else {
            std::cout << "Gauss failed\n";
        }

        if (with_pivot) {
            std::cout << "Gauss with pivot error: " << rel_error(x_with_pivot, x_exact) << "\n";
            std::cout << "Gauss with pivot residual: " << calc_res(G, x_with_pivot, b) << "\n";
        } else {
            std::cout << "Gauss with pivot failed\n";
        }

        if (lu) {
            std::cout << "LU error: " << rel_error(x_lu, x_exact) << "\n";
            std::cout << "LU residual: " << calc_res(G, x_lu, b) << "\n";
        } else {
            std::cout << "LU failed\n";
        }

        std::cout << "--------------------------\n";
    }
}