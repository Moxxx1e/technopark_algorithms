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

template <typename T>
class Comparator {
public:
    bool isLess(T left, T right)
    {
        return left < right;
    }
    bool isGreater(T left, T right)
    {
        return left > right;
    }
    bool isLessEqual(T left, T right)
    {
        return left <= right;
    }
    bool isGreaterEqual(T left, T right)
    {
        return left >= right;
    }
    bool isEqual(T left, T right)
    {
        return left == right;
    }
};

template <typename T, class Cmp = Comparator<T> >
void swap_pivot_and_first(T pivot, T* array, int l, int mid, int r, Cmp cmp)
{
    if (cmp.isEqual(pivot, array[r]))
        std::swap(array[r], array[l]);
    else if (cmp.isEqual(pivot, array[mid]))
        std::swap(array[mid], array[l]);
}

template <typename T, class Cmp = Comparator<T> >
T median(T first, T mid, T last, Cmp cmp)
{
    if (cmp.isLessEqual(first, mid) && cmp.isGreaterEqual(first, last))
        return first;
    else if (cmp.isGreaterEqual(first, mid) && cmp.isLessEqual(first, last))
        return first;
    else if (cmp.isGreaterEqual(mid, first) && cmp.isLessEqual(mid, last))
        return mid;
    else if (cmp.isLessEqual(mid, first) && cmp.isGreaterEqual(mid, last))
        return mid;
    else
        return last;
}

template <typename T, class Cmp = Comparator<T> >
int partition(T* array, int l, int r, Cmp cmp)
{
    int mid = (l + r) / 2;
    int pivot = median(array[l], array[mid], array[r], cmp);
    swap_pivot_and_first(pivot, array, l, mid, r, cmp);

    int i = r, j = i - 1;
    while (cmp.isGreater(array[i], pivot) && j > 0) {
        i--;
        j--;
    }

    while (j > 0) {
        while (cmp.isLessEqual(array[j], pivot) && j > 0) {
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

template <typename T, class Cmp = Comparator<T> >
T kth_statistic(T* array, int size, int k, Cmp cmp = Cmp())
{
    int l = 0;
    int r = size - 1;
    while (1) {
        int pivot_pos = partition(array, l, r, cmp);
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
