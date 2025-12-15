#include <iostream>
#include <cstdlib>
#include <ctime>
#include "macierz.h"

using namespace std;

int main() {
    srand(time(NULL));
    cout << "Konstruktor macierz(int n) - tworzenie macierzy 2x2:" << endl;
    macierz m1(2);
    cout << m1;

    cout << "--- 3. Test konstruktora kopiujacego: macierz m2(m1) ---" << endl;
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

    return 0;
}