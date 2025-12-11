#include "macierz.h"

matrix::matrix(int n) {
    this->n = n;

    if (n > 0) {
        dane = std::make_unique<int[]>(n * n);
    }
    else {
        this->n = 0;
        dane = nullptr;
    }
}