#include "macierz.h"
#include <cstdlib>

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

macierz& macierz::alokuj(int n) {
    this->n = n;
    if (n > 0) {
        dane = std::make_unique<int[]>(n * n);
    }
    else {
        this->n = 0;
        dane = nullptr;
    }
    return *this;
}

int macierz::pokaz(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return dane[indeks(x, y)];
    }
    return 0;
}

macierz& macierz::losuj() {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] = std::rand() % 10;
        }
    }
    return *this;
}

macierz& macierz::diagonalna(int* t) {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            dane[indeks(i, i)] = t[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& o, const macierz& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.dane[i * m.n + j] << " ";
        }
        o << std::endl;
    }
    return o;
}