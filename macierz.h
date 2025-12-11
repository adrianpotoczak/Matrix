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

};
