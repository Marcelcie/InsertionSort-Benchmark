#include "sorting.h"
#include <chrono>
#include <algorithm>
#include <ctime>

using namespace std;

bool isSorted(const int T[], size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (T[i - 1] > T[i]) return false;
    }
    return true;
}

void generateRandom(int T[], int n) {
    for (int i = 0; i < n; i++) T[i] = rand() % 10000 + 1;
}

void generateSorted(int T[], int n) {
    for (int i = 0; i < n; i++) T[i] = i;
}

void generateSortedReversed(int T[], int n) {
    for (int i = 0; i < n; i++) T[i] = n - i;
}

Stats insertionSortClassic(int T[], int n) {
    Stats s;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int x = T[i];
        int j = i - 1;
        while (j >= 0 && T[j] > x) {
            T[j + 1] = T[j];
            j--;
            s.porownania++;
            s.przesuniecia++;
        }
        if (j >= 0) s.porownania++;
        T[j + 1] = x;
    }
    auto stop = chrono::high_resolution_clock::now();
    s.czas = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return s;
}

Stats insertionSortLinearMirror(int T[], int n) {
    Stats s;
    auto start = chrono::high_resolution_clock::now();
    for (int i = n - 2; i >= 0; i--) {
        int x = T[i];
        int j = i + 1;
        while (j < n && T[j] < x) {
            T[j - 1] = T[j];
            j++;
            s.porownania++;
            s.przesuniecia++;
        }
        if (j < n) s.porownania++;
        T[j - 1] = x;
    }
    auto stop = chrono::high_resolution_clock::now();
    s.czas = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return s;
}

Stats insertionSortBinary(int T[], int n) {
    Stats s;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int x = T[i];
        int left = 0, right = i;
        while (left < right) {
            int mid = left + (right - left) / 2;
            s.porownania++;
            if (T[mid] <= x) left = mid + 1;
            else right = mid;
        }
        for (int j = i; j > left; j--) {
            T[j] = T[j - 1];
            s.przesuniecia++;
        }
        T[left] = x;
    }
    auto stop = chrono::high_resolution_clock::now();
    s.czas = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return s;
}