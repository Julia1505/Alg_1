/*Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
        медиана
90%  перцентиль

        Требования: к дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
 Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.*/

#include <iostream>
#include <sstream>

using std::swap;

template <class T>
bool compDefault(const T& l, const T& r) {
    return l > r;
}

template <class T>
int IndexMediana (T *array, int a, int b, int c, bool (*comp)(const T&, const T&) = compDefault) {
    if (comp(array[a], array[b])) {
        if (comp(array[c], array[a]))
            return a;
        return (comp(array[b], array[c])) ? b : c;
    }
    if (comp(array[c], array[b]))
        return b;
    return (comp(array[a], array[c])) ? a : c;
}

template <class T>
int Partition( T *array, int l, int r, bool (*comp)(const T&, const T&) = compDefault ) {
    if (r - l + 1 <= 1) {
        return 0;
    }

    swap(array[l], array[IndexMediana(array, l, (r + l + 1) / 2, r)]);
    T pivot = array[l];

    int i = r;
    int j = r;
    while (j != l) {
        if (comp(pivot, array[j])) {
            --j;
        } else {
            swap(array[i--], array[j--]);
        }
    }
    swap(array[i], array[l]);
    return i;
}


int FindKStat(int* a, int n, int k) {
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int pivotPos = Partition(a, l, r);
        if (pivotPos == k) {
            return a[k];
        }
        if (k < pivotPos) {
            r = pivotPos - 1;
        } else {
            l = pivotPos + 1;
        }
    }
    return a[l];
}


int run(std::istream& input, std::ostream& output) {
    int N;
    input >> N;
    int *array = new int[N];
    for (int i = 0; i < N; ++i) {
        input >> array[i];
    }
    int par10 = (N / 10);
    int med = (N + 1) / 2;
    int par90 = N * 9 / 10;
    int res1 = FindKStat(array, N, par10);
    int res2 = FindKStat(array, N, med);
    int res3 = FindKStat(array, N, par90);
    output << res1 <<"\n" << res2 << "\n" << res3;

    delete[] array;
    return 0;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}
