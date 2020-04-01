#include <iostream>
#include "algorithm"
#include "vector"
#include "assert.h"

/*
 * Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Куча должна быть динамической.

 * Вовочка ест фрукты из бабушкиной корзины.
 * В корзине лежат фрукты разной массы.
 * Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
 * За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
 * откусывает от каждого половину и кладет огрызки обратно в корзину.
 * Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.
 * Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов.
 * Затем K - "грузоподъемность".
 * Формат выходных данных. Неотрицательное число - количество подходов к корзине.
 */

template <typename T>
class Comparator {
public:
    bool operator()(const T& left, const T& right)
    {
        return left < right;
    }

    bool isLess(const T& left, const T& right)
    {
        return left < right;
    }
    bool isGreater(const T& left, const T& right)
    {
        return left > right;
    }
    bool isLessEqual(const T& left, const T& right)
    {
        return left <= right;
    }
    bool isGreaterEqual(const T& left, const T& right)
    {
        return left >= right;
    }
};

#define INIT_ALLOC 5
#define EXTENSION_KOEF 2
template <typename T>
class Vector{
public:
    Vector()
    {
        data = nullptr;
        len = 0;
        allocated = 0;
    }

    ~Vector(){
        delete[] data;
    }

    void push_back(T value)
    {
        if (len == allocated)
            expand();
        assert(len < allocated && data != nullptr);
        data[len++] = value;
    }

    void pop_back()
    {
        assert(!isEmpty());
        len--;
    }

    bool isEmpty()
    {
        return len == 0;
    }

    T& front()
    {
        assert(!isEmpty());
        return data[0];
    }

    T& back()
    {
        assert(!isEmpty());
        return data[len - 1];
    }

    T& operator[](int i)
    {
        assert(i >= 0 && i < len && !isEmpty());
        return data[i];
    }

    int size()
    {
        return len;
    }

private:
    void expand()
    {
        int new_allocated = std::max(allocated * EXTENSION_KOEF, INIT_ALLOC);
        T* new_data = new T[new_allocated];
        std::copy(data, data + len, new_data);
        delete[] data;
        data = new_data;
        allocated = new_allocated;
    }

    T* data;
    int len;
    int allocated;
};

template <typename T, class Compare = Comparator<T> >
class Heap {
public:
    void Add(T value)
    {
        vector.push_back(value);

        SiftUp(vector.size() - 1);
    }

    T RemoveMax()
    {
        assert(!isEmpty());

        T max_element = vector.front();
        vector.front() = vector.back();

        vector.pop_back();

        if (!isEmpty())
            SiftDown(0);

        return max_element;
    }

    T GetMax()
    {
        if (isEmpty())
            return -1;
        return vector.front();
    }

    bool isEmpty()
    {
        return vector.isEmpty();
    }

private:
    void SiftUp(int index)
    {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (comparator(vector[index], vector[parent]) || vector[index] == vector[parent])
                return;
            std::swap(vector[index], vector[parent]);
            index = parent;
        }
    }

    void SiftDown(int i)
    {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int largest_child = i;

        if (left_child < vector.size() && comparator(vector[i], vector[left_child]))
            largest_child = left_child;
        if (right_child < vector.size() && comparator(vector[largest_child], vector[right_child]))
            largest_child = right_child;

        if (largest_child != i) {
            std::swap(vector[largest_child], vector[i]);
            SiftDown(largest_child);
        }
    }

    Vector<T> vector;
    Compare comparator;
};

int calc_iterations(Heap<int>* heap, int carr_capacity)
{
    int counter = 0;
    while (!(*heap).isEmpty()) {
        int control_sum = 0;
        Vector<int> bufer;

        while (true) {
            int tmp_element = (*heap).GetMax();
            if (tmp_element == -1)
                break;

            if (control_sum + tmp_element > carr_capacity)
                break;
            (*heap).RemoveMax();
            bufer.push_back(tmp_element);
            control_sum += tmp_element;
        }

        for (int i = 0; i < bufer.size(); i++) {
            if (bufer[i] != 1) {
                bufer[i] /= 2;
                (*heap).Add(bufer[i]);
            }
        }
        counter++;
    }
    return counter;
}

int main()
{
    int number_of_fruits = 0;
    //std::cout << "Input number of fruits: ";
    std::cin >> number_of_fruits;

    Heap<int> heap;

    int mass = 0;
    //std::cout << "Input masses of fruits: ";
    for (int i = 0; i < number_of_fruits; i++) {
        std::cin >> mass;
        heap.Add(mass);
    }

    //std::cout << "Input Vovochka carrying capacity: ";
    int carr_capacity = 0;
    std::cin >> carr_capacity;

    int result = calc_iterations(&heap, carr_capacity);
    std::cout << result;

    return 0;
}
