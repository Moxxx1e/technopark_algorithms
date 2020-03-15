#include <iostream>
#include "vector"

/*
 * Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 */

class Stack{
public:
    //Stack();
    ~Stack(){
        while (!isEmpty())
        {
            Pop();
        }
    }

    void Push(int value)
    {
        dyn_array.push_back(value);
    }

    int Pop()
    {
        int pop_element = dyn_array.back();
        dyn_array.pop_back();
        return pop_element;
    }

    bool isEmpty()
    {
        return dyn_array.empty();
    }

private:
    std::vector<int> dyn_array;
};

class Queue{
public:
    //Queue();

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
        {
            return -1;
        }
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
