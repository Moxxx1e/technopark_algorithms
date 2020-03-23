#include <iostream>
#include "vector"

/*
 * Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 */

#define INIT_ALLOC 5
#define EXTENSION_KOEF 2

template <typename T>
class Vector{
public:
    Vector()
    {
        data = NULL;
        len = 0;
        allocated = INIT_ALLOC;
    }

    ~Vector()
    {
        len = 0;
        allocated = 0;
        if (data)
            free(data);
    }

    void push_back(T value)
    {
        if (!data)
        {
            data = (T*)malloc(allocated * sizeof(T));
            if (!data)
                return;
        }
        else
        {
            if (len >= allocated)
            {
                allocated *= EXTENSION_KOEF;
                T* tmp = (T*)realloc(data, allocated * sizeof(T));
                if (!tmp)
                {
                    free(data);
                    return;
                }
                data = tmp;
            }
        }
        data[len] = value;
        len++;
    }

    T pop_back()
    {
        if (!isEmpty())
            len--;
        else
            return -1;

        T return_value = data[len];

        return return_value;
    }

    bool isEmpty()
    {
        return len == 0;
    }

    T back()
    {
        if (isEmpty())
            return -1;

        return data[len - 1];
    }

private:
    T* data;
    int len;
    size_t allocated;
};

class Stack{
public:
    ~Stack()
    {
        while (!isEmpty())
            Pop();
    }

    void Push(int value)
    {
        dyn_array.push_back(value);
    }

    int Pop()
    {
        if (isEmpty())
            return -1;
        int pop_element = dyn_array.back();
        dyn_array.pop_back();
        return pop_element;
    }

    bool isEmpty()
    {
        return dyn_array.isEmpty();
    }

private:
    Vector<int> dyn_array;
};

class Queue{
public:
    ~Queue()
    {
        while(!isEmpty())
        {
            Dequeue();
        }
    }

    void Enqueue(int val)
    {
        stack_1.Push(val);
    }

    int Dequeue()
    {
        if (isEmpty())
            return -1;

        if (stack_2.isEmpty())
        {
            while (!stack_1.isEmpty())
            {
                stack_2.Push(stack_1.Pop());
            }
        }

        return stack_2.Pop();
    }

    bool isEmpty()
    {
        return stack_1.isEmpty() && stack_2.isEmpty();
    }

private:
    Stack stack_1;
    Stack stack_2;
};

int main() {
    int command = 0;
    int number_of_commands = 0;
    std::cin >> number_of_commands;

    Queue queue;

    int counter = 0;
    int counter_success = 0;
    for (int i = 0; i < number_of_commands; i++)
    {
        std::cin >> command;
        if (command == 3)
        {
            int number = 0;
            std::cin >> number;
            queue.Enqueue(number);
        }
        else if (command == 2)
        {
            counter++;
            int value = 0;
            value = queue.Dequeue();
            int read_value = 0;
            std::cin >> read_value;
            if (read_value == value)
            {
                counter_success++;
            }
        }
    }

    if (counter == counter_success)
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
