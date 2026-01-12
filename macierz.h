#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

/**
 * @class macierz
 * @brief Klasa reprezentuj¹ca macierz kwadratow¹ liczb ca³kowitych.
 * * Klasa wykorzystuje inteligentne wskaŸniki (std::unique_ptr) do zarz¹dzania pamiêci¹.
 * Dane przechowywane s¹ w jednowymiarowej tablicy dla optymalizacji wydajnoœci.
 */
class macierz {
private:
    /** @brief Wymiar macierzy (liczba wierszy i kolumn). */
    int n;

    /** @brief WskaŸnik na tablicê przechowywuj¹c¹ elementy macierzy. */
    std::unique_ptr<int[]> dane;

    /**
      * @brief Pomocnicza metoda do obliczania indeksu w tablicy jednowymiarowej.
      * @param x Wspó³rzêdna kolumny.
      * @param y Wspó³rzêdna wiersza.
      * @return Indeks elementu w tablicy dane.
      */
    int indeks(int x, int y) const;

public:
    /**
      * @brief Konstruktor tworz¹cy macierz o zadanym rozmiarze.
      * @param n Wymiar macierzy (n x n).
      */
    macierz(int n);

    /**
      * @brief Konstruktor kopiuj¹cy.
      * Tworzy g³êbok¹ kopiê obiektu, alokuj¹c now¹ pamiêæ dla danych.
      * @param m Referencja do macierzy, która ma zostaæ skopiowana.
      */
    macierz(const macierz& m);

    /**
      * @brief Zmienia rozmiar macierzy (realokacja pamiêci).
      * @param n Nowy wymiar macierzy.
      * @return Referencja do zmodyfikowanego obiektu.
      */
    macierz& alokuj(int n);

    /**
      * @brief Zwraca wartoœæ elementu na pozycji (x, y).
      * @param x Numer wiersza.
      * @param y Numer kolumny.
      * @return Wartoœæ elementu lub 0, jeœli indeks jest poza zakresem.
      */
    int pokaz(int x, int y);

    /**
      * @brief Wype³nia macierz losowymi wartoœciami z zakresu 0-9.
      * @return Referencja do obiektu.
      */
    macierz& losuj();

    /**
      * @brief Zeruje macierz i wype³nia g³ówn¹ przek¹tn¹ wartoœciami z tablicy.
      * @param t WskaŸnik na tablicê liczb ca³kowitych.
      * @return Referencja do obiektu.
      */
    macierz& diagonalna(int* t);

    /**
      * @brief Wype³nia wybran¹ kolumnê danymi z tablicy.
      * @param x Indeks kolumny do uzupe³nienia.
      * @param t WskaŸnik na tablicê wartoœci.
      * @return Referencja do obiektu.
      */
    macierz& kolumna(int x, int* t);

    /**
      * @brief Tworzy macierz jednostkow¹ (1 na przek¹tnej, 0 poza ni¹).
      * Poprzednia zawartoœæ jest usuwana (zerowana).
      * @return Referencja do obiektu.
      */
    macierz& przekatna();

    /**
      * @brief Konstruktor domyœlny.
      * Tworzy pust¹ macierz o wymiarze 0.
      */
    macierz(void);

    /**
      * @brief Konstruktor parametryczny.
      * Tworzy macierz o wymiarze n i inicjalizuje j¹ danymi z tablicy t.
      * @param n Wymiar macierzy.
      * @param t WskaŸnik na tablicê wartoœci pocz¹tkowych.
      */
    macierz(int n, int* t);

    /**
      * @brief Destruktor.
      */
    ~macierz(void);

    /**
      * @brief Wstawia wartoœæ do macierzy na podanych wspó³rzêdnych.
      * @param x Numer kolumny (0 do n-1).
      * @param y Numer wiersza (0 do n-1).
      * @param wartosc Wartoœæ do wstawienia.
      * @return Referencja do bie¿¹cego obiektu (umo¿liwia ³añcuchowanie).
      */
    macierz& wstaw(int x, int y, int wartosc);

    /**
      * @brief Transponuje macierz (zamienia wiersze z kolumnami).
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& dowroc(void);

    /**
      * @brief Zeruje macierz i wstawia losowe wartoœci w losowe miejsca.
      * @param x Liczba losowych elementów do wstawienia.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& losuj(int x);

    /**
      * @brief Ustawia wartoœci na k-tej przek¹tnej.
      * Pozosta³e elementy macierzy s¹ zerowane.
      * @param k Indeks przek¹tnej (0 - g³ówna, >0 - nad g³ówn¹, <0 - pod g³ówn¹).
      * @param t Tablica wartoœci do wstawienia na przek¹tn¹.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& diagonalna_k(int k, int* t);

    /**
      * @brief Wype³nia wskazany wiersz wartoœciami z tablicy.
      * @param y Indeks wiersza do wype³nienia.
      * @param t Tablica wartoœci dla tego wiersza.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& wiersz(int y, int* t);

    /**
      * @brief Wype³nia macierz tak, aby pod g³ówn¹ przek¹tn¹ by³y jedynki, a reszta zerami.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& pod_przekatna(void);

    /**
      * @brief Wype³nia macierz wzorem szachownicy.
      * Wstawia 1, gdy suma indeksów (x+y) jest nieparzysta, w przeciwnym razie 0.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& szachownica(void);

    /**
      * @brief Mno¿enie macierzy przez macierz.
      * @param m Macierz, przez któr¹ mno¿ymy .
      * @return Referencja do bie¿¹cego obiektu (zaktualizowanego o wynik mno¿enia).
      */
    macierz& operator*(macierz& m);

    /**
      * @brief Mno¿enie wszystkich elementów macierzy przez skalar.
      * @param a Liczba ca³kowita, przez któr¹ mno¿ymy.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& operator*(int a);

    /**
      * @brief Dodawanie skalarne.
      * Tworzy now¹ macierz, nie modyfikuje argumentu m.
      * @param a Skalar dodawany do ka¿dego elementu.
      * @param m Macierz Ÿród³owa.
      * @return Nowy obiekt macierzy bêd¹cy wynikiem operacji.
      */
    friend macierz operator+(int a, macierz& m);

    /**
      * @brief Odejmowanie skalarne.
      * Tworzy now¹ macierz, nie modyfikuje argumentu m.
      * @param a Skalar (odjemna).
      * @param m Macierz Ÿród³owa (odjemnik).
      * @return Nowy obiekt macierzy bêd¹cy wynikiem operacji.
      */
    friend macierz operator-(int a, macierz& m);

    /**
      * @brief Operator dekrementacji postfiksowej.
      * Zmniejsza ka¿dy element macierzy o 1.
      * @param int Atrapa parametru dla rozró¿nienia wersji postfiksowej.
      * @return Referencja do bie¿¹cego obiektu (z wartoœciami po dekrementacji).
      */
    macierz& operator--(int);

    /**
      * @brief Operator -= (odejmowanie wartoœci od ka¿dego elementu).
      * @param a Wartoœæ odejmowana od elementów macierzy.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& operator-=(int a);

    /**
      * @brief Operator wywo³ania funkcji.
      * Dodaje czêœæ ca³kowit¹ liczby double do ka¿dego elementu macierzy.
      * @param d Liczba double do dodania.
      * @return Referencja do bie¿¹cego obiektu.
      */
    macierz& operator()(double d);

    /**
      * @brief Operator porównania równoœci.
      * Sprawdza, czy wymiary i wszystkie elementy obu macierzy s¹ identyczne.
      * @param m Macierz do porównania.
      * @return true jeœli macierze s¹ identyczne, false w przeciwnym razie.
      */
    bool operator==(const macierz& m);

    /**
      * @brief Operator mniejszoœci.
      * @param m Macierz do porównania.
      * @return true jeœli ka¿dy element tej macierzy jest mniejszy od odpowiedniego elementu macierzy m, false w przeciwnym razie.
      */
    bool operator<(const macierz& m);

    /**
      * @brief Wype³nia obszar nad g³ówn¹ przek¹tn¹ jedynkami.
      * Elementy na przek¹tnej i pod ni¹ s¹ zerowane.
      * @return Referencja do obiektu.
      */
    macierz& nad_przekatna();

    /**
      * @brief Operator dodawania macierzy (A += B).
      * Dodaje wartoœci z macierzy m do bie¿¹cej macierzy element po elemencie.
      * @param m Macierz dodawana.
      * @return Referencja do zmodyfikowanej macierzy.
      */
    macierz& operator+(macierz& m);

    /**
      * @brief Operator odejmowania liczby od macierzy.
      * Odejmuje wartoœæ 'a' od ka¿dego elementu macierzy.
      * @param a Liczba ca³kowita.
      * @return Referencja do macierzy.
      */
    macierz& operator-(int a);

    /**
      * @brief Operator inkrementacji (postfiksowy).
      * Zwiêksza wartoœæ wszystkich elementów macierzy o 1.
      * @param Parametr ignorowany (oznacza wersjê postfiksow¹).
      * @return Referencja do macierzy.
      */
    macierz& operator++(int);

    /**
      * @brief Operator += (dodawanie liczby).
      * Dodaje liczbê 'a' do ka¿dego elementu macierzy.
      * @param a Liczba ca³kowita.
      * @return Referencja do macierzy.
      */
    macierz& operator+=(int a);

    /**
      * @brief Operator *= (mno¿enie przez liczbê).
      * Mno¿y ka¿dy element macierzy przez liczbê 'a'.
      * @param a Skalar (liczba ca³kowita).
      * @return Referencja do macierzy.
      */
    macierz& operator*=(int a);

    /**
      * @brief Operator porównania wiêkszoœci (>).
      * Sprawdza, czy ka¿dy element bie¿¹cej macierzy jest wiêkszy od odpowiedniego elementu macierzy m.
      * @param m Macierz porównywana.
      * @return true jeœli A > B (ka¿dy element), false w przeciwnym razie.
      */
    bool operator>(const macierz& m);

    /**
      * @brief Operator mno¿enia liczby przez macierz (friend).
      * Tworzy now¹ macierz bêd¹c¹ wynikiem mno¿enia ka¿dego elementu m przez a.
      * @param a Liczba ca³kowita (mno¿nik).
      * @param m Macierz mno¿ona.
      * @return Nowy obiekt macierzy.
      */
    friend macierz operator*(int a, macierz& m);

    /**
      * @brief Operator strumieniowy wyjœcia (wypisywanie).
      * Pozwala na wypisanie macierzy na ekran (np. std::cout << m).
      * @param o Strumieñ wyjœciowy.
      * @param m Macierz do wypisania.
      * @return Referencja do strumienia.
      */
    friend std::ostream& operator<<(std::ostream& o, const macierz& m);
};