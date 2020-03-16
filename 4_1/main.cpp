#include <iostream>
#include "algorithm"
#include "vector"

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
class Heap{
public:
    ~Heap()
    {
        while(!isEmpty())
            vector.pop_back();
    }

    void Add(T value)
    {
        vector.push_back(value);

        int i = vector.size() - 1;
        int parent = (i-1)/2;

        while(i > 0 && vector[i] > vector[parent])
        {
            std::swap(vector[i], vector[parent]);
            i = parent;
            parent = (i-1)/2;
        }

        if (i >= 1 && vector[i-1] > vector[i])
            std::swap(vector[i], vector[i-1]);
    }

    T RemoveMax()
    {
        if (isEmpty())
            return -1;

        T max_element = vector.front();
        std::swap(vector.back(), vector.front());

        vector.pop_back();

        if (!isEmpty())
            Heapify(0);

        return max_element;
    }

    void Heapify(int i)
    {
        int left_child;
        int right_child;
        int largest_child;

        for(; ; )
        {
            left_child = 2*i + 1;
            right_child = 2*i + 2;
            largest_child = i;

            if (left_child < vector.size()-1 && vector[largest_child] < vector[left_child])
                largest_child = left_child;
            else if (right_child < vector.size()-1 && vector[largest_child] < vector[right_child])
                largest_child = right_child;

            if (largest_child == i)
                break;

            std::swap(vector[largest_child], vector[i]);
            i = largest_child;
        }
    }

    T Get_max()
    {
        if (vector.empty())
            return -1;
        return vector.front();
    }

    bool isEmpty()
    {
        return vector.empty();
    }

private:
    std::vector<T> vector;
};

int calc_iterations(Heap<int> heap, int carr_capacity)
{
    int counter = 0;
    while(!heap.isEmpty())
    {
        int control_sum = 0;
        std::vector<int> bufer;

        while(true)
        {
            int tmp_element = heap.Get_max();
            if (tmp_element == -1)
                break;

            if (control_sum + tmp_element > carr_capacity)
                break;

            heap.RemoveMax();
            bufer.push_back(tmp_element);
            control_sum += tmp_element;
        }

        for(int & i : bufer)
        {
            if (i != 1)
            {
                i /= 2;
                heap.Add(i);
            }
        }
        counter++;
    }
    return counter;
}

int main()
{
    int number_of_fruits = 0;
    std::cout << "Input number of fruits: ";
    std::cin >> number_of_fruits;

    Heap<int> heap;

    int mass = 0;
    std::cout << "Input masses of fruits: ";
    for (int i = 0; i < number_of_fruits; i++)
    {
        std::cin >> mass;
        heap.Add(mass);
    }

    std::cout << "Input Vovochka carrying capacity: ";
    int carr_capacity = 0;
    std::cin >> carr_capacity;

    int result = calc_iterations(heap, carr_capacity);
    std::cout << result;

    return 0;
}
