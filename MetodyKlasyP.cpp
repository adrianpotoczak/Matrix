#include "macierz.h"
#include <cstdlib>

 /**
  * @brief Przelicza wspó³rzêdne 2D na indeks tablicy jednowymiarowej.
  * * Metoda pomocnicza u¿ywana wewnêtrznie do mapowania wierszy i kolumn
  * na p³ask¹ strukturê pamiêci.
  * * @param x Numer wiersza.
  * @param y Numer kolumny.
  * @return Indeks elementu w tablicy `dane`.
  */
int macierz::indeks(int x, int y) const {
    return x * n + y;
}

/**
 * @brief Konstruktor tworz¹cy macierz o zadanym wymiarze.
 * * Alokuje pamiêæ dla tablicy o rozmiarze n*n. Jeœli n <= 0,
 * tworzy pust¹ macierz (wskaŸnik null).
 * * @param n Wymiar macierzy (liczba wierszy i kolumn).
 */
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

/**
 * @brief Konstruktor kopiuj¹cy.
 * * Tworzy g³êbok¹ kopiê obiektu, alokuj¹c now¹ pamiêæ i kopiuj¹c
 * zawartoœæ tablicy ze Ÿród³owej macierzy `m`.
 * * @param m Referencja do macierzy, która ma zostaæ skopiowana.
 */
macierz::macierz(const macierz& m) : n(m.n) {
    if (m.n > 0) {
        dane = std::make_unique<int[]>(n * n);
        std::copy(m.dane.get(), m.dane.get() + (n * n), dane.get());
    }
    else {
        n = 0;
        dane = nullptr;
    }
}

/**
 * @brief Zmienia rozmiar macierzy (realokacja).
 * * Usuwa poprzedni¹ zawartoœæ i alokuje now¹ pamiêæ dla zadanego wymiaru.
 * * @param n Nowy wymiar macierzy.
 * @return Referencja do bie¿¹cego obiektu (`*this`).
 */
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

/**
 * @brief Pobiera wartoœæ elementu macierzy.
 * * Zwraca wartoœæ znajduj¹c¹ siê w wierszu x i kolumnie y.
 * Posiada zabezpieczenie przed wyjœciem poza zakres.
 * * @param x Numer wiersza.
 * @param y Numer kolumny.
 * @return Wartoœæ elementu lub 0, jeœli indeksy s¹ nieprawid³owe.
 */
int macierz::pokaz(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return dane[indeks(x, y)];
    }
    return 0;
}

/**
 * @brief Wype³nia macierz losowymi liczbami.
 * * Ustawia w ka¿dym polu macierzy losow¹ wartoœæ z zakresu od 0 do 9.
 * * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::losuj() {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] = std::rand() % 10;
        }
    }
    return *this;
}

/**
 * @brief Ustawia wartoœci na g³ównej przek¹tnej.
 * * Zeruje ca³¹ macierz, a nastêpnie wpisuje wartoœci z tablicy `t`
 * na g³ówn¹ przek¹tn¹ (indeksy [0,0], [1,1] itd.).
 * * @param t WskaŸnik na tablicê wartoœci do wpisania na przek¹tn¹.
 * @return Referencja do bie¿¹cego obiektu.
 */
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

/**
 * @brief Wype³nia wskazan¹ kolumnê wartoœciami.
 * * Wpisuje wartoœci z tablicy `t` do kolumny o indeksie `x`.
 * * @param x Indeks kolumny do zmodyfikowania.
 * @param t WskaŸnik na tablicê wartoœci.
 * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::kolumna(int x, int* t) {
    if (n > 0 && dane != nullptr && x >= 0 && x < n) {
        for (int i = 0; i < n; i++) {
            dane[indeks(i, x)] = t[i];
        }
    }
    return *this;
}

/**
 * @brief Tworzy macierz jednostkow¹.
 * * Zeruje macierz i ustawia jedynki na g³ównej przek¹tnej.
 * * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::przekatna() {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            dane[indeks(i, i)] = 1;
        }
    }
    return *this;
}

/**
 * @brief Wype³nia obszar nad g³ówn¹ przek¹tn¹.
 * * Ustawia wartoœæ 1 dla wszystkich elementów, gdzie numer kolumny
 * jest wiêkszy od numeru wiersza. Pozosta³e elementy (w tym przek¹tna) s¹ zerowane.
 * * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::nad_przekatna() {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > i) {
                    dane[indeks(i, j)] = 1;
                }
                else {
                    dane[indeks(i, j)] = 0;
                }
            }
        }
    }
    return *this;
}

/**
 * @brief Operator dodawania innej macierzy.
 * * Dodaje wartoœci z macierzy `m` do bie¿¹cej macierzy (element do elementu).
 * Modyfikuje bie¿¹cy obiekt.
 * * @param m Macierz, której wartoœci zostan¹ dodane.
 * @return Referencja do bie¿¹cego (zmodyfikowanego) obiektu.
 */
macierz& macierz::operator+(macierz& m) {
    if (n > 0 && dane != nullptr && m.n == n) {
        for (int i = 0; i < n * n; i++) {
            dane[i] += m.dane[i];
        }
    }
    return *this;
}

/**
 * @brief Operator odejmowania skalarnego.
 * * Odejmuje liczbê ca³kowit¹ `a` od ka¿dego elementu macierzy.
 * * @param a Wartoœæ do odjêcia.
 * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::operator-(int a) {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] -= a;
        }
    }
    return *this;
}

/**
 * @brief Operator inkrementacji postfiksowej.
 * * Zwiêksza wartoœæ ka¿dego elementu macierzy o 1.
 * * @param int Parametr nieu¿ywany (oznacza wersjê postfiksow¹).
 * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::operator++(int) {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i]++;
        }
    }
    return *this;
}

/**
 * @brief Operator += (dodawanie skalarne).
 * * Dodaje liczbê ca³kowit¹ `a` do ka¿dego elementu macierzy.
 * * @param a Wartoœæ do dodania.
 * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::operator+=(int a) {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] += a;
        }
    }
    return *this;
}

/**
 * @brief Operator *= (mno¿enie skalarne).
 * * Mno¿y ka¿dy element macierzy przez liczbê ca³kowit¹ `a`.
 * * @param a Mno¿nik.
 * @return Referencja do bie¿¹cego obiektu.
 */
macierz& macierz::operator*=(int a) {
    if (n > 0 && dane != nullptr) {
        for (int i = 0; i < n * n; i++) {
            dane[i] *= a;
        }
    }
    return *this;
}

/**
 * @brief Operator porównania wiêkszoœci.
 * * Sprawdza, czy ka¿dy element bie¿¹cej macierzy jest œciœle wiêkszy
 * od odpowiadaj¹cego mu elementu macierzy `m`.
 * * @param m Macierz do porównania.
 * @return true, jeœli wszystkie elementy s¹ wiêksze, false w przeciwnym razie.
 */
bool macierz::operator>(const macierz& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++) {
        if (dane[i] <= m.dane[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Globalny operator mno¿enia liczby przez macierz.
 * * Tworzy now¹ macierz bêd¹c¹ wynikiem przemno¿enia ka¿dego elementu
 * macierzy `m` przez skalar `a`. Nie modyfikuje macierzy wejœciowej `m`.
 * * @param a Liczba ca³kowita (mno¿nik).
 * @param m Macierz Ÿród³owa.
 * @return Nowy obiekt macierzy zawieraj¹cy wynik mno¿enia.
 */
macierz operator*(int a, macierz& m) {
    macierz wynik(m.n);
    if (m.n > 0 && m.dane != nullptr) {
        for (int i = 0; i < m.n * m.n; i++) {
            wynik.dane[i] = m.dane[i] * a;
        }
    }
    return wynik;
}

/**
 * @brief Operator strumieniowy wyjœcia.
 * * Pozwala wypisaæ zawartoœæ macierzy na standardowe wyjœcie (np. std::cout).
 * Wypisuje macierz wierszami.
 * * @param o Strumieñ wyjœciowy.
 * @param m Macierz do wypisania.
 * @return Referencja do strumienia (umo¿liwia ³añcuchowanie).
 */
std::ostream& operator<<(std::ostream& o, const macierz& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.dane[i * m.n + j] << " ";
        }
        o << std::endl;
    }
    return o;
}