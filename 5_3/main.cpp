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

void sort(Point* array, int arr_size)
{
    for (int i = 0; i < arr_size - 1; i++)
    {
        for (int j = 0; j < arr_size - 1; j++)
        {
            if (array[j].value > array[j+1].value)
            {
                std::swap(array[j], array[j+1]);
            }
        }
    }
}

int find_length(Point* points_array, int arr_size)
{
    int length = 0;
    int thickness = 0;

    if (arr_size == 2 && points_array[0].status == 1 && points_array[1].status == -1)
    {
        return points_array[1].value - points_array[0].value;
    }

    for (int i = 0; i < arr_size; i++)
    {
        if (points_array[i].status == 1)
            thickness++;
        else
            thickness--;

        if (thickness > 0 && i >= 1)
        {
            length += points_array[i].value - points_array[i-1].value;
        }
    }
    return length;
}

int main()
{
    int number_of_segments = 0;
    std::cin >> number_of_segments;

    int arr_size = number_of_segments*2;

    Point points_array[arr_size];

    for (int i = 0; i < arr_size; ++i) {
        std::cin >> points_array[i].value;
        if (i == 0)
            points_array[i].status = 1;
        else
            points_array[i].status = -points_array[i-1].status;
    }

    sort(points_array, arr_size);
    int length = find_length(points_array, arr_size);
    std::cout << length;

    return 0;
}

