#include <iostream>

/*
 *
 /* В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 * затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.
 * Необходимо определить номер уцелевшего.
 * N, k ≤ 10000.
 */

struct Node
{
    int value;
    Node* next;
};

Node* create_node(int value)
{
    Node* new_node = new Node;

    new_node->value = value;
    new_node->next = nullptr;
    return new_node;
}

Node* append_node(Node* head, Node* new_element)
{
    if (!head)
    {
        head = new_element;
        head->next = head;
        return head;
    }

    Node* cur = head;
    for(; cur->next != head; cur = cur->next);

    cur->next = new_element;
    new_element->next = head;
    return head;
}

Node* delete_element(Node* element)
{
    Node* cur = element;
    for (; cur->next != element; cur = cur->next);

    if (cur->next == element->next)
    {
        delete element;
        return nullptr;
    }

    cur->next = element->next;
    delete element;
    return cur->next;
}

void print_list(Node* head)
{
    Node* cur = head;
    std::cout << cur->value << " ";
    for (cur = head->next; cur != head; cur = cur->next)
    {
        std::cout << cur->value << " ";
    }
}

void free_list(Node* head)
{
    Node* element = head;
    while (element)
        element = delete_element(element);
}

int counting(Node* head, int k)
{
    Node* cur = head;

    while(cur->next != cur)
    {
        for(int i = 0; i < k-1; i++)
            cur = cur->next;

        cur = delete_element(cur);
    }
    int ret_value = cur->value;
    delete cur;
    return ret_value;
}

int main()
{
    int N = 0;
    std::cin >> N;

    Node* head = nullptr;
    for (int i = 1; i <= N; ++i)
    {
        Node *new_node = create_node(i);
        head = append_node(head, new_node);
    }

    int k = 0;
    std::cin >> k;
    int answer = counting(head, k);

    std::cout << answer;
    return 0;
}
