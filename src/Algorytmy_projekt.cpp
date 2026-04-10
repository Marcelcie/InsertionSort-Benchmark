#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Stats {
    long long czas = 0;       // czas w mikrosekundach
    long long przesuniecia = 0;    // liczba przestawień
    long long porownania = 0;       // liczba porównań
};
bool isSorted(const int T[], size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (T[i - 1] > T[i]) {
            return false;
        }
    }
    return true;
}

// Generowanie danych losowych
void generateRandom(int T[], int n) {
    for (int i = 0; i < n; i++) {
        T[i] = rand() % 10000 + 1;
    }
}

// Generowanie danych posortowanych rosnąco
void generateSorted(int T[], int n) {
    for (int i = 0; i < n; i++) {
        T[i] = i;
    }
}

// Generowanie danych posortowanych malejaco
void generateSortedReversed(int T[], int n) {
    for (int i = 0; i < n; i++) {
        T[i] = n - i;
    }
}

// Sortowanie przez wstawianie - wersja klasyczna
Stats insertionSortClassic(int T[], int n) {
    Stats s = { 0, 0, 0 };
    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    s.czas = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return s;
}

// Sortowanie przez wstawianie - przez szukanie miejsca liniowo
Stats insertionSortLinear(int T[], int n) {
    Stats s = { 0, 0, 0 };
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++) {
        int x = T[i];
        int pos = i;

        while (pos > 0) {
            s.porownania++;
            if (T[pos - 1] > x) {
                pos--;
            }
            else {
                break;
            }
        }
        for (int j = i; j > pos; j--) {
            T[j] = T[j - 1];
            s.przesuniecia++;
        }

        T[pos] = x;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    s.czas = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return s;
}

Stats insertionSortLinearMirror(int T[], int n) {
    Stats s = { 0, 0, 0 };
    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    s.czas = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return s;
}
// Sortowanie przez wstawianie binarne
 Stats insertionSortBinary(int T[], int n) {
     Stats s = { 0,0,0 };
     auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int x = T[i];

        // Wyszukiwanie binarne miejsca do wstawienia
        int left = 0;
        int right = i;
        while (left < right) {
            int mid = (left + right) / 2;
            s.porownania++;
            if (T[mid] <= x) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // Przesuwanie elementów
        for (int j = i; j > left; j--) {
            T[j] = T[j - 1];
            s.przesuniecia++;
        }
        // Wstawienie elementu
        T[left] = x;
    }
    auto stop = std::chrono:: high_resolution_clock::now();
    s.czas = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return s;
}
 void (*generator[3])(int[], int) = { generateRandom,generateSorted,generateSortedReversed };
// Pomiar czasu działania
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
        Stats sumClassic = { 0,0,0 };
        Stats sumLinear = { 0,0,0 };
        Stats sumClassicMirror = { 0,0,0 };
        Stats sumBinary = { 0,0,0 };
        Stats sumLinearMirror = { 0,0,0 };

        vector<int>working;

        for (int i = 0; i < LICZBA_PROB; i++) {
            vector<int> original(n);
            generator[rodzaj_sortowania](original.data(), n);

            // 1. Klasyczne
            working = original;
            auto s1 = insertionSortClassic(working.data(), n);
            sumClassic.czas += s1.czas;
            sumClassic.porownania += s1.porownania;
            sumClassic.przesuniecia += s1.przesuniecia;

            // 2. Liniowe (jeśli dopiszesz logikę, teraz używamy Classic dla testu)
            working = original;
            auto s2 = insertionSortLinear(working.data(), n);
            sumLinear.czas += s2.czas;
            sumLinear.porownania += s2.porownania;
            sumLinear.przesuniecia += s2.przesuniecia;

            // 3. Binarne
            working = original;
            auto s4 = insertionSortBinary(working.data(), n);
            sumBinary.czas += s4.czas;
            sumBinary.porownania += s4.porownania;
            sumBinary.przesuniecia += s4.przesuniecia;

            // 4. Liniowe Lustro
            working = original;
            auto s5 = insertionSortLinearMirror(working.data(), n);
            sumLinearMirror.czas += s5.czas;
            sumLinearMirror.porownania += s5.porownania;
            sumLinearMirror.przesuniecia += s5.przesuniecia;
        }

            plik << endl;
            if (isSorted(working.data(), n)) {
                cout << "Tablica zostala posortowana prawidlowo";
            }
            else {
                cout << "Tablica nie została prawidłowo posortowana";
            }
            cout << "\nSrednie wyniki po " << 100 << " pomiarach dla tablicy o rozmiarze " << n << ":\n";

            cout << "\n--- Klasyczne ---\n";
            cout << "Czas: " << sumClassic.czas / 100 << " us\n";
            cout << "Porownania: " << sumClassic.porownania / 100 << "\n";
            cout << "przesuniecia: " << sumClassic.przesuniecia / 100 << "\n";

            cout << "\n--- Liniowe ---\n";
            cout << "Czas: " << sumLinear.czas / 100 << " us\n";
            cout << "Porownania: " << sumLinear.porownania / 100 << "\n";
            cout << "przesuniecia: " << sumLinear.przesuniecia / 100 << "\n";

            cout << "\n--- KlasyczneLustro ---\n";
            cout << "Czas: " << sumClassicMirror.czas / 100 << " us\n";
            cout << "Porownania: " << sumClassicMirror.porownania / 100 << "\n";
            cout << "przesuniecia: " << sumClassicMirror.przesuniecia / 100 << "\n";

            cout << "\n--- LinioweLustro ---\n";
            cout << "Czas: " << sumLinearMirror.czas / 100 << " us\n";
            cout << "Porownania: " << sumLinearMirror.porownania / 100 << "\n";
            cout << "przesuniecia: " << sumLinearMirror.przesuniecia / 100 << "\n";

            cout << "\n--- Binarne ---\n";
            cout << "Czas: " << sumBinary.czas / 100 << " us\n";
            cout << "Porownania: " << sumBinary.porownania / 100 << "\n";
            cout << "przesuniecia: " << sumBinary.przesuniecia / 100 << "\n";

            // wrzucanie wynikow do pliku .txt
            plik << "Wyniki dla n = " << n << ", h = " << 100 << "\n";
            plik << "Classic;" << (sumClassic.czas / 100) << ";"
                << (sumClassic.porownania / 100) << ";"
                << (sumClassic.przesuniecia / 100) << ";\n";

            plik << "Linear;" << (sumLinear.czas / 100) << ";"
                << (sumLinear.porownania / 100) << ";"
                << (sumLinear.przesuniecia / 100) << ";\n";

            plik << "ClassicMirror;" << (sumClassicMirror.czas / 100) << ";"
                << (sumClassicMirror.porownania / 100) << ";"
                << (sumClassicMirror.przesuniecia / 100) << ";\n";

            plik << "LinearMirror;" << (sumLinearMirror.czas / 100) << ";"
                << (sumLinearMirror.porownania / 100) << ";"
                << (sumLinearMirror.przesuniecia / 100) << ";\n";

            plik << "Binary;" << (sumBinary.czas / 100) << ";"
                << (sumBinary.porownania / 100) << ";"
                << (sumBinary.przesuniecia / 100) << ";\n";
            plik.close();
        return 0;
