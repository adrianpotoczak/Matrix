/**
 * @file MetodyKlasyNiep.cpp
 * @brief Implementacja metod klasy macierz.
 */

#include "macierz.h"
#include <cstdlib> // dla rand()

 /**
  * @brief Konstruktor domyœlny.
  * Inicjalizuje macierz o rozmiarze 0.
  */
macierz::macierz(void) {
    n = 0;
};

/**
 * @brief Konstruktor parametryczny.
 * Alokuje pamiêæ i kopiuje dane z tablicy wejœciowej.
 * @param n Wymiar macierzy.
 * @param t WskaŸnik na tablicê z danymi.
 */
macierz::macierz(int n, int* t) {
    this->n = n;
    dane = std::make_unique<int[]>(n * n);
    for (int i = 0; i < n * n; i++) {
        dane[i] = t[i];
    }
}

/**
 * @brief Destruktor.
 * Pamiêæ jest zwalniana automatycznie przez std::unique_ptr.
 */
macierz::~macierz(void) {
}

/**
 * @brief Wstawia wartoœæ do macierzy po sprawdzeniu zakresu indeksów.
 * @param x Wspó³rzêdna kolumny.
 * @param y Wspó³rzêdna wiersza.
 * @param wartosc Wartoœæ do wstawienia.
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && n > y && y >= 0 && x < n) { // Poprawiono warunek logiczny z oryginalnego kodu dla bezpieczeñstwa
        dane[y * n + x] = wartosc;
    }
    return *this;
};

/**
 * @brief Dokonuje transpozycji macierzy.
 * Wykorzystuje tymczasow¹ tablicê do zamiany wierszy z kolumnami.
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::dowroc(void) {
    auto temp = std::make_unique<int[]>(n * n);

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            // Zapis do temp: wiersze staj¹ siê kolumnami
            temp[x * n + y] = dane[y * n + x];
        }
    }
    dane = std::move(temp);

    return *this;
};

/**
 * @brief Zeruje macierz, a nastêpnie wstawia x losowych wartoœci.
 * @param x Liczba losowych komórek do wype³nienia.
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::losuj(int x) {
    for (int i = 0; i < n * n; i++) dane[i] = 0;

    for (int i = 0; i < x; i++) {
        int los_x = rand() % n;
        int los_y = rand() % n;
        int wartosc = rand() % 10;

        wstaw(los_x, los_y, wartosc);
    }
    return *this;
}

/**
 * @brief Ustawia wartoœci na zadanej przek¹tnej (k).
 * @param k Przesuniêcie przek¹tnej (0: g³ówna, >0: nad, <0: pod).
 * @param t Tablica wartoœci do wstawienia.
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::diagonalna_k(int k, int* t) {

    for (int i = 0; i < n * n; i++) dane[i] = 0;

    if (k == 0) {
        for (int i = 0; i < n; i++) wstaw(i, i, t[i]);
    }
    else if (k > 0) {
        for (int i = 0; i < n - k; i++) {
            wstaw(i + k, i, t[i]);
        }
    }
    else {
        int shift = -k;
        for (int i = 0; i < n - shift; i++) {
            wstaw(i, i + shift, t[i]);
        }
    }
    return *this;
}

/**
 * @brief Wype³nia konkretny wiersz danymi z tablicy.
 * @param y Indeks wiersza.
 * @param t Tablica danych.
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::wiersz(int y, int* t) {
    if (y >= 0 && y < n) {
        for (int x = 0; x < n; x++) {
            wstaw(x, y, t[x]);
        }
    }
    return *this;
}

/**
 * @brief Tworzy macierz trójk¹tn¹ doln¹ (1 pod przek¹tn¹, 0 w reszcie).
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::pod_przekatna(void) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (y > x) wstaw(x, y, 1);
            else wstaw(x, y, 0);
        }
    }
    return *this;
}

/**
 * @brief Wype³nia macierz wzorem szachownicy (0 i 1).
 * @return Referencja do obiektu macierzy.
 */
macierz& macierz::szachownica(void) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if ((x + y) % 2 != 0) wstaw(x, y, 1);
            else wstaw(x, y, 0);
        }
    }
    return *this;
}

/**
 * @brief Operator mno¿enia macierzy przez macierz.
 * Wykonuje mno¿enie wiersz przez kolumnê.
 * @param m Druga macierz.
 * @return Referencja do zaktualizowanej macierzy.
 */
macierz& macierz::operator*(macierz& m) {
    if (this->n != m.n) return *this;

    auto wynik = std::make_unique<int[]>(n * n);

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int suma = 0;
            for (int k = 0; k < n; k++) {
                suma += dane[y * n + k] * m.dane[k * n + x];
            }
            wynik[y * n + x] = suma;
        }
    }

    dane = std::move(wynik);
    return *this;
}

/**
 * @brief Operator mno¿enia macierzy przez skalar (modyfikuje obiekt).
 * @param a Wartoœæ skalara.
 * @return Referencja do macierzy.
 */
macierz& macierz::operator*(int a) {
    for (int i = 0; i < n * n; i++) {
        dane[i] *= a;
    }
    return *this;
}

/**
 * @brief Operator dodawania skalara do macierzy (friend).
 * Tworzy now¹ macierz z wynikiem.
 * @param a Skalar.
 * @param m Macierz.
 * @return Nowy obiekt macierzy.
 */
macierz operator+(int a, macierz& m) {
    // Uwaga: Wymaga odpowiedniego konstruktora w klasie macierz
    // Zak³adamy istnienie konstruktora przyjmuj¹cego rozmiar lub inicjalizacjê zerami
    int* temp = new int[m.n * m.n](); // Inicjalizacja zerami dla bezpieczeñstwa
    macierz nowa(m.n, temp);
    delete[] temp;

    for (int y = 0; y < m.n; y++) {
        for (int x = 0; x < m.n; x++) {
            int stary = m.dane[y * m.n + x];
            nowa.wstaw(x, y, a + stary);
        }
    }
    return nowa;
}

/**
 * @brief Operator odejmowania elementów macierzy od skalara (friend).
 * Wynik = a - element_macierzy.
 * @param a Skalar (odjemna).
 * @param m Macierz (odjemnik).
 * @return Nowy obiekt macierzy.
 */
macierz operator-(int a, macierz& m) {
    int* temp = new int[m.n * m.n]();
    macierz nowa(m.n, temp);
    delete[] temp;

    for (int y = 0; y < m.n; y++) {
        for (int x = 0; x < m.n; x++) {
            int stary = m.dane[y * m.n + x];
            nowa.wstaw(x, y, a - stary);
        }
    }
    return nowa;
}

/**
 * @brief Operator dekrementacji postfiksowej.
 * Zmniejsza ka¿dy element o 1.
 * @return Referencja do macierzy.
 */
macierz& macierz::operator--(int) {
    for (int i = 0; i < n * n; i++) {
        dane[i]--;
    }
    return *this;
}

/**
 * @brief Operator odejmowania skalara od macierzy .
 * @param a Wartoœæ do odjêcia.
 * @return Referencja do macierzy.
 */
macierz& macierz::operator-=(int a) {
    for (int i = 0; i < n * n; i++) {
        dane[i] -= a;
    }
    return *this;
}

/**
 * @brief Operator funkcyjny.
 * Dodaje czêœæ ca³kowit¹ liczby double do ka¿dego elementu.
 * @param d Liczba double.
 * @return Referencja do macierzy.
 */
macierz& macierz::operator()(double d) {
    int dodatek = (int)d;
    for (int i = 0; i < n * n; i++) {
        dane[i] += dodatek;
    }
    return *this;
}

/**
 * @brief Operator porównania równoœci.
 * @param m Macierz do porównania.
 * @return true jeœli wymiary i elementy s¹ identyczne.
 */
bool macierz::operator==(const macierz& m) {
    if (this->n != m.n) return false;

    for (int i = 0; i < n * n; i++) {
        if (dane[i] != m.dane[i]) return false;
    }
    return true;
}

/**
 * @brief Operator mniejszoœci .
 * @param m Macierz do porównania.
 * @return true jeœli KA¯DY element this jest mniejszy od odpowiedniego elementu m.
 */
bool macierz::operator<(const macierz& m) {
    if (this->n != m.n) return false;

    for (int i = 0; i < n * n; i++) {
        if (!(dane[i] < m.dane[i])) return false;
    }
    return true;
}