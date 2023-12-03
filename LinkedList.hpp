#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node(const T &value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    Node<T> *getHead()
    {
        return head;
    }

    void insert(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node<T> *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // reverse the linked list
    void reverse()
    {
        Node<T> *current = head;
        Node<T> *prev = NULL;
        Node<T> *next = NULL;

        while (current)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }
};
