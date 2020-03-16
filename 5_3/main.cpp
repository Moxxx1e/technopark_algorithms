#include <iostream>
#include "algorithm"
/*
 *
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
Формат ввода

В первой строке записано количество отрезков.
В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.
Формат вывода

Выведите целое число — длину окрашенной части.
 */

struct Point{
    int value;
    int status;
};

bool my_greater_equal(const Point p1, const Point p2)
{
    return  p1.value >= p2.value;
}

template <typename T, typename Comparator = std::greater_equal<T>>
void mergesort(T* arr, int l, int r, Comparator cmp)
{
    if (l < r)
    {
        int m = l + (r - l)/2;

        mergesort(arr, l, m, cmp);
        mergesort(arr, m+1, r, cmp);

        merge(arr, l, m, r, cmp);
    }
}

template <typename T, typename Comparator = std::greater_equal<T>>
void merge(T* arr, int l, int m, int r, Comparator cmp)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    T L[n1];
    T R[n2];

    int i, j, k;
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2)
    {
        if (cmp(R[j], L[i]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int find_length(Point* points_array, int arr_size)
{
    int length = 0;
    int thickness = 0;
    for (int i = 0; i < arr_size; i++)
    {
        if (thickness && i >= 0)
            length += points_array[i].value - points_array[i-1].value;

        if (points_array[i].status == 1)
            thickness++;
        else
            thickness--;
    }
    return length;
}

int main()
{
    int number_of_segments = 0;
    std::cin >> number_of_segments;

    int arr_size = number_of_segments*2;

    Point points_array[arr_size];

    for (int i = 0; i < arr_size; ++i)
    {
        std::cin >> points_array[i].value;
        if (i == 0)
            points_array[i].status = 1;
        else
            points_array[i].status = -points_array[i-1].status;
    }

    mergesort(points_array,0, arr_size-1, my_greater_equal);

    int length = find_length(points_array, arr_size);
    std::cout << length;

    return 0;
}

