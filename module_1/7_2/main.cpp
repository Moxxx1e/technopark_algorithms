#include <iostream>
#include "assert.h"

/*
 * Дан массив неотрицательных целых 64-битных чисел.
 * Количество чисел не больше 10^6.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.
 */

int digit(long long number, int byte_num)
{
    return (number >> (byte_num * 8)) & 0xFF;
}

void fill_zeros(int* array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

#define ALPHABET_SIZE 255
#define CAPACITY 8
void lsd_sort(long long* array, int arr_size)
{
    int digit_index_array[ALPHABET_SIZE];
    for (int i = 0; i < CAPACITY; i++) {
        long long tmp_array[arr_size];
        fill_zeros(digit_index_array, ALPHABET_SIZE);

        for (int j = 0; j < arr_size; j++) {
            int d = digit(array[j], i);
            digit_index_array[d]++;
        }

        int count = 0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            int tmp = digit_index_array[j];
            digit_index_array[j] = count;
            count += tmp;
        }

        for (int j = 0; j < arr_size; j++) {
            int d = digit(array[j], i);
            tmp_array[digit_index_array[d]] = array[j];
            digit_index_array[d]++;
        }

        for (int j = 0; j < arr_size; j++)
            array[j] = tmp_array[j];
    }
}

int main()
{
    int arr_size = 0;
    std::cin >> arr_size;

    long long array[arr_size];
    for (int i = 0; i < arr_size; i++) {
        std::cin >> array[i];
    }

    lsd_sort(array, arr_size);

    for (int i = 0; i < arr_size; i++) {
        std::cout << array[i] << " ";
    }

    return 0;
}
