# Benchmark Algorytmów Sortowania: Warianty Insertion Sort

## 📝 Opis projektu
Projekt ma na celu empiryczną analizę wydajności różnych wariantów algorytmu **Sortowania przez wstawianie (Insertion Sort)**. Program został zaimplementowany w języku C++ z podziałem na moduły, co zapewnia wysoką czytelność i łatwość rozbudowy.

Głównym celem było sprawdzenie, jak optymalizacje (np. wyszukiwanie binarne) oraz charakterystyka danych wejściowych (losowe, posortowane, odwrotne) wpływają na czas wykonania, liczbę porównań oraz liczbę przesunięć elementów.

## 🚀 Implementowane algorytmy
1. **Classic Insertion Sort**: Standardowa implementacja algorytmu ze wstawianiem liniowym.
2. **Binary Insertion Sort**: Optymalizacja polegająca na użyciu wyszukiwania binarnego ($O(\log n)$) do znalezienia miejsca wstawienia elementu.
3. **Linear Mirror Sort**: Wariant algorytmu przeszukujący tablicę od końca (lustrzane odbicie).



## 📊 Wyniki pomiarów (dla n = 10 000)
Poniższe dane stanowią średnią ze 100 pomiarów przeprowadzonych w trybie **Release (x64)**.

| Algorytm | Typ danych | Czas [μs] | Porównania | Przesunięcia |
| :--- | :--- | :--- | :--- | :--- |
| **Classic** | Losowe | 63 800 | 25 016 522 | 25 006 531 |
| **Binary** | Losowe | 79 124 | **119 004** | 25 006 531 |
| **Classic** | Posortowane | **39** | 9 999 | 0 |
| **Binary** | Posortowane | 525 | 113 631 | 0 |



### Kluczowe wnioski:
* **Wyszukiwanie Binarne**: Drastycznie redukuje liczbę porównań (z ~25 mln do ~119 tys.), jednak całkowity czas wykonania jest nieco wyższy przez narzut obliczeniowy wyszukiwania binarnego oraz tę samą liczbę przesunięć w pamięci.
* **Dane Posortowane**: Algorytm wykazuje swoją najlepszą wydajność ($O(n)$), co potwierdza wynik zaledwie 39 μs.
* **Wpływ Linkera i Optymalizacji**: Kod kompilowany w trybie **Release** działa wielokrotnie szybciej niż w trybie Debug dzięki optymalizacjom pętli przez kompilator.

## 📁 Struktura plików
Projekt został podzielony zgodnie z dobrymi praktykami programowania strukturalnego i obiektowego:
- `main.cpp`: Logika pomiarowa, interakcja z użytkownikiem i pętla benchmarku.
- `sorting.cpp`: Implementacje algorytmów sortujących oraz generatorów danych.
- `sorting.h`: Plik nagłówkowy zawierający prototypy funkcji i definicję struktury `Stats`.



## 🛠 Kompilacja i uruchomienie
Program można skompilować przy użyciu kompilatora GCC (g++) lub środowiska Visual Studio.

**Kompilacja przez terminal:**
```bash
g++ main.cpp sorting.cpp -o sort_benchmark -O3
