#include <iostream>
#include "fibonacci.h"

int main() {
    int n = fibonacci(5);

    printf("[PARENT] F(5) = %llu\n", n);
    return 0;
}