#include <iostream>
#include <cstdlib>
#include <ctime>
#include "macierz.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    cout << "Konstruktor macierz(int n) - tworzenie macierzy 2x2:" << endl;
    macierz m1(2);
    cout << m1;

    cout << "Test konstruktora kopiujacego: macierz m2(m1)" << endl;
    macierz m2(m1);
    cout << "Oryginal (m1):" << endl << m1;
    cout << "Kopia (m2):" << endl << m2;

    cout << "Metoda alokuj(int n) - realokacja pamieci na rozmiar 5x5:" << endl;
    m1.alokuj(5);
    cout << m1;

    cout << "Metoda losuj():" << endl;
    m1.losuj();
    cout << m1;

    cout << "Metoda diagonalna(int* t):" << endl;
    int t[] = { 1, 2, 3, 4, 5 };
    m1.diagonalna(t);
    cout << m1;

    cout << "Metoda pokaz(int x, int y) - pobranie wartosci z indeksu [2][2]:" << endl;
    int wartosc = m1.pokaz(2, 2);
    cout << wartosc << endl;

    cout << "Metoda pokaz(int x, int y) - proba pobrania spoza zakresu [100][100] (zabezpieczenie):" << endl;
    int blad = m1.pokaz(100, 100);
    cout << blad << endl;

    cout << "Metoda przekatna() - macierz jednostkowa:" << endl;
    m1.przekatna();
    cout << m1;

    cout << "Metoda kolumna(int x, int* t) - wstawienie danych do kolumny o indeksie 2:" << endl;
    int daneKolumny[] = { 9, 9, 9, 9, 9 };
    m1.kolumna(2, daneKolumny);
    cout << m1;

    cout << "Metoda nad_przekatna() - 1 nad przekatna, 0 reszta:" << endl;
    m1.nad_przekatna();
    cout << m1;

    cout << "Tworzenie macierzy m3 (5x5) do dodawania:" << endl;
    macierz m3(5);
    int t2[] = { 1, 1, 1, 1, 1 };
    m3.diagonalna(t2);
    cout << m3;

    cout << "Operator+ (dodawanie m3 do m1):" << endl;
    m1 + m3;
    cout << m1;

    return 0;
}