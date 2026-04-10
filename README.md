# Benchmark Algorytmów Sortowania: Warianty Insertion Sort

## 📝 Opis projektu
Projekt ma na celu empiryczną analizę wydajności różnych wariantów algorytmu **Sortowania przez wstawianie (Insertion Sort)**. Program został zaimplementowany w języku C++ w formie funkcjonalnego narzędzia do pomiarów wydajnościowych.

Głównym celem było sprawdzenie, jak optymalizacje oraz charakterystyka danych wejściowych (losowe, posortowane, odwrotnie posortowane) wpływają na:
* **Czas wykonania** (w mikrosekundach),
* **Liczbę porównań** kluczy,
* **Liczbę przesunięć** elementów w tablicy.

## 💻 Specyfikacja sprzętowa
Pomiary zostały przeprowadzone na następującej konfiguracji:
* **Procesor:** AMD Ryzen 7 5700X3D (8 rdzeni, 16 wątków)
* **Karta graficzna:** NVIDIA GeForce RTX 3060
* **Pamięć RAM:** 32GB DDR4 3200mhz

## 🚀 Implementowane algorytmy
1. **Classic Insertion Sort**: Standardowa implementacja z jednoczesnym szukaniem miejsca i przesuwaniem elementów wewnątrz jednej pętli.
2. **Linear Insertion Sort**: Wariant z rozdzielonym procesem liniowego szukania miejsca wstawienia oraz przesuwania elementów.
3. **Binary Insertion Sort**: Optymalizacja wykorzystująca wyszukiwanie binarne ($O(\log n)$) do znalezienia odpowiedniego miejsca wstawienia.
4. **Linear Mirror Sort**: Wariant algorytmu rozpoczynający proces sortowania od końca tablicy (lustrzane odbicie).

## 📊 Przykład wyników (dla n = 10 000)
Dane stanowią średnią ze **100 pomiarów** przeprowadzonych w trybie **Release**.

| Algorytm | Typ danych | Czas [μs] | Porównania | Przesunięcia |
| :--- | :--- | :--- | :--- | :--- |
| **Classic** | Losowe | ~63 800 | ~25 000 000 | ~25 000 000 |
| **Binary** | Losowe | ~79 000 | **~119 000** | ~25 000 000 |
| **Classic** | Posortowane | **~40** | 9 999 | 0 |

> **Wniosek:** Wyszukiwanie binarne drastycznie redukuje liczbę porównań, ale ze względu na koszt operacji na pamięci i tę samą liczbę przesunięć, czas całkowity może być zbliżony do wersji klasycznej lub nieco wyższy przez narzut logiki wyszukiwania.

## 📁 Struktura plików
* **src/Algorytmy_projekt.cpp**: Główny i jedyny plik źródłowy zawierający implementację algorytmów, generatory danych oraz logikę benchmarku [cite: 2026-03-23].
* **wyniki.txt**: Plik generowany automatycznie, zawierający szczegółowe dane z pomiarów w formacie CSV.

## 🛠 Kompilacja i uruchomienie
Program można skompilować przy użyciu dowolnego kompilatora C++ wspierającego standard C++11 lub nowszy.

**Kompilacja (GCC):**
```bash
g++ src/Algorytmy_projekt.cpp -o benchmark -O3
