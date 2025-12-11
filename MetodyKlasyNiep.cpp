#include "macierz.h"

macierz::macierz(void) {
	n = 0;
};
macierz::macierz(int n, int* t) {
	this->n = n;
	dane = std::make_unique<int[]>(n * n);
	for (int i = 0; i < n * n; i++) {
		dane[i] = t[i];
	}
}
macierz::~macierz(void) {

}
macierz& macierz::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && n < y && y >= 0 && y < n) {
		dane[y*n+ x ] = wartosc;
    }
	return *this;
};
macierz& macierz::dowroc(void) {
	auto temp = std::make_unique<int[]>(n * n);

	for(int y =0 ; y < n; y++) {
		for(int x =0; x < n; x++) {
			dane[x * n + y] = dane[y * n + x];
		}
	}
	dane = std::move(temp);

	return *this;
};
macierz& macierz::losuj(int x) {
	for (int i = 0; i < n * n; i++) dane[i] = 0;

	for (int i = 0; i < x; i++) {
		int los_x = rand() % n;
		int los_y = rand() % n;
		int wartosc = rand() % 10;

		wstaw(los_x, los_y, wartosc);	
	}
	return *this;
}