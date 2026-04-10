#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>

struct Stats {
    long long czas = 0;
    long long przesuniecia = 0;
    long long porownania = 0;
};

// Prototypy funkcji sortujących
Stats insertionSortClassic(int T[], int n);
Stats insertionSortBinary(int T[], int n);
Stats insertionSortLinearMirror(int T[], int n);

// Funkcje pomocnicze
bool isSorted(const int T[], size_t n);
void generateRandom(int T[], int n);
void generateSorted(int T[], int n);
void generateSortedReversed(int T[], int n);

#endif