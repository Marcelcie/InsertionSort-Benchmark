#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "sorting.h"

using namespace std;

void (*generator[3])(int[], int) = { generateRandom, generateSorted, generateSortedReversed };

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    ofstream plik("wyniki.txt", ios::app);

    int n, rodzaj_sortowania;
    const int LICZBA_PROB = 100;

    cout << "Podaj rozmiar tablicy: ";
    cin >> n;
    cout << "Wybierz typ danych (0-Losowe, 1-Rosnace, 2-Malejace): ";
    cin >> rodzaj_sortowania;

    if (rodzaj_sortowania < 0 || rodzaj_sortowania > 2) {
        cout << "Bledny wybor!" << endl;
        return 1;
    }

    Stats sumClassic, sumBinary, sumLinearMirror;
    vector<int> working;

    for (int i = 0; i < LICZBA_PROB; i++) {
        vector<int> original(n);
        generator[rodzaj_sortowania](original.data(), n);

        working = original;
        auto s1 = insertionSortClassic(working.data(), n);
        sumClassic.czas += s1.czas;
        sumClassic.porownania += s1.porownania;
        sumClassic.przesuniecia += s1.przesuniecia;

        working = original;
        auto s4 = insertionSortBinary(working.data(), n);
        sumBinary.czas += s4.czas;
        sumBinary.porownania += s4.porownania;
        sumBinary.przesuniecia += s4.przesuniecia;

        working = original;
        auto s5 = insertionSortLinearMirror(working.data(), n);
        sumLinearMirror.czas += s5.czas;
        sumLinearMirror.porownania += s5.porownania;
        sumLinearMirror.przesuniecia += s5.przesuniecia;
    }

    if (isSorted(working.data(), n)) cout << "\nTablica posortowana prawidlowo.\n";

    cout << "Srednie wyniki (n=" << n << "):\n";
    cout << "Classic: " << sumClassic.czas / LICZBA_PROB << " us\n";
    cout << "Binary: " << sumBinary.czas / LICZBA_PROB << " us\n";
    cout << "Mirror: " << sumLinearMirror.czas / LICZBA_PROB << " us\n";

    return 0;
}