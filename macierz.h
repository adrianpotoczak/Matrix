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
    friend std::ostream& operator<<(std::ostream& o, const macierz& m);
};