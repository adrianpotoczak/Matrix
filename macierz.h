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

    macierz(void);
    macierz(int n, int* t);
    ~macierz(void);
	macierz& wstaw(int x, int y, int wartosc);
    macierz& dowroc(void);
    macierz& losuj(int x);
};
