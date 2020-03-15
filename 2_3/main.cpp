#include <iostream>

/*
2_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n >> m.
Найдите их пересечение.
Требования: Время работы: O(m * log k),
где k - позиция элемента B[m-1] в массиве A..
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
Внимание! В этой задаче для каждого B[i]
сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.
*/

int binary_search(int* array, int left, int right, int value)
{
    int mid = 0;
    while (left != right -1)
    {
        mid = (left + right)/2;
        if (array[mid] > value)
            right = mid;
        else
            left = mid;
    }
    if (array[right] == value)
        return right;
    else if (array[left] == value)
        return left;
    else
        return -1;
}

void task_sol(int* A, int* B, int size_A, int size_B)
{
    int l = 0;
    int r = 1;
    int index_in_A = 0;

    for (int i = 0; i < size_B; i++)
    {
        if (B[i] <= A[r])
        {
            index_in_A = binary_search(A, l,  r, B[i]);
        }
        else
        {
            if (B[i] > A[size_A - 1])
            {
                break;
            }
            while(B[i] > A[r])
            {
                l = r;
                r *= 2;
                if (r > size_A - 1)
                {
                    r = size_A - 1;
                }
            }
            index_in_A = binary_search(A, l, r, B[i]);
        }
        if (index_in_A != -1)
        {
            std::cout << A[index_in_A] << " ";
        }
    }
}

int main()
{
    int size_A = 0;
    int size_B = 0;

    //std::cout << "Введите размер массива А: ";
    std::cin >> size_A;
    //std::cout << "Введите размер массива B: ";
    std::cin >> size_B;

    int A[size_A];
    int B[size_B];

    //std::cout << "Введите массив A: ";
    for (int i = 0; i < size_A; ++i)
    {
        std::cin >> A[i];
    }
    //std::cout << "Введите массив B: ";
    for (int i = 0; i < size_B; ++i)
    {
        std::cin >> B[i];
    }

    task_sol(A, B, size_A, size_B);

    return 0;
}
