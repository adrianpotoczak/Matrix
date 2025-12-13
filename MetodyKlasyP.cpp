#include "macierz.h"

int macierz::indeks(int x, int y) const {
    return x * n + y;
}

macierz::macierz(int n) {
    this->n = n;
    if (n > 0) {
        dane = std::make_unique<int[]>(n * n);
    }
    else {
        this->n = 0;
        dane = nullptr;
    }
}

macierz::macierz(macierz& m) : n(m.n) {
    if (m.n > 0) {
        dane = std::make_unique<int[]>(n * n);
        std::copy(m.dane.get(), m.dane.get() + (n * n), dane.get());
    }
    else {
        n = 0;
        dane = nullptr;
    }
}