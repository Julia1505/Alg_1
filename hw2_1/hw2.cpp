//2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
// Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
// равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
//Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)).
// Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска
// размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
//Формат входных данных.
//В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.

#include <iostream>

int binPoisk(const int array[], int searchElem, int left, int right) {
    int mid = 0;
    int count = right;
    while (left < right) {
        mid = (left  + right) / 2;
        if (array[mid] < searchElem) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return (left == count) ? -1 : left;
}

int expotentialPoisk (const int array[], int length, int searchElem) {
    int border = 1;
    while (border < (length - 1) && array[border] < searchElem) {
        border *= 2;
    }

    if (border > (length - 1)) {
        border = length - 1;
    }
    int res = binPoisk(array, searchElem, border / 2, border + 1);
    return (res == -1) ? length : res;
}

void inputArray(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        std::cin >> array[i];
    }
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    auto *A = new int[n];
    auto *B = new int[m];

    inputArray(A, n);
    inputArray(B, m);

    for (int i = 0; i < m; ++i) {
        std::cout << expotentialPoisk(A, n, B[i]) << ' ';
    }

    delete[] A;
    delete[] B;

    return 0;
}
