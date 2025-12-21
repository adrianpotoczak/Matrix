/**
 * @file macierz.h
 * @brief Plik nag³ówkowy definicji klasy macierz.
 */

#include <iostream>
#include <memory>    
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

 /**
  * @brief Klasa reprezentuj¹ca macierz kwadratow¹ liczb ca³kowitych.
  * * Klasa zarz¹dza pamiêci¹ dynamiczn¹ za pomoc¹ std::unique_ptr i udostêpnia
  * szereg operacji matematycznych oraz manipulacyjnych na macierzach.
  */
class macierz {
private:
    int n; ///< Wymiar macierzy (n x n).
    std::unique_ptr<int[]> dane; ///< WskaŸnik na tablicê jednowymiarow¹ przechowuj¹c¹ elementy macierzy.

    /**
     * @brief Pomocnicza metoda do obliczania indeksu w tablicy jednowymiarowej.
     * @param x Wspó³rzêdna kolumny.
     * @param y Wspó³rzêdna wiersza.
     * @return Indeks elementu w tablicy dane.
     */
    int indeks(int x, int y) const;

public:

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
};