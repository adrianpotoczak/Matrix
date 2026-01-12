
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
     * @brief Przelicza wspó³rzêdne 2D (x, y) na indeks tablicy 1D.
     * @param x Numer wiersza.
     * @param y Numer kolumny.
     * @return Indeks w tablicy liniowej.
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