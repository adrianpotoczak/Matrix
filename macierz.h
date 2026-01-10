#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

class macierz {
private:
    int n;
    std::unique_ptr<int[]> dane;
    int indeks(int x, int y) const;

public:
    macierz(int n);
    macierz(macierz& m);
    macierz& alokuj(int n);
    int pokaz(int x, int y);
    macierz& losuj();
    macierz& diagonalna(int* t);
    macierz& kolumna(int x, int* t);
    macierz& przekatna();
    macierz& nad_przekatna();
    macierz& operator+(macierz& m);
    macierz& operator-(int a);
    macierz& operator++(int);
    macierz& operator+=(int a);
    macierz& operator*=(int a);
    bool operator>(const macierz& m);

    friend macierz operator*(int a, macierz& m);
    friend std::ostream& operator<<(std::ostream& o, const macierz& m);
};