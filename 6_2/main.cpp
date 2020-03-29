#include <iostream>

/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число, к
 * оторое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * Требования: к дополнительной памяти: O(n). Среднее время работы: O(n).
 * Должна быть отдельно выделенная функция partition. Рекурсия запрещена.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 *
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 * Описание для случая прохода от начала массива к концу:
 * Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
 * Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 * Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
 * Последним элементом лежит опорный.
 * Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 * Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 * Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 * Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 * В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

 * 6_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

int median(int first, int mid, int last)
{
    if (first <= mid && first >= last)
        return first;
    else if (first >= mid && first <= last)
        return first;
    else if (mid >= first && mid <= last)
        return mid;
    else if (mid <= first && mid >= last)
        return mid;
    else
        return last;
}

void swap_pivot_and_first(int pivot, int* array, int l, int mid, int r)
{
    if (pivot == array[r])
        std::swap(array[r], array[l]);
    else if (pivot == array[mid])
        std::swap(array[mid], array[l]);
}

int partition(int* array, int l, int r)
{
    int mid = (l + r) / 2;
    int pivot = median(array[l], array[mid], array[r]);
    swap_pivot_and_first(pivot, array, l, mid, r);

    int i = r, j = i - 1;

    while (array[i] > pivot && j > 0) {
        i--;
        j--;
    }

    while (j > 0) {
        while (array[j] <= pivot && j > 0) {
            j--;
        }

        if (j > 0) {
            std::swap(array[j], array[i]);
            j--;
            i--;
        }
    }

    std::swap(array[i], array[l]);
    return i;
}

int kth_statistic(int* array, int size, int k)
{
    int l = 0;
    int r = size - 1;
    while (1) {
        int pivot_pos = partition(array, l, r);
        if (pivot_pos == k) {
            return array[pivot_pos];
        }
        else {
            if (pivot_pos < k) {
                l = pivot_pos + 1;
            }
            else {
                r = pivot_pos - 1;
            }
        }
    }
}

int main()
{
    int arr_size, k = 0;

    std::cin >> arr_size >> k;
    int array[arr_size];
    for (int i = 0; i < arr_size; ++i) {
        std::cin >> array[i];
    }

    int result = kth_statistic(array, arr_size, k);

    std::cout << result;

    return 0;
}
