#include <iostream>

#include "tests/tests.h"

void run_tests() {
    std::cout << "============= TESTS STARTED ==========\n";
    first_test();
    second_test();
    third_test();
    std::cout << "\n============= TESTS ENDED =============\n";
}

int main() {
    run_tests();
    return 0;
}